#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Character {
public:
    string name;
    int health;
    int attack;
    int defense;

    Character(const string& name, int health, int attack, int defense)
        : name(name), health(health), attack(attack), defense(defense) {}

    void takeDamage(int damage) {
        int actualDamage = max(0, damage - defense);
        health -= actualDamage;
    }

    bool isDead() {
        return health <= 0;
    }
};

class Enemy : public Character {
public:
    Enemy(const string& name, int health, int attack, int defense)
        : Character(name, health, attack, defense) {}
};

class Player : public Character {
public:
    int experience;
    vector<string> inventory;

    Player(const string& name, int health, int attack, int defense)
        : Character(name, health, attack, defense), experience(0) {}

    void Use_Potion() {
        if (!inventory.empty()) {
            inventory.pop_back();
            health += 20;
            cout << "You used a potion";
        }
        else {
            cout << "You have no potions";
        }
    }
};



class Potion {
public:
    string Name;
    int Health_Restore;

    Potion(const string& name, int health_restore) : Name(name), Health_Restore(health_restore) {}
};

class Room {
public:
    string name;
    vector<Enemy> enemies;
    vector<Potion> potions;

    //Passing an object by reference into a constructor is useful when you want 
    //to avoid copying the object.This can be especially important when the 
    //object is large or when you want to modify the original object.

    //When we create our own copy constructor, we pass an object by reference
    //and we generally pass it as a const reference.One reason for passing const 
    //reference is, we should use const in C++ wherever possible so that objects 
    //are not accidentally modified.


    Room(const string& name, const vector<Enemy>& enemies)
        : name(name), enemies(enemies), potions(potions) {}
};

class Game {
public:
    Player player;
    vector<Room> rooms;
    int currentRoomIndex;

    Game(const string& playerName)
        : player(playerName, 100, 10, 5), currentRoomIndex(0) {}

    void createRooms() {
        //Enemy enemy1("Goblin", 20, 8, 2);
        //Enemy enemy2("Skeleton", 30, 10, 5);
        //Enemy enemy3("Orc", 40, 12, 8);

        //Room room1("Dungeon Entrance", { enemy1 });
        //Room room2("Dark Corridor", { enemy1, enemy2 });
        //Room room3("Treasure Room", { enemy1, enemy2, enemy3 });

        //rooms.push_back(room1);
        //rooms.push_back(room2);
        //rooms.push_back(room3);

        srand(time(nullptr));

        int Num_Rooms = 3;
        int Max_Enemies = 4;

        for (int i = 0; i < Num_Rooms; i++) {//number rooms
            //room name
            string roomName = "Room " + to_string(i + 1);
            // random number of enemies
            int randAmtEnemies = rand() % Max_Enemies + 1;
            //vector of enemy objects
            vector<Enemy> enemies;

            for (int j = 0; j < randAmtEnemies; j++) { // ememies generate randome stats

                string enemyName = "Enemy " + to_string(j + 1);

                int enemyHealth = rand() % 20 + 10;
                int enemyAttack = rand() % 5 + 5;
                int enemyDefense = rand() % 3 + 2;

                //create enemy objects from class
                Enemy enemy(enemyName, enemyHealth, enemyAttack, enemyDefense);
                //push enemies to the vector
                enemies.push_back(enemy);
                        
            }
            //create rooms from the class
            Room room(roomName, enemies);
            
            //push rooms to the vector
            rooms.push_back(room);
        }

        Potion potion1("Health Potion", 20);
        Potion potion2("Medium Potion", 50);
        Potion potion3("Large Potion", 100);

        rooms[0].potions.push_back(potion1);
        rooms[1].potions.push_back(potion2);
        rooms[2].potions.push_back(potion3);

    }

    string Create_Health_Bar(int Current_Health, int Max_Health, int Bar_Width) {
        int Filled_Width = static_cast<int>(1.0 * Current_Health / Max_Health * Bar_Width);
        int Empty_Width = Bar_Width - Filled_Width;

        string Health_Bar = "[";
        Health_Bar += string(Filled_Width, '#');
        Health_Bar += string(Empty_Width, ' ');
        Health_Bar += "]";

        return Health_Bar;
    }

    void play() {
        cout << "Welcome to the Text RPG!" << endl;

        createRooms();
        
        while (true) {
            Room currentRoom = rooms[currentRoomIndex];
            cout << "You are in the " << currentRoom.name << "." << endl;
            cout << "Player Health: " << Create_Health_Bar(player.health, 100, 20) << endl;
            cout << "You have " << to_string(player.inventory.size()) << " potions left. \n";

            if (currentRoom.enemies.size() > 0) {
                cout << "Enemies encountered: " << endl;
                for (const Enemy& enemy : currentRoom.enemies) {
                    cout << enemy.name << endl;
                }

                // Battle loop
                while (!currentRoom.enemies.empty() && !player.isDead()) {
                    Enemy& enemy = currentRoom.enemies[0];
                    cout << "You are battling " << enemy.name << "." << endl;

                    while (!enemy.isDead() && !player.isDead()) {
                        // Player's turn
                        enemy.takeDamage(player.attack);
                        cout << "You attacked " << enemy.name << " for " << player.attack << " damage." << endl;

                        // Enemy's turn
                        if (!enemy.isDead()) {
                            player.takeDamage(enemy.attack);
                            cout << enemy.name << " attacked you for " << enemy.attack << " damage." << endl;
                        }
                    }

                    if (enemy.isDead()) {
                        cout << "You defeated " << enemy.name << "." << endl;
                        player.experience += 10;
                        currentRoom.enemies.erase(currentRoom.enemies.begin());
                    }

                    if (player.isDead())
                    {
                        cout << "You are deaded " << endl;
                        return;
                    }
                }
                if (currentRoom.potions.size() > 0) {
                    cout << "You found some potions in the room!" << endl;
                    cout << "Potions available: " << endl;

                    for (const Potion& potion : currentRoom.potions) {
                        cout << "- " << potion.Name << endl;
                    }
                    cout << "Do you want to collect the potion? (y / n): ";
                    char choice;
                    cin >> choice;

                    if (choice == 'y') {
                        Potion potion = currentRoom.potions.back();
                        currentRoom.potions.pop_back();
                        player.inventory.push_back(potion.Name);
                        cout << "You took the " << potion.Name << " and added it to your inventory." << endl;
                    }

                }

                if (player.inventory.size() > 0) {
                    cout << "Would you like to use a a potion? (y / n)" << endl;
                    char choice;
                    cin >> choice;
                    if (choice == 'y') {
                        // Use Potion
                        player.Use_Potion();

                        cout << "You have " << to_string(player.inventory.size()) << " potions left. \n";
                    }
                    else {
                        // Don't use Potion
                    }
                }
            }

            cout << " Room is clear progress or quit = q \n";
            char choice;
            cin >> choice;

            if (choice == 'q') {
                cout << "you quiter " << endl;
                return;
            }

            currentRoomIndex++;

            if (currentRoomIndex >= rooms.size())
            {
                cout << "weldone you won" << endl;
                return;
            }
        }
    }
};

int main()
{
    srand(time(nullptr));

    string playerName;
    cout << "Enter Player name :";

    getline(cin, playerName);

    Game game(playerName);
    game.play();

    return 0;
}