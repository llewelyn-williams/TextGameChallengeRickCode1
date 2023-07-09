/* Includes are libraries of pre - built classes that we
can make use of in our C++ code.*/

// Input output. Does lots of stuff. We need it for cinand cout at least, maybe more things.
#include <iostream> 
// String does string stuff, we include this becuase we work with strings in our code.
#include <string>
// We want to use vectors so we include vector. Vectors are similar to arrays
// in that they store sets of data, but way fancier and do more that arrays can't.
#include <vector>
// Standard C Library? I don't know why we needed this, but we did.
#include <cstdlib>
// C Time, we used this to help us create some randomness.
#include <ctime>

// The lazy man thing we always do so that we don't have to write what
// name space we're using in out code all the time. Standard Namespace.
using namespace std;

//Our first class, defines a chacter. This is our base class for both player and enemy.
class Character {
// The following will be public...
public:
    string name; // A string to store a character name.
    int health; // The player health, it can go up and down and charcter dies if it reaches zero.
    int attack; // How much base damage a character delivers when attaking.
    int defense; // How much a character can negate received damage value.

    // Constructor function for Character class 
    // Takes a pointer to a string for the name and integers for the rest.
    Character(const string& name, int health, int attack, int defense)
        : name(name), health(health), attack(attack), defense(defense) {}

    // Function to calulate and apply received damage.
    // It takes an integer that is the amount of incoming damage attempting to be applied.
    void takeDamage(int damage) {
        // The actual damage received is caculated by subtracting the defense value from the damage value.
        // We don't want to accidently apply negative damage, so we only set the actual damage to the larger
        // of either that calulated result OR zero.
        int actualDamage = max(0, damage - defense); // max(this, that) - return larger of this or that.
        // The character health is reduced by the amount of "actual damage".
        health -= actualDamage;
    }

    //Function that will return either true or false
    // Trus if the player IS dea, false if not.
    bool isDead() {
        // The comparison (health <= 0) equates to a boolean value, either true or false.
        // So if it's true the statement becomes "return true" and the obviouse opposite.
        // If we could be certain that health is ALWAYS either 0 or a positive int, I belive we could
        // have written this as "return !health" and it would still work, because this function
        // returns a bool, it'll take any int that isn't zero and treat is a true.
        return health <= 0; 
    }
};


// Here  is our Enemy class, it's a decendent of the Character class
class Enemy : public Character {
public:
    // It's contructor takes the same stuff as the Character class, then
    // it puts them into those pars of itself that it get from the Character class.
    Enemy(const string& name, int health, int attack, int defense)
        : Character(name, health, attack, defense) {}
};

// Here  is our Player class, it's a decendent of the Character class as well
class Player : public Character {
public:
    // UNlike our enemy, the player ALSO has experience and an inventory.
    int experience; // An int, that I'm not sure we actually use afterwards.

    //This is a vector of ints, it stores potion values not potion objects in their entirety.
    vector<int> inventory; // To store potion health restoration values as int, we only got as far as potions.

    // The player constructor takes all the things that character class part neds and
    // passes them to it and the additoinaly sets the experience to an inital value of zero.
    // This is some quick contructor way of writing "experience = 0;"
    Player(const string& name, int health, int attack, int defense)
        : Character(name, health, attack, defense), experience(0) {}

    // Function to use a collected potion.
    void Use_Potion() {

        // Check to see if we actually have any in the inventory.
        if (!inventory.empty()) {

            // If we added the potion restoration value to the current health, would it EXCEED 100?
            if (health + inventory.back() > 100) {
                // Wew don't want it to exceed 100 because some othe code will break because it's
                // using 100 as an assumed maximum health. So, we simply set the health to 100.
                health = 100;
                cout << "Maximum Health! \n";
            }
            else {
                // Otherwise go ahead and just increase the health by the amount of the last picked up potion.
                health += inventory.back();
            }

            // Tell the player how much health they restored. to_string is used because << is trying
            // to slpa different strings togeether and I think it'd get confused if we changed type 
            // in the middle of doing that.
            cout << "You used a potion and restored " << to_string(inventory.back()) << " health.\n";
            
            // We just "used" a potion so we remove it from the inventory. The one from the end or "back".
            inventory.pop_back();
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
        Potion potion2("Medium Potion", 40);
        Potion potion3("Large Potion", 60);

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
                        player.inventory.push_back(potion.Health_Restore);
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
                cout << "Well done, you won!" << endl;
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