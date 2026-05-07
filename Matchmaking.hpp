#ifndef MATCHMAKING_HPP
#define MATCHMAKING_HPP

#include "Player.hpp"

const int MAX_PLAYERS = 100000;

class Matchmaking {

private:

    Player players[MAX_PLAYERS];
    int size;

public:

    Matchmaking();
    ~Matchmaking();

    bool insert(Player player);    
    bool removePlayer(int id);

    void sortByScoreInsertion();
    bool comesBefore(Player p1, Player p2);
    
    void mergeSort(Player players_[MAX_PLAYERS], int first, int middle, int last);
    void divideMerge(Player players_[MAX_PLAYERS], int first, int last);
    void sortByScoreMerge();
    
    Player* formGroup(int groupSize, int delta, int* n);
    void printGroup(Player* group, int n);

    Player* getWaitingPlayers(int* n);

    void printWaitingPlayers();
};

#endif
