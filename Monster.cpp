#include "Monster.h"

Monster::Monster() :GameCharacter("", "Monster", 0, 0, 0){}

Monster::Monster(string theName, int theHealth, int theAttack, int theDefense) :GameCharacter(theName, "Monster", theHealth, theAttack, theDefense){}

//deal with combat system
bool Monster::triggerEvent(Object* obj){
    //cout << "deal with combat system" << endl;
    Player* player = dynamic_cast<Player*>(obj);
    if(player == NULL) return false;

    //get poison from the monster
    if(this->getName() == "Littlemonster" && this->getCurrentHealth() == 50 ){
        player->addItem(Item("devilpoison", "poison", 0, 0, 0, 0, 0, 10));
        cout << "You meet the Littlemonster!!!" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cout << "The Littlemonster forced you to drink the Devil Poison." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cout << "Your poison increased by 10." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    while(1){
        //show status of player and monster
        cout << "Your status: " << endl;
        cout << "HP: " << player->getCurrentHealth() << "/" << player->getMaxHealth() << endl;
        cout << "Attack: " << player->getAttack() << endl;
        cout << "Defense: " << player->getDefense() << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cout << this->getName() << " status: " << endl;
        cout << "HP: " << this->getCurrentHealth() << "/" << this->getMaxHealth() << endl;
        cout << "Attack: " << this->getAttack() << endl;
        cout << "Defense: " << this->getDefense() << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cout << "Are you sure you are going to attack " << this->getName() << endl;
        cout << "C(c): Confirm attack" << endl;
        cout << "R(r): retreat" << endl;
        cout << "Enter your decision:";

        //deal with operation retreat or comfirm attack
        string operation;
        cin >> operation;
        operation[0] = tolower(operation[0]); 
        if(operation != "c" && operation != "r"){
            cout << "Invalid Input" << endl;
            continue;
        }
        if(operation == "r"){
            cout << "Sending you back to the previous room." << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            player->changeRoom(player->getPreviousRoom());
            break;
        }
        if(operation == "c"){
            int damageCause = this->takeDamage(player->getAttack());
            cout << "You attack the monster(" << this->getName() << "), cause " << damageCause << " damage." << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if(this->checkIsDead()){
                //If the Boss is dead finish the game, the player win
                if(this->getName() == "Boss"){
                    cout << "The Boss is dead!" << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    cout << "You win!!!" << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    cout << "Congratulation!!!" << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    exit(0);
                }
                //other monster(Littlemonster) continue the game, get food from Littlemonster(if it is dead)
                else{
                    cout << "The monster(" << this->getName() << ") is dead" << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    cout << "You beat the Little Monster." << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    cout << "You are such a hero." << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    cout << "You are going to eat the superbanana that the Littlemonster left." << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    cout << "Eat..." << endl;
                    player->addItem(Item("superbanana", "food", 50, 0, 0, 50, 50, 0)); 
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    cout << "Your hunger, thirst, and HP all increased by 50." << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    return true;
                }   
            }
        }

        //deal with player's statue, and check if player is dead or not
        int damageCause = player->takeDamage(this->getAttack());
        cout << "The monster(" << this->getName() << ") attack you, cause " << damageCause << " damage." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if(player->checkIsDead()){
            cout << "You are dead, beaten by the monster(" << this->getName() << ")!" << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            cout << "Game Over!!!" << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            //break;
            exit(0);
        }
        sleep(1);
    }
    return false;
}

