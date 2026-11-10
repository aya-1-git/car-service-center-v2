# Car Service Center Guidance Plan

## Team split (final)

| Member | Entities / Infrastructure | Simulator steps |
|---|---|---|
| **Member 1** | `Car`, `Bay`, `CarGenerator` (1000 random cars), bay setup (`Center_Setup.cpp`), repo setup | **2.1, 2.2** |
| **Member 2** | All data structures + their tests | **2.3, 2.4** |
| **Member 3** | `Center.h/.cpp`, final integration and checks | **2.5, 2.6, 2.7, 2.11** |
| **Member 4** | `UI` class, `ID.txt`, video recording and upload | **2.8, 2.9, 2.10** |

---

## PART 1: Shared names (everyone must use exactly these)

### Enums and struct (in `entities/Car.h`)

```cpp
enum CarStatus { IDLE, ERLY, LATE, REDY, DIAG, WAIT, SERV, CNCL, FNSH };
enum SeqType   { SS, FS };
enum UnitType  { DU, MU, EU, WU };
struct Service { UnitType type; int duration; };
```

### Car data members

| Name | Type | Meaning |
|---|---|---|
| `cid` | int | car ID (printed as C<cid>) |
| `pt` | int | appointment time |
| `vt` | int | arrival time |
| `dd` | int | diagnosis duration |
| `status` | CarStatus | current status |
| `seqType` | SeqType | SS or FS |
| `serviceList` | Queue<Service*> | required services |
| `diagStart`, `diagEnd` | int | diagnosis start / end timestep |
| `servStart`, `servEnd` | int | service start / end timestep |
| `currentBay` | Bay* | bay the car is in (null if none) |
| `tw`, `ts` | int | total waiting / service time |
| `ft` | int | finish time or cancel time |

Constructor: `Car(int cid, int pt, int vt, int dd)`
Getters/setters follow the pattern `getVT()`, `setStatus(...)`, `getDiagEnd()`, `setDiagEnd(int)`, ...
Print helpers: `print()`, `printWithBay()`, `printWithNextService()`, `printWithFinishTime()`, and `operator<<` for `Car*`.

### Bay data members

| Name | Type | Meaning |
|---|---|---|
| `id` | int | bay ID (D4, M14, E5, W3) |
| `unitType` | UnitType | DU / MU / EU / WU |
| `capacity` | int | 1 (DU/MU/EU) or WB_Cap (wash) |
| `remainingCapacity` | int | free slots |

Functions: `getID()`, `getUnitType()`, `getRemainingCapacity()`, `isFull()`, `isEmpty()`, `addCar()`, `removeCar()`, `print()`.

### Lists inside `Center` (all store pointers)

| Name | Type | Order |
|---|---|---|
| `idleList` | PriQueue<Car*> | min VT |
| `earlyList` | EarlyPQ | min PT |
| `lateList` | LateQueue | arrival order |
| `readyList` | Queue<Car*> | FCFS |
| `freeDiagBays` | Queue<Bay*> | FCFS |
| `diagList` | PriQueue<Car*> | min diagEnd |
| `waitMB`, `waitEB`, `waitWB` | WaitingQueue | FCFS + running total |
| `freeMB`, `freeEB` | Queue<Bay*> | FCFS |
| `freeWB` | Queue<Bay*> | bays that still have room |
| `servList` | PriQueue<Car*> | min servEnd |
| `cnclList`, `fnshList` | Stack<Car*> | top = latest time |

Also in `Center`: `int totalCars;`, `int currentTimestep;`, `UI ui;`

### Data structure functions (every DS has these)

*(Double-check these names against the lab code on Day 0.)*

| Function | Meaning |
|---|---|
| `enqueue(x)` / `push(x)` | insert |
| `dequeue(x)` / `pop(x)` | remove top/front into `x`, false if empty |
| `peek(x)` | look at top/front without removing |
| `isEmpty()` | empty? |
| `GetCount()` | number of elements |
| `print()` | print all elements, **never removes anything** |

Derived classes:
- `EarlyPQ` (from PriQueue): `removeAt(position, removed)`
- `LateQueue` (from Queue): `removeAt(position, removed)`, order of the rest unchanged
- `WaitingQueue` (from Queue): `GetTotalServiceTime()`, updated on enqueue/dequeue

(If the lab uses different names, we fix this table once and everyone follows it.)

### Center functions (all declared by Member 3 in `Center.h`)

```cpp
// Member 1: setup + steps 2.1, 2.2
void setupBays(int nDU, int nMU, int nEU, int nWU, int wbCap);
void loadRandomCars(int count);
void moveIdleToLists(int t);      // 2.1
void moveEarlyToReady(int t);     // 2.2

// Member 2: steps 2.3, 2.4
void cancelRandomLate(int t);     // 2.3
void moveLateToReady(int t);      // 2.4

// Member 3: driver + steps 2.5, 2.6, 2.7, 2.11
bool allCarsDone() const;
void runRandomSimulation();       // calls 2.1 to 2.11 in order, every timestep
void assignReadyToDiag(int t);    // 2.5
void finishDiagnosis(int t);      // 2.6, 2.7
void printState(int t);           // 2.11 (calls ui.printScreen)

// Member 4: steps 2.8, 2.9, 2.10
void assignWaitToBays(int t);     // 2.8
void finishServices(int t);       // 2.9, 2.10
```

`runRandomSimulation()` calls the functions in exactly this order each timestep:
`moveIdleToLists` → `moveEarlyToReady` → `cancelRandomLate` → `moveLateToReady` → `assignReadyToDiag` → `finishDiagnosis` → `assignWaitToBays` → `finishServices` → `printState`.

(`simPart1` / `simPart2` are removed. Each member now has their own step functions.)

### UI (Member 4)

`UI::printScreen(...)` takes the lists as references and only calls each list's `print()`.
**Member 4 pushes the `UI.h` skeleton (declaration of `printScreen`) on Day 0** so Member 3's `printState` can compile against it.

---

## PART 2: Folder structure and owners

```
CarServiceCenter/
├── .gitignore            (Member 1)
├── README.md             (Member 1)  full contract
├── TEAM_GUIDE.md         (Member 1)  this file
├── ID.txt                (Member 4)
├── main.cpp              (SHARED, ~10 lines, only calls each member's function)
│
├── entities/             (Member 1)
│   ├── Car.h / Car.cpp
│   ├── Bay.h / Bay.cpp
│   └── CarGenerator.h / CarGenerator.cpp     generates the 1000 cars
│
├── ds/                   (Member 2)
│   ├── Queue.h, Stack.h, PriQueue.h          lab code + print() + GetCount()
│   ├── EarlyPQ.h, LateQueue.h, WaitingQueue.h
│   └── DS_Test.cpp                           tests only
│
├── ui/                   (Member 4)
│   └── UI.h / UI.cpp
│
└── center/
    ├── Center.h                  (Member 3)  all lists + ALL declarations
    ├── Center.cpp                (Member 3)  constructor, destructor, allCarsDone(), runRandomSimulation()
    ├── Center_Setup.cpp          (Member 1)  creates bays, loads random cars
    ├── Center_Sim_M1.cpp         (Member 1)  steps 2.1, 2.2
    ├── Center_Sim_M2.cpp         (Member 2)  steps 2.3, 2.4
    ├── Center_Sim_M3.cpp         (Member 3)  steps 2.5, 2.6, 2.7, 2.11
    └── Center_Sim_M4.cpp         (Member 4)  steps 2.8, 2.9, 2.10
```

One simulator file per member, so nobody edits the same file.

### Who does what

- **Member 1:** `Car`, `Bay`, `CarGenerator` (1000 random cars), `Center_Setup.cpp`, repo setup, steps 2.1 to 2.2.
- **Member 2:** all data structures and their tests, steps 2.3 to 2.4.
- **Member 3:** `Center.h/.cpp`, steps 2.5 to 2.7 and 2.11, final integration and checks.
- **Member 4:** `UI` class, `ID.txt`, steps 2.8 to 2.10, video recording and upload.
- **Everyone:** explains their own part in the video, reviews the rules before submitting.

---

## PART 3: How we work

### Rules (breaking these loses marks)
1. **No STL** (no vector, queue, list, algorithm...). Only the lab Stack/Queue/PriQueue or classes derived from them.
2. **No global variables.**
3. **No friendship**, except `operator<<`.
4. **Share, move, don't copy:** each car and bay is created once with `new`. Lists hold pointers only. Moving a car = dequeue the pointer from one list, enqueue the same pointer into another.
5. Only edits allowed inside the lab DS classes: add `print()` and `GetCount()`.
6. Never commit `.exe` or `.o` files.
7. The repo stays **private**.

### Only edit your own files
If you need a change in someone else's file, message them. This avoids Git conflicts.

### Nobody waits for anybody
- On Day 0, Member 1 pushes skeleton `Car.h` / `Bay.h`, Member 3 pushes `Center.h` with all declarations, and Member 4 pushes the `UI.h` skeleton.
- After that, everyone works on their own part in their own free time.
- Test your part alone with a tiny temporary stub (for example, test the DS with `int`, test a simulator step with a few fake cars). Don't wait for a teammate's code.

### Git routine (GitHub Desktop or terminal)
- Branches: `member1-entities-steps`, `member2-ds-steps`, `member3-center`, `member4-ui-steps`.
- **Every day before starting:** switch to `main`, pull, switch back to your branch, merge `main` into it.
- **Commit small and often** with a clear message ("Add LateQueue removeAt").
- **When your part compiles and is tested:** push, open a Pull Request into `main`, someone else glances at it, then merge.
- Never merge code that doesn't compile into `main`.

### Test before merging
- Every DS: enqueue/dequeue, empty case, `GetCount()` correct after each operation, `print()` doesn't remove anything, `removeAt` at start/middle/end/out of range.
- Simulator steps: first with a few cars, then 1000.
- Final check: `fnshList.GetCount() + cnclList.GetCount() == 1000` and all other lists are empty.

### Simulator steps (each timestep; skip a step if there is no car/bay)

| Step | What happens | Owner |
|---|---|---|
| 2.1 | Top 50 from IDLE go randomly to LATE / ERLY / REDY | Member 1 |
| 2.2 | Top 6 from ERLY go to REDY | Member 1 |
| 2.3 | With 10% probability, a random LATE car (not the top) goes to CNCL | Member 2 |
| 2.4 | Top 6 from LATE go to REDY | Member 2 |
| 2.5 | Each free diagnosis bay takes one car from REDY | Member 3 |
| 2.6 / 2.7 | After 3 timesteps in DIAG: 20% go to CNCL, the rest go to a random WAIT list. The bay becomes free. | Member 3 |
| 2.8 | Top 6 from WAIT lists go to a random bay (MB 60%, EB 30%, WB 10%). No free bay means the car stays. | Member 4 |
| 2.9 / 2.10 | After 4 timesteps in SERV: 40% go to FNSH, the rest go back to a WAIT list. The bay becomes free. | Member 4 |
| 2.11 | Print all lists | Member 3 (calls Member 4's UI) |
| Stop | When all cars are in FNSH or CNCL | Member 3 |

### Handoffs between members
- Member 1's 2.1 and 2.2 use `idleList`, `earlyList`, `lateList`, `readyList` from Member 2's DS.
- Member 2's 2.3 uses `LateQueue::removeAt`, so Member 2 owns both the function and the step that uses it.
- Member 3's 2.5 uses `freeDiagBays`, filled by Member 1's `setupBays`.
- Member 4's 2.8 to 2.10 use the `Car`/`Bay` functions from Member 1 and the `WaitingQueue` from Member 2.
- Member 3's `printState` calls Member 4's `UI::printScreen`.

### Timeline (submission Fri 13 Nov, no late submission)

| When | What |
|---|---|
| Mon 9 Nov | New split starts: push skeletons (`Car.h`, `Bay.h`, `Center.h`, `UI.h`), check names against lab code. Anyone who already wrote code for a step that changed owner hands it to the new owner. |
| Mon 9 to Tue 10 Nov | Each member finishes and tests their own part alone |
| Tue 10 Nov (night) | Merge everything into `main` |
| Wed 11 Nov | Integration: compile, fix errors, run with 1000 cars, check rules (no STL, globals, friendship) |
| Thu 12 Nov | Record video, upload to Drive (access for everyone), check `ID.txt`, no `.exe` |
| Fri 13 Nov | Submit in the morning |