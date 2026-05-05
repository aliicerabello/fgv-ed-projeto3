#include "Matchmaking.hpp"
#include "Player.hpp"
#include <iostream>

using namespace std;

Matchmaking::Matchmaking(){
    int size = 0;
    /* dúvida: inicializar uma nova lista
    para ser ordenada aqui?*/
}

Matchmaking::~Matchmaking(){
}

bool Matchmaking::insert(Player player_){
    if(size == MAX_PLAYERS)
        return false;

    players[size] = player_; size++; 
    return true;
}

bool Matchmaking::removePlayer(int id_){
    int id_remove = -1;

    for(int i = 0; i < size; i++){
        if(id_ == players[i].getId()){
            id_remove = i;
            break;
        }
    }

    if (id_remove == -1){
        return false;
    }

    for (int j = id_remove; j < size - 1; j++){
        players[j] = players[j+1];
    }
    
    size--;
    return false;  

}

void Matchmaking::sortByScoreInsertion(){

}

void Matchmaking::sortByScoreMerge(){

}

Player* Matchmaking::formGroup(int groupSize, int delta, int* n){
    // n indica se o grupo tem 0 ou groupsize players
    int index = -1;
    for (int i = 0; i < *n; i ++){
        if (players[i + groupSize - 1].getScore() - players[i].getScore() <= delta){
            index = i;
            break;
        }

    if (index == -1){
        *n = 0;
        return nullptr;
    }

    
    
    }
}