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

    Player(const string& name, int health, int attack, int defense)
        : Character(name, health, attack, defense), experience(0) {}
};

class Room {
public:
    string name;
    vector<Enemy> enemies;

    //Passing an object by reference into a constructor is useful when you want 
    //to avoid copying the object.This can be especially important when the 
    //object is large or when you want to modify the original object.

    //When we create our own copy constructor, we pass an object by reference
    //and we generally pass it as a const reference.One reason for passing const 
    //reference is, we should use const in C++ wherever possible so that objects 
    //are not accidentally modified.


    Room(const string& name, const vector<Enemy>& enemies)
        : name(name), enemies(enemies) {}
};

class Game {
public:
    Player player;
    vector<Room> rooms;
    int currentRoomIndex;

    Game(const string& playerName)
        : player(playerName, 100, 10, 5), currentRoomIndex(0) {}

    void createRooms() {
        Enemy enemy1("Goblin", 20, 8, 2);
        Enemy enemy2("Skeleton", 30, 10, 5);
        Enemy enemy3("Orc", 40, 12, 8);

        Room room1("Dungeon Entrance", { enemy1 });
        Room room2("Dark Corridor", { enemy1, enemy2 });
        Room room3("Treasure Room", { enemy1, enemy2, enemy3 });

        rooms.push_back(room1);
        rooms.push_back(room2);
        rooms.push_back(room3);
    }

    void play() {
        cout << "Welcome to the Text RPG!" << endl;

        createRooms();
        
        while (true) {
            Room currentRoom = rooms[currentRoomIndex];
            cout << "You are in the " << currentRoom.name << "." << endl;

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
            }

            cout << " Room is clear progress or quit = q ";
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