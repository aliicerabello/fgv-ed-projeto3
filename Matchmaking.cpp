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

void Matchmaking::sortByScoreInsertion(){

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
    cout << "Waiting Player" << endl;
    if (size == 0){
        cout << "(empty)" << endl;
    }
}