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
    for(int i = 0; i < size; i++){
        if(id_ == players[i].getId()){
            /*lógica de remoção*/
            return true;
        }
    }
    return false;  
}