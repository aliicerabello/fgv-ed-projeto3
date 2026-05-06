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

bool Matchmaking::comesBefore(Player p1, Player p2){
    if (p1.getScore() > p2.getScore())
        return false;

    if (p1.getScore() < p2.getScore())
        return true;

    if (p1.getTimestamp() < p2.getTimestamp())
        return true;

    return false;
}

void Matchmaking::sortByScoreInsertion(){
    for (int i = 1; i < size; i++){
        Player key = players[i];
        int j = i - 1;


        while (j >= 0 && comesBefore(key, players[j])){
            players[j + 1] = players[j];
            j--;
        }

        players[j + 1] = key;
    }
}

void Matchmaking::mergeSort(Player players_[MAX_PLAYERS], int first, int middle, int last){
    int i = first;
    int k = first;
    int j = middle +1;
    
    Player* aux_players = new Player[MAX_PLAYERS];
    
    while(i <= middle && j <= last){
        if(comesBefore(players_[i], players_[j])){
            aux_players[k] = players_[i];
            i++;
        }
        else{
            aux_players[k] = players_[j];
            j++;
        }
        k++;
    }

    while (i <= middle){
        aux_players[k] = players_[i];
        i++; k++;
    }

    while (j <= last){
        aux_players[k] = players_[j];
        j++; k++;
    }

    for(int n = first; n <= last; n++)
        players_[n] = aux_players[n];

    delete[] aux_players;
}

void Matchmaking::divideMerge(Player players_[MAX_PLAYERS], int first, int last){
    if(first >= last)
        return;
        
    int middle = (first + last)/2;
    divideMerge(players_, first, middle);
    divideMerge(players_, middle+1, last);

    mergeSort(players_, first, middle, last);
}

void Matchmaking::sortByScoreMerge(){
    if(size <= 1)
        return; 

    divideMerge(players, 0, size-1);    
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