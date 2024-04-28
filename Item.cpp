#include "Item.h"

Item::Item() :Object(){}

/*
Item::Item(string theName, int theHealth, int theAttack, int theDefense) :Object(theName, "Item"){
    this->health = theHealth;
    this->attack = theAttack;
    this->defense = theDefense;
}*/

Item::Item(string theName, string theType, int theHealth, int theAttack, int theDefense, int theHunger, int theThirst, int thePoison) :Object(theName, "Item"){
    this->health = theHealth;
    this->attack = theAttack;
    this->defense = theDefense;
    this->hunger = theHunger;
    this->thirst = theThirst;
    this->poison = thePoison;
    this->type = theType;
}

//player picks up Item
bool Item::triggerEvent(Object* obj){
    Player *player = dynamic_cast<Player*>(obj);
    if(player == NULL) return false;
    player->addItem(*this);
    return true;
}

int Item::getHealth(){
    return this->health;
}

int Item::getAttack(){
    return this->attack;
}

int Item::getDefense(){
    return this->defense;
}

int Item::getHunger(){
    return this->hunger;
}

int Item::getThirst(){
    return this->thirst;
}

int Item::getPoison(){
    return this->poison;
}

string Item::getType(){
    return this->type;
}

void Item::setHealth(int theHealth){
    this->health = theHealth;
}

void Item::setAttack(int theAttack){
    this->attack = theAttack;
}

void Item::setDefense(int theDefense){
    this->defense = theDefense;
}

void Item::setHunger(int theHunger){
    this->hunger = theHunger;
}

void Item::setThirst(int theThirst){
    this->thirst = theThirst;
}

void Item::setPoison(int thePoison){
    this->poison = thePoison;
}

void Item::setType(string theType){
    this->type = theType;
}
