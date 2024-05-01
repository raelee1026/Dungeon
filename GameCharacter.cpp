#include "GameCharacter.h"

GameCharacter::GameCharacter() :Object(){}

GameCharacter::GameCharacter(string theName, string theTag, int theHealth, int theAttack, int theDefense) :Object(theName, theTag){
	this->name = theName;
	this->maxHealth = theHealth;
	this->currentHealth = theHealth;
	this->attack = theAttack;
	this->defense = theDefense;
}

GameCharacter::GameCharacter(string theName, string theTag, int theHealth, int theAttack, int theDefense, int theHunger, int theThirst, int thePoison) :Object(theName, theTag){
	this->name = theName;
	this->maxHealth = theHealth;
	this->currentHealth = theHealth;
	this->attack = theAttack;
	this->defense = theDefense;
	this->hunger = theHunger;
	this->thirst = theThirst;
	this->poison = thePoison;
}

bool GameCharacter::checkIsDead(){
	return (this->currentHealth <= 0);
}

int GameCharacter::takeDamage(int t){
	int damageCause;
	//cout << "deal with takeDamage" << endl;
	damageCause = t - defense; 
	if(damageCause < 0){
		damageCause = 0;
	}
	this->currentHealth -= damageCause;
	return damageCause;
}

void GameCharacter::setMaxHealth(int theHealth){
	this->maxHealth = theHealth;
}

void GameCharacter::setCurrentHealth(int theHealth){
	this->currentHealth = min(theHealth, this->maxHealth);
}

void GameCharacter::setAttack(int theAttack){
	this->attack = theAttack;
}

void GameCharacter::setDefense(int theDefense){
	this->defense = theDefense;
}

void GameCharacter::setHunger(int theHunger){
	this->hunger = min(max(theHunger, 0), 200);
}

void GameCharacter::setThirst(int theThirst){
	this->thirst = min(max(theThirst, 0), 200);
}

void GameCharacter::setPoison(int thePoison){
	this->poison = max(thePoison, 0);
}

int GameCharacter::getMaxHealth(){
	return this->maxHealth;
}

int GameCharacter::getCurrentHealth(){
	return this->currentHealth;
}

int GameCharacter::getAttack(){
	return this->attack;
}

int GameCharacter::getDefense(){
	return this->defense;
}

int GameCharacter::getHunger(){
	return this->hunger;
}

int GameCharacter::getThirst(){
	return this->thirst;
}

int GameCharacter::getPoison(){
	return this->poison;
}