#include "Player.h"

Player::Player(){}

/*
Player::Player(string theName, int theHealth, int theAttack, int theDefense) :GameCharacter(theName, "Player", theHealth, theAttack, theDefense){
    this->currentRoom = NULL;
    this->previousRoom = NULL;
}*/

Player::Player(string theName, int theHealth, int theAttack, int theDefense, int theHunger, int theThirst, int thePoison) :GameCharacter(theName, "Player", theHealth, theAttack, theDefense, theHunger, theThirst, thePoison){
    this->currentRoom = NULL;
    this->previousRoom = NULL;
}

void Player::addItem(Item theItem){
    this->increaseStates(theItem.getHealth(), theItem.getAttack(), theItem.getDefense(), theItem.getHunger(), theItem.getThirst(), theItem.getPoison());
    this->inventory.push_back(theItem);
}

void Player::increaseStates(int theHealth, int theAttack, int theDefense, int theHunger, int theThirst, int thePoison){
	this->setCurrentHealth(min(getCurrentHealth()+theHealth, getMaxHealth()));
	this->setAttack(getAttack() + theAttack);
	this->setDefense(getDefense() + theDefense);
    this->setHunger(getHunger() + theHunger);
    this->setThirst(getThirst() + theThirst);
    this->setPoison(getPoison() + thePoison);

}

void Player::changeRoom(Room* now){
	this->previousRoom = this->currentRoom;
	this->currentRoom = now;
}

//show the status of player
bool Player::triggerEvent(Object* objs){
	cout << "show the status of player" << endl;
    return false;
}

void Player::setCurrentRoom(Room* now){
	this->setPreviousRoom(this->currentRoom);
	this->currentRoom = now;
}

void Player::setPreviousRoom(Room* theRoom){
    this->previousRoom = theRoom;
}

void Player::setInventory(vector<Item> v){
    for(auto i: v){
        i.triggerEvent(this);
    }
    this->inventory = v;
}

Room* Player::getCurrentRoom(){
    return this->currentRoom;
}

Room* Player::getPreviousRoom(){
    return this->previousRoom;
}

vector<Item> Player::getInventory(){
    return this->inventory;
}

void Player::setCanCommunicate(bool k){
    this->canCommunicate = k;
}

bool Player::getCanCommunicate(){
    return this->canCommunicate;
}

void Player::setCanAttack(bool k){
    this->canAttack = k;
}

bool Player::getCanAttack(){
    return this->canAttack;
}

void Player::setCanGetFoodEnvironment(bool k){
    this->canGetFoodEnvironment = k;
}

bool Player::getCanGetFoodEnvironment(){
    return this->canGetFoodEnvironment;
}

void Player::setCanGetPoisonEnvironment(bool k){
    this->canGetPoisonEnvironment = k;
}

bool Player::getCanGetPoisonEnvironment(){
    return this->canGetPoisonEnvironment;
}
