#include "Dungeon.h"

Dungeon::Dungeon(){}

void Dungeon::createPlayer(string& theName){
    this->player = Player(theName, 100, 10, 0, 100, 100, 0);
    this->player.setCurrentRoom(&rooms[0]);
    this->player.setPreviousRoom(&rooms[0]);
}

void Dungeon::createMap(){
    ifstream file_input;
    file_input.open("map.txt");
    if(!file_input.good()){
        cout << "Map file loads failed" << endl;
        exit(0);
    }

    int RoomNumber;
    file_input >> RoomNumber;
    for(int i=0; i<RoomNumber; i++){
        rooms.push_back(Room());
        rooms[i].setIndex(i); 
    }
    int x;
    string roomType;
    for(int i=0; i<RoomNumber; i++){
        file_input >> roomType;
        rooms[i].setRoomType(roomType);
        file_input >> x;
        if(x != -1){
            rooms[i].setUpRoom(&rooms[x]);
        }
        file_input >> x;
        if(x != -1){
            rooms[i].setDownRoom(&rooms[x]);
        }
        file_input >> x;
        if(x != -1){
            rooms[i].setLeftRoom(&rooms[x]);
        }
        file_input >> x;
        if(x != -1){
            rooms[i].setRightRoom(&rooms[x]);
        }
    }
    file_input.close();

    rooms[RoomNumber-1].setIsExit(true);

    //set NPCs in the rooms
    file_input.open("NPC.txt");
    if(!file_input.good()){
        cout << "NPC file loads failed" << endl;
        exit(0);
    }
    int NpcNumber;
    file_input >> NpcNumber;

    NPC* tmpNpc;
    int NpcInRoom;
    string NpcName, NpcScript;
    vector<Item> NpcCommodity;
    int ItemNumber;
    string ItemName, ItemType;
    int theHealth, theAttack, theDefense, theHunger, theThirst, thePoison;
    for(int i=0; i<NpcNumber; i++){
        file_input >> NpcInRoom;
        file_input >> NpcName;
        file_input.ignore();
		getline(file_input, NpcScript);
        
        file_input >> ItemNumber;
        NpcCommodity.clear();
        for(int j=0; j<ItemNumber; j++){
            file_input >> ItemName;
            //file_input.ignore();
            file_input >> ItemType >> theHealth>> theAttack >> theDefense >> theHunger >> theThirst >> thePoison;
            //cout << ItemType;
            NpcCommodity.push_back(Item(ItemName, ItemType, theHealth, theAttack, theDefense, theHunger, theThirst, thePoison));
        }
        tmpNpc = new NPC(NpcName, NpcScript, NpcCommodity);
        rooms[NpcInRoom].pushObject(tmpNpc);
    }
    file_input.close();

    //set up monsters
    file_input.open("Monster.txt");
    if(!file_input.good()){
        cout << "Monster file loads failed" << endl;
        exit(0);
    }
    int MonsterNumber;
    file_input >> MonsterNumber;
    
    Monster* tmpMonster;
    int MonsterInRoom;
    string MonsterName;
    for(int i=0; i<MonsterNumber; i++){
        file_input >> MonsterInRoom;
        file_input >> MonsterName;
        file_input >> theHealth >> theAttack >> theDefense;
        tmpMonster = new Monster(MonsterName, theHealth, theAttack, theDefense);
        rooms[MonsterInRoom].pushObject(tmpMonster);
    }
    file_input.close();
}

void Dungeon::handleMovement(){
    Room* current = player.getCurrentRoom();
    Room* previous = player.getPreviousRoom();
    
    Room* up = (*current).getUpRoom();
    Room* down = (*current).getDownRoom();
    Room* left = (*current).getLeftRoom();
    Room* right = (*current).getRightRoom();

    if (up != NULL) cout << "U(u): Go up room" << endl;
	if (down != NULL) cout << "D(d): Go down room" << endl;
	if (left != NULL) cout << "L(l): Go left room" << endl;
	if (right != NULL) cout << "R(r): Go right room" << endl;
    cout << "Enter your movement: ";
    
    string movement;
    cin >> movement;
    movement[0] = tolower(movement[0]);
    if(movement == "u" && up != NULL) player.setCurrentRoom(up);
    else if(movement == "d" && down != NULL) player.setCurrentRoom(down);
    else if(movement == "l" && left != NULL) player.setCurrentRoom(left);
    else if(movement == "r" && right != NULL) player.setCurrentRoom(right);
    else{
        cout << "You can't do this!" << endl;
    }
}


void Dungeon::startGame(){
    string player_name;
    bool canStart = false;
    Record record;

    cout << "Welcome to Dungeon!" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1)); 
    while(!canStart){
        cout << "Enter your name: ";
        cin >> player_name;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if(record.checkFile(player_name)){
            string operation;
            cout << "Found previous records." << endl;
            cout << "Do you want to continue?(Enter y for yes, n for no):";
            cin >> operation;
            if(operation == "y"){
                record.loadFromFile(player_name, &player, rooms);
                std::this_thread::sleep_for(std::chrono::seconds(1));
                cout << "Hello! " << player_name << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                canStart = true;
            }
            else if(operation == "n"){
                cout << "You have to change a name!" << endl;
            }
        }
        else{
            cout << "Hello! " << player_name << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            this->createMap();
            this->createPlayer(player_name);
            canStart = true;
        }
    }
    this->runDungeon();
    /*
    cout << "Enter your name: ";
    cin >> player_name;
    std::this_thread::sleep_for(std::chrono::seconds(1)); 
    cout << "Hello! " << player_name << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1)); 

    this->createMap();
    this->createPlayer(player_name);
    this->runDungeon();
    */
}

bool Dungeon::checkGameLogic(){
    if((this->player).checkIsDead()){
        cout << "----------------------------------------" << endl;
        cout << "You don't have HP" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
        cout << "Game Over!" << endl;
        cout << "Game Over!!" << endl;
        cout << "Game Over!!!" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
        exit(0);
        //return false;
    }
    return true;
}

bool Dungeon::isOperation(string& s){
    if(s.length() != 1) return false;

    if(s == "e") return true;
    if(s == "s") return true;
	if(s == "o") return true;
	if(s == "m") return true;
	if(s == "c" && player.getCanCommunicate()) return true;
    if (s == "a" && player.getCanAttack()) return true;

    return false;
}


void Dungeon::handleHungerSystem(){
    cout << "----------------------------------------" << endl;
    player.setHunger(player.getHunger() - 5);
    cout << "You are hungry, so your hunger decreases 5." << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    player.setThirst(player.getThirst() - 5);
    cout << "You are thirsty, so your thirst decreases 5." << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1)); 
    if(player.getHunger() == 0){
        cout << "----------------------------------------" << endl;
        cout << "Your hunger is 0!"<< endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
        cout << "Because you are too hungry, it's very unhealthy." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
        cout <<"So your HP decreased by 10." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        player.setCurrentHealth(player.getCurrentHealth()-10);
    }
    if(player.getThirst() == 0){
        cout << "----------------------------------------" << endl;
        cout << "Your thirst is 0!"<< endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
        cout << "Because you are too thirsty, it's very unhealthy." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
        cout <<"So your HP decreased by 10." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        player.setCurrentHealth(player.getCurrentHealth()-10);
    }
    if(player.getPoison() != 0){
        cout << "----------------------------------------" << endl;
        cout << "Your poison is NOT 0!"<< endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
        cout << "Because you are still poisoned right now." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cout << "It really affects your health." << endl; 
        std::this_thread::sleep_for(std::chrono::seconds(1));  
        cout <<"So your HP decreased by 10." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        player.setCurrentHealth(player.getCurrentHealth()-10);
        cout << "----------------------------------------" << endl;
        cout << "As time goes by, your poison decreases by 10." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        player.setPoison(player.getPoison()-10);
        cout << "You gradually become less poisoned." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Dungeon::handleRoomSystem(){
    //room system design
        srand(time(NULL));
        int possibility = rand() % 10; //from 0~9
        //cout << possibility;
        if(player.getCurrentRoom()->getRoomType() == "desert"){
            cout << "----------------------------------------" << endl;
            cout << "You are in the desert right now." << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if(possibility>=6){  //from6~9 sandstorm
                cout << "OOPS! You're in a sandstorm." << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                cout << "It's really dangerous!" << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                cout << "And you can't find any water" << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                cout << "You are very thirsty, so you're thirst reduced by 20." << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                player.setThirst(player.getThirst()-20);
            }
            else if(possibility<=5 && possibility>=2){  //from2~5 just desert
                cout << "The desert is very hot." << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                cout << "You can't find any water." << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                cout << "You are thirsty, so your thirst reduced by 10." << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                player.setThirst(player.getThirst()-10);
            }
            else{  //from0~2 oasis
                cout << "WOW! You find an oasis!" << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                cout << "You can drink as much water as you want!" << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                cout << "You aren't thirsty anymore, so your thirst increased by 50." << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                player.setThirst(player.getThirst()+50);
                
            }
        }

        if(player.getCurrentRoom()->getRoomType() == "forest"){
            cout << "----------------------------------------" << endl;
            cout << "You are in the forest right now." << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            cout << "OOPS! You can't find any food in the forest." << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            cout << "You are very hungry, so your hunger decreases 20." << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            player.setHunger(player.getHunger()-20);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if(possibility >= 0 && possibility <= 4){
                cout << "The forest is very dangerous." << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                cout << "There are many formidable predators." << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                if(possibility >= 0 && possibility <= 2){
                    cout << "A tiger is chasing you!!!" << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    cout << "Keep running!!!" << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    cout << "Run..." << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    cout << "Run..." << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    cout << "Run..." << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    player.setCurrentHealth(player.getCurrentHealth() - 10);
                    player.setHunger(player.getHunger() - 10);
                    player.setThirst(player.getThirst() - 10);
                    cout << "Your HP, hunger, and thirst are each reduced by 10 because you ran vigorously." << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    cout << "Congratulations, you've escaped the tiger." << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    cout << "Keep the adventuring going!" << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
                else if(possibility >= 2 && possibility <= 4){
                    cout << "A bear is chasing you!!!" << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    cout << "Keep running!!!" << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    cout << "Run..." << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    cout << "Run..." << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    cout << "Run..." << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    player.setCurrentHealth(player.getCurrentHealth() - 10);
                    player.setHunger(player.getHunger() - 10);
                    player.setThirst(player.getThirst() - 10);
                    cout << "Your HP, hunger, and thirst are each reduced by 10 because you ran vigorously." << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    cout << "Congratulations, you've escaped the bear." << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    cout << "Keep the adventuring going!" << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
            }
            else{
                cout << "WOW!You find a lake in the forest." << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                cout << "You aren't thirsty anymore, so your thirst increased by 20." << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                player.setThirst(player.getThirst()+20);
            }
        }
        if(player.getCurrentRoom()->getRoomType() == "swamp"){
            cout << "----------------------------------------" << endl;
            cout << "You are in the swamp right now." << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            cout << "Swamp is actually full of dangers!" << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            cout << "OOPS! You accidentally got poisoned." << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            cout << "Your poison has increased by 10" << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            player.setPoison(player.getPoison() + 10);
            if(possibility >= 0 && possibility <= 4){
                cout << "You're really lucky!" << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                cout << "You've actually found rare plants that can cure all kinds of illnesses." << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                cout << "Your poison has been reset to zero." << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                cout << "And your hunger and thirst have both increased by 50" << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                cout << "Your HP is also back to 100." << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                player.setPoison(0);
                player.setHunger(player.getHunger() + 50);
                player.setThirst(player.getThirst() + 50);
                player.setCurrentHealth(100);
            }
            else{
                cout << "You have very bad luck!" << endl; 
                std::this_thread::sleep_for(std::chrono::seconds(1));
                cout << "You've been bitten by poisonous insects." << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                cout << "After being bitten by the insects, you're both hungry and thirsty, and you're lacking energy." << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                cout << "Your hunger and thirst have both decreased by 10" << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                cout << "And your HP has also decreased by 10." << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                player.setHunger(player.getHunger() - 10);
                player.setThirst(player.getThirst() - 10);
                player.setCurrentHealth(player.getCurrentHealth() - 10);
            }
        }
}

void Dungeon::handleEnvironmentItem(){
    //handle food and poison on the floor
    if(player.getCurrentRoom()->getIndex() == 2 && player.getCanGetFoodEnvironment() == true){
        player.addItem(Item("apple", "food", 0, 0, 0, 50, 30, 0));
        cout << "----------------------------------------" << endl;
        cout << "Wow! There is an apple on the floor. You picked it up." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));         
        cout << "And eat it." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
        cout << "Eat..." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
        cout << "The apple is very yummy." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
        cout << "Your hunger increased by 50, and your thirst increased by 30." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
        player.setCanGetFoodEnvironment(false);
    }
    if(player.getCurrentRoom()->getIndex() == 4 && player.getCanGetPoisonEnvironment() == true){
        player.addItem(Item("poisonbanana", "poison", 0, 0, 0, 10, 0, 20));
        cout << "----------------------------------------" << endl;
        cout << "You accidentally picked up a poisonbanana on the floor." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
        cout << "And you ate it." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
        cout << "You were poisoned by the poisonbanana." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
        cout << "Your poison increased by 20." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
        cout << "At least you can fill your stomach." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
        cout << "Your hunger also increased by 10." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
        player.setCanGetFoodEnvironment(false);
    }
}

void Dungeon::runDungeon(){
    string operation;
    while(checkGameLogic()){
        cout << "----------------------------------------" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));

        vector<Object*> objects = player.getCurrentRoom()->getObjects();
        Object* firstobject;
        if(!objects.empty())firstobject = objects[0];

        player.setCanCommunicate(false);
        player.setCanAttack(false);        
        if(!objects.empty() && firstobject->getTag() == "NPC"){
            cout << "* * * * * * * * * *" << endl;
            cout << "*                 *" << endl;
            cout << "*                 *" << endl;
            cout << "*       NPC       *" << endl;
            cout << "*                 *" << endl;
            cout << "*                 *" << endl;
            cout << "* * * * * * * * * *" << endl;
        }
        else if(!objects.empty() && firstobject->getTag() == "Monster"){
            cout << "* * * * * * * * * *" << endl;
            cout << "*                 *" << endl;
            cout << "*                 *" << endl;
            cout << "*     Monster     *" << endl;
            cout << "*                 *" << endl;
            cout << "*                 *" << endl;
            cout << "* * * * * * * * * *" << endl;
        }
        else if(player.getCurrentRoom()->getRoomType() == "desert"){
            cout << "* * * * * * * * * *" << endl;
            cout << "*      Desert     *" << endl;
            cout << "*                 *" << endl;
            cout << "*                 *" << endl;
            cout << "*                 *" << endl;
            cout << "*                 *" << endl;
            cout << "* * * * * * * * * *" << endl;
        }
        else if(player.getCurrentRoom()->getRoomType() == "forest"){
            cout << "* * * * * * * * * *" << endl;
            cout << "*      Forest     *" << endl;
            cout << "*                 *" << endl;
            cout << "*                 *" << endl;
            cout << "*                 *" << endl;
            cout << "*                 *" << endl;
            cout << "* * * * * * * * * *" << endl;
        }
        else if(player.getCurrentRoom()->getRoomType() == "swamp"){
            cout << "* * * * * * * * * *" << endl;
            cout << "*      Swamp      *" << endl;
            cout << "*                 *" << endl;
            cout << "*                 *" << endl;
            cout << "*                 *" << endl;
            cout << "*                 *" << endl;
            cout << "* * * * * * * * * *" << endl;
        }
        else{
            cout << "* * * * * * * * * *" << endl;
            cout << "*                 *" << endl;
            cout << "*                 *" << endl;
            cout << "*                 *" << endl;
            cout << "*                 *" << endl;
            cout << "*                 *" << endl;
            cout << "* * * * * * * * * *" << endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cout << "S(s): Show status" << endl;
        cout << "O(o): Open backpack" << endl;
        cout << "M(m): Move" << endl;
        if(!objects.empty()){
            if(firstobject->getTag() == "NPC"){
                cout << "C(c): Communicate and get items from NPC" << endl;
                player.setCanCommunicate(true);
            }
            if(firstobject->getTag() == "Monster"){
                cout << "A(a): Attack the monster" << endl;
                player.setCanAttack(true);
            }
        }
        cout << "E(e): Exit the game and save record" << endl;
        cout << "Enter the operation: ";

        cin >> operation;
        cout << "----------------------------------------" << endl;
        operation[0] = tolower(operation[0]);
        while(!isOperation(operation)){
            cout << "Invalid input(s)" << endl;
            cout << "Enter the operation: ";
            cin >> operation;
            cout << "----------------------------------------" << endl;
        }

        if(operation == "e"){
            Record record;
            record.saveToFile(&player, rooms);
            break;
        }
        if(operation == "s"){
            cout << player.getName() << "'s Status: " << endl;
            cout << "HP: " << player.getCurrentHealth() << '/' << player.getMaxHealth() << endl;
            cout << "Attack: " << player.getAttack() << endl;
            cout << "Defense: " << player.getDefense() << endl;
            cout << "Hunger: " << player.getHunger() << endl;
            cout << "Thirst: " << player.getThirst() << endl;
            cout << "Poison: " << player.getPoison() << endl;
        }
        if(operation == "o"){
            vector<Item> v = player.getInventory();
            int weaponCount = 0, foodCount = 0;
            if(v.size() == 0) cout << "You have nothing!" << endl;
            else{
                cout << "You have: " << endl;
                for(auto i: v){
                    if(i.getType() == "Weapon"){
                        cout << i.getName() << endl;
                        weaponCount++;
                    } 
                }
                if(weaponCount == 0) cout << "nothing!!!" << endl;
                cout << "You ate and drank: " << endl;
                for(auto i: v){
                    if(i.getType() != "Weapon") {
                        cout << i.getName() << endl;
                        foodCount++;
                    }
                if(foodCount == 0) cout << "nothing!!!" << endl;
                }
            }
        }
        if(operation == "m"){
            this->handleMovement();
            this->handleEnvironmentItem();
        }
        if(operation == "c"){
            NPC* NpcInRoom = dynamic_cast<NPC*>(firstobject);
            cout << "NPC's name: " << NpcInRoom->getName() << endl;
            cout << NpcInRoom->getScript() << endl;
            //NpcInRoom->listCommodity();
            if(NpcInRoom->triggerEvent(&player)){
                player.getCurrentRoom()->popObject(NpcInRoom);
            }
        }
        if(operation == "a"){
            Monster* MonsterInRoom = dynamic_cast<Monster*>(firstobject);
            cout << "Monster's name: " << MonsterInRoom->getName() << endl;
            cout << "Monster is here" << endl;
            if(MonsterInRoom->triggerEvent(&player)){
                player.getCurrentRoom()->popObject(MonsterInRoom);
            }
        }
        this->handleRoomSystem();
        this->handleHungerSystem();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
}


