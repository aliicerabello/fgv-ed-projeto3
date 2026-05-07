#include "Player.hpp"

//constructor
Player::Player(){

}

Player::Player(int id_, std::string name_, int score_, int timestamp_){
    this->id = id_;
    this->name = name_;
    this->score = score_;
    this->timestamp = timestamp_;
}

//destructor
Player::~Player(){
}

int Player::getId(){
    return id;
}

std::string Player::getName(){
    return name;
}

int Player::getScore(){
    return score;
}

int Player::getTimestamp(){
    return timestamp;
}                      