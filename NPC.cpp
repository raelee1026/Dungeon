#include "NPC.h"

NPC::NPC() :GameCharacter("", "NPC", 0, 0, 0){}

NPC::NPC(string theName, string theScript, vector<Item> v): GameCharacter(theName, "NPC", 0, 0, 0) {
	this->script = theScript;
	this->commodity = v;
}

void NPC::listCommodity(){
    cout << "Number of Items(s): " << commodity.size() << endl;
    for(auto i: commodity){
        cout << i.getType() << ": " << i.getName() << endl;
    }
}

//deal with transaction
bool NPC::triggerEvent(Object* obj){
    Player* player = dynamic_cast<Player*>(obj);
    if(player == NULL) return false;

    vector<Item> tmp;
    vector<Item> list = commodity;
    for(int i=0; i<list.size(); i++){
        cout << i << ". " << list[i].getName();
        if(list[i].getType() == "Weapon"){
            cout << " HP:" << list[i].getHealth() << " Attack:" << list[i].getAttack() << " Defense:" << list[i].getDefense() << endl;
        } 
        else{
            cout << " Hunger:" << list[i].getHunger() << " Thirst:" << list[i].getThirst() << endl;
        }
    }
    cout << "Enter the item number you want(You can only pick one item): ";
    int theItemNumber; 
    cin >> theItemNumber;
    tmp.clear();
    bool picked = false;
    for(int i=0; i<list.size(); i++){
        if(i == theItemNumber){
            cout << "You picked up " << list[i].getName() << endl;
            player->addItem(list[i]);
            picked = true;
        }
        else{
            tmp.push_back(list[i]);
        }
    }
    if(picked){
        this->setCommodity(tmp);
        return(this->commodity.size() == 0);
    }
    cout << "There is no Item number " << theItemNumber << " for you to pick." << endl;
    return false;
}

void NPC::setScript(string theScript){
	this->script = theScript;
}

void NPC::setCommodity(vector<Item> v){
	this->commodity = v;
}

string NPC::getScript(){
	return this->script;
}

vector<Item> NPC::getCommodity(){
	return this->commodity;
}
