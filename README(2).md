# Online Game Matchmaking System

This project implements a simple matchmaking system for online games, developed in C++ as part of a Data Structures assignment.

The system manages players who are waiting to join a match. Each player has an ID, a name, a score representing their skill level, and a timestamp representing their arrival order in the queue.

The main goal of the project is to use sorting algorithms to organize players by score and make it easier to form balanced groups of players with similar skill levels.

## Project Description

The matchmaking system stores players in a waiting queue and allows the program to:

- insert new players;
- remove players by ID;
- sort players by score using insertion sort;
- sort players by score using merge sort;
- form groups of players with close scores;
- retrieve the current waiting players;
- print the current state of the waiting queue.

Players are stored inside the `Matchmaking` class using a static array with maximum capacity defined by `MAX_PLAYERS`.

The project does not use STL data structures such as `vector`, `list`, `map`, `queue`, or `stack`. The sorting algorithms are implemented manually, without using `std::sort` or any other built-in sorting function.

## Sorting Criteria

Players are sorted in ascending order of score.

If two players have the same score, the player with the smaller timestamp comes first.

Therefore, the sorting priority is:

1. smaller score;
2. smaller timestamp in case of equal scores.

Example:

```text
Before sorting:
[1 | Ana   | 1000 | 3]
[2 | Bruno | 900  | 2]
[3 | Carla | 1000 | 1]

After sorting:
[2 | Bruno | 900  | 2]
[3 | Carla | 1000 | 1]
[1 | Ana   | 1000 | 3]
```

Carla appears before Ana because both have score `1000`, but Carla has a smaller timestamp.

## Group Formation

A valid group is formed by `groupSize` consecutive players in the sorted array such that:

```text
highest_score - lowest_score <= delta
```

For example, if the scores are:

```text
1000, 1010, 1020
```

and:

```text
groupSize = 3
delta = 30
```

then the group is valid because:

```text
1020 - 1000 = 20 <= 30
```

The `formGroup` method assumes that the players are already sorted by score.

The method searches for the first valid group in the current order of the array. If a valid group is found, the selected players are removed from the waiting queue and returned in a dynamically allocated array.

If no valid group is found, the method returns `nullptr` and no player is removed.

## File Organization

The project is organized using `.hpp` and `.cpp` files.

```text
main.cpp
Matchmaking.hpp
Matchmaking.cpp
Player.hpp
Player.cpp
```

### File Description

- `main.cpp`: contains the test cases for the implemented methods.
- `Player.hpp`: declares the `Player` class.
- `Player.cpp`: implements the `Player` class.
- `Matchmaking.hpp`: declares the `Matchmaking` class.
- `Matchmaking.cpp`: implements the `Matchmaking` class.

## Main Classes

### Player

The `Player` class represents a player waiting for a match.

Each player has:

- `id`: unique player identifier;
- `name`: player name;
- `score`: skill score;
- `timestamp`: arrival order in the queue.

Main methods:

```cpp
Player();
Player(int id, std::string name, int score, int timestamp);
~Player();

int getId();
std::string getName();
int getScore();
int getTimestamp();
```

### Matchmaking

The `Matchmaking` class is responsible for managing the players waiting for a match.

It stores the players in a static array:

```cpp
Player players[MAX_PLAYERS];
int size;
```

Main methods:

```cpp
bool insert(Player player);
bool removePlayer(int id);

void sortByScoreInsertion();
void sortByScoreMerge();

Player* formGroup(int groupSize, int delta, int* n);

Player* getWaitingPlayers(int* n);

void printWaitingPlayers();
```

## Compilation Instructions

To compile the project, run the following command in the terminal:

```bash
g++ main.cpp Matchmaking.cpp Player.cpp -o matchmaking
```

## Execution Instructions

After compiling the project, run:

```bash
./matchmaking
```

## Running the Tests

The tests are implemented in the `main.cpp` file.

To run the tests, first compile the project:

```bash
g++ main.cpp Matchmaking.cpp Player.cpp -o matchmaking
```

Then execute the program:

```bash
./matchmaking
```

The output will show the results of the test cases created for the system.

The tests include:

- player insertion;
- player removal by ID;
- printing the waiting queue;
- sorting players using insertion sort;
- sorting players using merge sort;
- sorting players with equal scores;
- successful group formation;
- unsuccessful group formation;
- retrieving the current waiting players using `getWaitingPlayers`.

## Memory Management

Some methods return dynamically allocated arrays.

The method:

```cpp
Player* formGroup(int groupSize, int delta, int* n);
```

returns a dynamically allocated array when a group is successfully formed.

The method:

```cpp
Player* getWaitingPlayers(int* n);
```

also returns a dynamically allocated array containing copies of the current waiting players.

In both cases, the caller is responsible for freeing the allocated memory using:

```cpp
delete[] array;
```

## Restrictions

This project follows the restrictions defined in the assignment:

- the system must be implemented in C++;
- the code must use classes and modularization;
- players must be stored in a static array;
- `std::sort` is not allowed;
- STL data structures such as `vector`, `list`, `map`, `queue`, and `stack` are not allowed;
- `std::string` is allowed;
- `<chrono>` may be used for performance tests;
- insertion sort and merge sort must be implemented manually.

## Performance Tests

The assignment also requires a brief comparison between insertion sort and merge sort.

The performance tests should measure the execution time of both sorting algorithms for different input sizes.

The expected theoretical complexities are:

- insertion sort: `O(n²)` in the worst case;
- merge sort: `O(n log n)` in the worst case.

The measured times should be presented and discussed in the project report.
