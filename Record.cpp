#include "Record.h"

Record::Record(){}

void Record::savePlayer(Player* thePlayer, ofstream& file_output){
    file_output << thePlayer->getName() << ' '
                << thePlayer->getTag() << endl;
    file_output << thePlayer->getMaxHealth() << ' ' 
                << thePlayer->getCurrentHealth() << ' '
                << thePlayer->getAttack() << ' ' 
                << thePlayer->getDefense() << ' '
                << thePlayer->getHunger() << ' ' 
                << thePlayer->getThirst() << ' ' 
                << thePlayer->getPoison() << endl;
    file_output << thePlayer->getCanCommunicate() << ' '
                << thePlayer->getCanAttack() << ' '
                << thePlayer->getCanGetFoodEnvironment() << ' '
                << thePlayer->getCanGetPoisonEnvironment() << endl;
    
    Room* cur = thePlayer->getCurrentRoom();
    Room* prv = thePlayer->getPreviousRoom();

    file_output << cur->getIndex() << ' '
                << prv->getIndex() << endl;

    vector<Item> theInventory = (*thePlayer).getInventory();
    file_output << theInventory.size() << endl;
    for(auto i: theInventory){
        file_output << i.getName() << ' ' << i.getTag() << endl;
        file_output << i.getType() << ' '
                    << i.getHealth() << ' '
                    << i.getAttack() << ' '
                    << i.getDefense() << ' '
                    << i.getHunger() << ' ' 
                    << i.getThirst() << ' ' 
                    << i.getPoison() << endl;
    }
}

void Record::loadPlayer(Player* thePlayer, ifstream& file_input, vector<Room>& rooms){
    string theName, theTag;
    file_input >> theName >> theTag;

    int theMaxHealth, theCurrentHealth, theAttack, theDefense, theHunger, theThirst, thePoison;
    file_input >> theMaxHealth >> theCurrentHealth >> theAttack >> theDefense >> theHunger >> theThirst >> thePoison;
    *thePlayer = *(new Player(theName, theCurrentHealth, theAttack, theDefense, theHunger, theThirst, thePoison));
    thePlayer->setMaxHealth(theMaxHealth);

    bool theCanCommunicate, theCanAttack, theCanGetFoodEnvironment, theCanGetPoisonEnvironment;
    file_input >> theCanCommunicate >> theCanAttack >> theCanGetFoodEnvironment >> theCanGetPoisonEnvironment;
    thePlayer->setCanCommunicate(theCanCommunicate);
    thePlayer->setCanAttack(theCanAttack);
    thePlayer->setCanGetFoodEnvironment(theCanGetFoodEnvironment);
    thePlayer->setCanGetPoisonEnvironment(theCanGetPoisonEnvironment);

    int curRoomIndex, prvRoomIndex;
    file_input >> curRoomIndex >>prvRoomIndex;
    //setRoom
    thePlayer->setCurrentRoom(&rooms[curRoomIndex]);
    thePlayer->setPreviousRoom(&rooms[prvRoomIndex]);

    vector<Item> theInventory;
    int count; 
    string theType;
    file_input >> count;
    for(int i=0; i<count; i++){
        file_input >> theName >> theTag;
        file_input >> theType;
        file_input >> theCurrentHealth >> theAttack >> theDefense >> theHunger >> theThirst >> thePoison;
        theInventory.push_back(Item(theName, theType, theCurrentHealth, theAttack, theDefense, theHunger, theThirst, thePoison));
    }
    thePlayer->setInventory(theInventory);
}

void Record::saveRooms(vector<Room>& v, ofstream& file_output){
    file_output << v.size() << endl;
    for(auto i: v){
        file_output << i.getRoomType() << endl;
        file_output << i.getIsExit() << endl;
        file_output << (i.getUpRoom() == NULL ? -1 : (*(i.getUpRoom())).getIndex()) << ' ';
        file_output << (i.getDownRoom() == NULL ? -1 : (*(i.getDownRoom())).getIndex()) << ' ';
        file_output << (i.getLeftRoom() == NULL ? -1 : (*(i.getLeftRoom())).getIndex()) << ' ';
        file_output << (i.getRightRoom() == NULL ? -1 : (*(i.getRightRoom())).getIndex()) << endl;
        
        vector<Object*> theObjects = i.getObjects();
        Object* tmp;
        file_output << theObjects.size() << endl;
        for(auto j: theObjects){
            tmp = j;
            file_output << j->getName() << ' ' << j->getTag() << endl;
            if(j->getTag() == "NPC"){
                NPC* NPCInRoom = dynamic_cast<NPC*>(tmp);
                file_output << NPCInRoom->getScript() << endl;
                file_output << NPCInRoom->getCommodity().size() << endl;
                for(auto k: NPCInRoom->getCommodity()){
                    file_output << k.getName() << ' ' << k.getTag() << endl;
                    file_output << k.getType() << ' '
                                << k.getHealth() << ' '
                                << k.getAttack() << ' '
                                << k.getDefense() << ' '
                                << k.getHunger() << ' ' 
                                << k.getThirst() << ' ' 
                                << k.getPoison() << endl;                    
                }
            }
            else if(j->getTag() == "Monster"){
                Monster* MonsterInRoom = dynamic_cast<Monster*>(tmp);
                file_output << MonsterInRoom->getMaxHealth() << ' '
                            << MonsterInRoom->getCurrentHealth() << ' '
                            << MonsterInRoom->getAttack() << ' '
                            << MonsterInRoom->getDefense() << endl;
            }
        }
    }
}

void Record::loadRooms(vector<Room>& v, ifstream& file_input){
    int roomCount;
    file_input >> roomCount;
    for(int i=0; i<roomCount; i++){
        v.push_back(Room());
        v[i].setIndex(i);
    }
    for(int i=0; i<roomCount; i++){
        int isExit;
        string theRoomType;
        file_input >> theRoomType;
        v[i].setRoomType(theRoomType);
        file_input >> isExit;
        v[i].setIsExit((isExit == 1 ? true : false));

        int theUp, theDown, theLeft, theRight;
        file_input >> theUp >> theDown >> theLeft >> theRight;
        if(theUp != -1) v[i].setUpRoom(&v[theUp]);
        if(theDown != -1) v[i].setDownRoom(&v[theDown]);
        if(theLeft != -1) v[i].setLeftRoom(&v[theLeft]);
        if(theRight != -1) v[i].setRightRoom(&v[theRight]);

        int objectCount;
        file_input >> objectCount;
        vector<Object*> objs; 
        objs.clear();
        while(objectCount--){
            string theName, theTag;
            file_input >> theName >> theTag;

            if(theTag == "NPC"){
                file_input.ignore();
                string theScript;
                getline(file_input, theScript);
                int NpcItemCount;
                file_input >> NpcItemCount;

                vector<Item> theCommodity;
                theCommodity.clear();
                for(int j=0; j<NpcItemCount; j++){
                    string theItemName, theItemTag, theItemType;
                    int theItemHealth, theItemAttack, theItemDefense, theItemHunger, theItemThirst, theItemPoison;
                    file_input >> theItemName >> theItemTag >> theItemType;
                    file_input >> theItemHealth >> theItemAttack >> theItemDefense >> theItemHunger >> theItemThirst >> theItemPoison;
                    theCommodity.push_back(Item(theItemName, theItemType, theItemHealth, theItemAttack, theItemDefense, theItemHunger, theItemThirst, theItemPoison));
                }
                objs.push_back(new NPC(theName, theScript, theCommodity));
            }
            if(theTag == "Monster"){
                int theMaxHealth, theCurrentHealth, theAttack , theDefense;
                file_input >> theMaxHealth >> theCurrentHealth >> theAttack >> theDefense;
                objs.push_back(new Monster(theName, theCurrentHealth, theAttack, theDefense));
                Monster* tmp = dynamic_cast<Monster*>(objs.back());
                (*tmp).setMaxHealth(theMaxHealth);
            }
        }
        v[i].setObjects(objs);
    }
}

void Record::loadFromFile(string& theName, Player* thePlayer, vector<Room>& v){
    std::ifstream file_input;
    
    cout << "Loading..." << endl; 
    std::this_thread::sleep_for(std::chrono::seconds(1)); 
    file_input.open(theName + "_map.txt");
    loadRooms(v, file_input);
    file_input.close();
    std::this_thread::sleep_for(std::chrono::seconds(1)); 

    cout << "Loading..." << endl; 
    std::this_thread::sleep_for(std::chrono::seconds(1)); 
    file_input.open(theName + "_player.txt");
    loadPlayer(thePlayer, file_input, v);
    file_input.close();
    std::this_thread::sleep_for(std::chrono::seconds(1)); 

    cout << "Finished" << endl;
}

void Record::saveToFile(Player* thePlayer, vector<Room>& v){
    string theName = (*thePlayer).getName();
    std::ofstream file_output;

    file_output.open(theName + "_map.txt");
    this->saveRooms(v, file_output);
    file_output.close();

    file_output.open(theName + "_player.txt");
    this->savePlayer(thePlayer, file_output);
    file_output.close();

    cout << "Saving the record..." << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1)); 
    cout << "Finished" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1)); 
}

bool Record::checkFile(string theName){
    std::ifstream file_input;

    string fileName = theName + "_player.txt";
    file_input.open(fileName);
    if(!file_input.good()) return false;
    file_input.close();

    fileName = theName + "_map.txt";
    file_input.open(fileName);
    if(!file_input.good()) return false;
    file_input.close();

    return true;
}

void Record::deleteFile(string playerName) {
        // Delete map file
        string mapFileName = playerName + "_map.txt";
        if (remove(mapFileName.c_str()) != 0) {
            //cout << "Error deleting map file: " << mapFileName << std::endl;
        } else {
            //cout << "Map file deleted: " << mapFileName << std::endl;
        }

        // Delete player file
        string playerFileName = playerName + "_player.txt";
        if (remove(playerFileName.c_str()) != 0) {
            //cout << "Error deleting player file: " << playerFileName << std::endl;
        } else {
            //cout << "Player file deleted: " << playerFileName << std::endl;
        }
    }