#include "Object.h"

Object::Object(){
    this->name = "NULL";
	this->tag = "NULL";
}


Object::Object(string theName, string theTag){
    this->name = theName;
	this->tag= theTag;
}

void Object::setName(string theName){
	this->name = theName;
}

void Object::setTag(string theTag){
	this->tag = theTag;
}

string Object::getName(){
	return this->name;
}

string Object::getTag(){
	return this->tag;
}