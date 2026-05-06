#include "Matchmaking.hpp"
#include "Player.hpp"
#include <iostream>

using namespace std;

Matchmaking::Matchmaking(){
    size = 0;
}

Matchmaking::~Matchmaking(){
}

bool Matchmaking::insert(Player player_){
    if(size == MAX_PLAYERS)
        return false;

    players[size] = player_; 
    size++; return true;
}

bool Matchmaking::removePlayer(int id_){
    int id_remove = -1;

    for(int i = 0; i < size; i++){
        if(id_ == players[i].getId()){
            id_remove = i;
            break;
        }
    }

    if(id_remove == -1)
        return false;
    
    for(int j = id_remove; j < size-1; j++) 
        players[j] = players[j+1];
    
    size--; return true;
}

bool Matchmaking::shouldComeFirst(Player p1, Player p2){
    if (p1.getScore() > p2.getScore()){
        return false;
    }

    if (p1.getScore() < p2.getScore()){
        return true;
    }

    if (p1.getTimestamp() < p2.getTimestamp()){
        return true;
    }

    return false;
}


void Matchmaking::sortByScoreInsertion(){
    for (int i = 1; i < size; i++){
        Player key = players[i];
        int j = i - 1;


        while (j >= 0 && shouldComeFirst(key, players[j])){
            players[j + 1] = players[j];
            j--;
        }

        players[j + 1] = key;

        }
    }

void Matchmaking::sortByScoreMerge(){
    
}

Player* Matchmaking::formGroup(int groupSize, int delta, int* n){
    if (groupSize <= 0 || groupSize > size) {
    *n = 0;
    return nullptr;
    }

    int index = -1;

    for (int i = 0; i <= size - groupSize; i ++){
        if (players[i + groupSize - 1].getScore() - players[i].getScore() <= delta){
            index = i;
            break;
        }
    }

    if (index == -1){
            *n = 0;
            return nullptr;
        }

    Player* group = new Player[groupSize];
    *n = groupSize;
        
    //copiar o grupo válido
    for (int j = 0; j < groupSize; j++){
        group[j] = players[index + j];
    }

    //retirar o grupo de players
    int k = 0;
    while (index + groupSize + k < size){
        players[index + k] = players[index + groupSize+ k];
        k++;
    }
    size -= groupSize;
    return group;

}

void Matchmaking::printGroup(Player* group, int n) {
    if (group == nullptr || n == 0) {
        cout << "Group: nullptr" << endl;
        return;
    }

    cout << "Group:" << endl;

    for (int i = 0; i < n; i++) {
        cout << "["
             << group[i].getId() << " | "
             << group[i].getName() << " | "
             << group[i].getScore() << " | "
             << group[i].getTimestamp()
             << "]" << endl;
    }
}


Player* Matchmaking::getWaitingPlayers(int* n){
    if (size == 0){
        *n = 0;
        return nullptr;
    }

    Player* waiting = new Player[size];

    for (int i = 0; i < size; i++){
        waiting[i] = players[i];
    }

    *n = size;
    return waiting;
} //lembrar de fazer o delete na main!!!


void Matchmaking::printWaitingPlayers(){
    cout << "Waiting Players:" << endl;

    if (size == 0){
        cout << "(empty)" << endl;
        return;
    }

    for (int i = 0; i < size; i++){
        cout << "["
             << players[i].getId() << " | "
             << players[i].getName() << " | "
             << players[i].getScore() << " | "
             << players[i].getTimestamp()
             << "]" << endl;
    }

}