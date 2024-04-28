#include "Room.h"

Room::Room() {
    isExit = false;
    upRoom = NULL;
    downRoom = NULL;
    leftRoom = NULL;
    rightRoom = NULL;
    objects.clear();
    index = -1;
}
Room::Room(bool theIsExit, int theIndex, vector<Object*> objs){
    upRoom = NULL;
    downRoom = NULL;
    leftRoom = NULL;
    rightRoom = NULL;
    this->isExit = theIsExit;
    this->index = theIndex;
    this->objects = objs;
}

//popObject
bool Room::popObject(Object* obj){
    for(auto i=objects.begin();i!=objects.end(); i++){
        if(*i == obj){
            objects.erase(i);
            return true;
        }
    }
    return false;
}

void Room::pushObject(Object* obj) {
	(this->objects).push_back(obj);
}

void Room::setUpRoom(Room* r){
    this->upRoom = r;
}

void Room::setDownRoom(Room* r){
    this->downRoom = r;
}

void Room::setLeftRoom(Room* r){
    this->leftRoom = r;
}

void Room::setRightRoom(Room* r){
    this->rightRoom = r;
}

void Room::setIsExit(bool theIsExit){
    this->isExit = theIsExit;
}

void Room::setIndex(int theIndex){
    this->index = theIndex;
}

void Room::setObjects(vector<Object*> objs){
    this->objects = objs;
}

void Room::setRoomType(string theRoomType){
    this->RoomType = theRoomType;
}

bool Room::getIsExit(){
    return this->isExit;
}

int Room::getIndex(){
    return this->index;  
}

vector<Object*> Room::getObjects(){
    return this->objects;
}

Room* Room::getUpRoom(){
    return this->upRoom;
}

Room* Room::getDownRoom(){
    return this->downRoom;
}

Room* Room::getLeftRoom(){
    return this->leftRoom;
}

Room* Room::getRightRoom(){
    return this->rightRoom;
}

string Room::getRoomType(){
    return this->RoomType;
}

