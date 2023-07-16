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


// The potion class
class Potion {
public:
    string Name; // Such as "Medium Potion", "Large Potion" etc.
    int Health_Restore; // How much it can heal you.

    // We use a string pointer here but I can't remeber if this is because we HAVE TO or because it's preferable. 
    Potion(const string& name, int health_restore) : Name(name), Health_Restore(health_restore) {}
};

class Room {
public:
    // So the reeom will have a name and a collection of potions and enemies in it.
    string name;
    vector<Enemy> enemies; // A container that contains objects of the class type Enemy, the container is called enemies.
    vector<Potion> potions; // A container that contains objects of the class type Potion, the container is called potions.

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
    Player player; // An onject of class Player called "player"
    vector<Room> rooms; // A container that contains objects of the class type Room, the container is called rooms.
    int currentRoomIndex; // An integer that we will increment as we move through the rooms.

    // When using this contructor all you need supply is the name for the player as a string.
    // The player is instatiated with default vaues for health, attack and defence.
    // The room index is set to zero.
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

        /* So, random doesn't exist within the computer. The numbers have to come some SOMEWHERE.
        srand() I belive is being used to take something as random as you can manage to use to create
        a "seed" for random numbers.

        calling time() with nullptr gives the current epch time (which changes every second? - so it's an easy source of 
        something "very varied" if not truly random.

        With this set we can  then make use of rand()
        */

        srand(time(nullptr));

        int Num_Rooms = 3; // Set how many rooms we want.
        int Max_Enemies = 4; // Set the maximum number of enemies that we're going to have populate a room.

        //Loop to create rooms
        for (int i = 0; i < Num_Rooms; i++) {//number rooms
            //room name
            string roomName = "Room " + to_string(i + 1); // Our room names will not be exciting, they'll be Room1, Room2 etc.
            // random number of enemies
            
            /* rand() returns a psudo - random number between 0 and something quite large.
             So, by using the modulo operator with it, we can get ourselves a number between
             zero and the one supplied.
             This is because the remainder when you divide a number by another number is either going to be 
             zero or at most one less than the number you're dividing by.. 
             .. which is why we +1 to it. So that it's shifted up.
             So we'll actually get between 1 and the maximum number of enemies we specified.
            */
            int randAmtEnemies = rand() % Max_Enemies + 1;

            //vector of enemy objects
            // Ready to be filled with the enemies that we'll create.
            vector<Enemy> enemies;

            // So we loop for the amount of times as random enemies we determined
            for (int j = 0; j < randAmtEnemies; j++) { // ememies generate random stats

                string enemyName = "Enemy " + to_string(j + 1); // Boring enemy names. Enemy1, Enemy2 etc.

                int enemyHealth = rand() % 20 + 10; // Health between 10 and 29
                int enemyAttack = rand() % 5 + 5; // Attack power between 5 and 9
                int enemyDefense = rand() % 3 + 2; // Defence between 2 and 4

                //create enemy objects from class
                Enemy enemy(enemyName, enemyHealth, enemyAttack, enemyDefense);
                //push enemies to the vector
                enemies.push_back(enemy);
                        
            }
            //create rooms from the class
            /* If you were to look back at the room constructor you;d see it takes two things.
            a string for a name and a vector that contains objects of type Enemy.
            And that's what we give it. The roomName is the boring name we generated above
            within this loop. 
            enemies was also created at this level of the loop, but we used the nested loop
            immediately above here to create the individual Enemy objects and push them to the
            vector enemies. */
            Room room(roomName, enemies); 
            
            //push rooms to the vector
            rooms.push_back(room);
        }

        // Here were create some potions.
        Potion potion1("Health Potion", 20);
        Potion potion2("Medium Potion", 40);
        Potion potion3("Large Potion", 60);

        // We know that we have 3 rooms, so we're just putting
        // each potion into a room in turn.
        rooms[0].potions.push_back(potion1); // Standard potion in the first room (20 hp).
        rooms[1].potions.push_back(potion2); // Medium potion in the first room (40 hp).
        rooms[2].potions.push_back(potion3); // Large potion in the first room (60 hp).

    }

    // This console based visual health bar made out of charactres was one of the last tings added to the game.
    // This is a fcuntion that returns a string.
    // The function takes three ints to work out how to diplay the health.
    string Create_Health_Bar(int Current_Health, int Max_Health, int Bar_Width) {

        // Filled width is how much of the health bar will be filled.
        // For this health bar that means how many '#' will be displaye din a row.
        
        /* First we divide the Current Health by the Max health to know what proportion of the bar needs to be filled
         In this case thetotal bar width will represent the max health.
         We thhen mutiply that nuber by the bar with value, so that it becomes a proportion OF THAT.
         That value is then cast as an int because as we're using division there's the potential
         for it to be a float or double as a result and we only want to use ints.*/

         /* Multiplying by 1.0 is coing to cause a conversion from int to double.
         One reason I think ew might do that is because the result of the division migght be a decimal number.
         So perhaps is's necessary in case that is the case.
         static_cast can cast down from double to int like we're doing here
         but I don't know why you wouldn't use the simpler : int (expression) */
        int Filled_Width = static_cast<int>(1.0 * Current_Health / Max_Health * Bar_Width);

        // The empty width is the reaminder fo the bar width once you subtract the recently calulated filled width.
        int Empty_Width = Bar_Width - Filled_Width;

        // Here a string called Health_Bar is constructed.
        string Health_Bar = "["; // The string starts with the '[' to show it's the start of the bar.

        // Then we += the string(so effectively add on to the existing) as many # symbols as worked out.
        // Here we use the 2 arguemtn contructor of the form: string(size_type count, CharT ch)
        // This takes a number and character and reurns a string of that character repeated as many tie as the number.
        // Obviously ideal for this situation where that's exactly what we want to d with our filled and then empty widths
        // with '#' for the filled followed by ' ' for the empty. 
        Health_Bar += string(Filled_Width, '#'); 
        Health_Bar += string(Empty_Width, ' ');
        Health_Bar += "]"; // Finally we add a ']' on the end to show it's the end of the bar.

        return Health_Bar; // Return the string created above.
    }

    // The play function. Here we do a lot of cout to the console that is the game that the user sees / plays.
    void play() {
        cout << "Welcome to the Text RPG!" << endl;

        // We call the function defined earlier.
        // This meaks the room and puts the enemies and potions in them as well.
        createRooms(); 
        
        // An infite loop, the game is "running".
        while (true) {
            // We create a room (currentRoom), it is a copy of one of the rooms from the vector rooms at the current index.
            Room currentRoom = rooms[currentRoomIndex]; 
            // We tell the player what room they're in.
            cout << "You are in the " << currentRoom.name << "." << endl; 
            // We display the healthbar using the player heath, max 100 and 20 bar sections.
            cout << "Player Health: " << Create_Health_Bar(player.health, 100, 20) << endl; 
            // Using dot notation we access the inventory vector on the player object.
            // The vector has a method size() that tells us how many items are in the vector.
            // We take that number and use to_string() to convert it to a string because
            // we're chaiing together << to the cout, so we need each part chained to be
            // a string.
            cout << "You have " << to_string(player.inventory.size()) << " potions left. \n";


            // Aother loop. While the current room has more than zero enemies
            // (i.e. you haven't killed them all yet.)
            if (currentRoom.enemies.size() > 0) {
                // Say what enemies there are in the room.
                cout << "Enemies encountered: " << endl;
                /* Because there can be more than one enemy, we use a 'Ranged for Loop'
                So for each item within the collection on the right of the colon 
                a varable is created with the name on the left.
                In this case a contant pointer to an object of class type Enemy, called ebemy*/
                for (const Enemy& enemy : currentRoom.enemies) {
                    cout << enemy.name << endl; // Within the loop for each enemy we cout its name.
                }

                // Battle loop
                /* So, two negative conditions here.Both need to be met for the loop to run.
                The first is the opposite of currentRoom.enemies.empty(), so if the enemies
                vector in the current room IS NOT empty..
                The second is the of player.isDead(), so if the sunction isDead() on the player
                returns true, then !player.isDead() will return false. Therefore the player IS NOT
                dead.
                In summary, "Room is not empty and player is not dead."
                It is in this instance we will engage in battle with the enemy in the room. 
                If either are true then we shall not and we will skip this entire loop.*/
                while (!currentRoom.enemies.empty() && !player.isDead()) {
                    // We create a enemy (enemy), it is a copy of one of the enemies from the vector enemies at the first position in the vector.
                    // We are not changing the index here '[0]', because as we kill the enemies we will be removing them from the vector and the "next"
                    // ememy will take it's place at the front of the vector.
                    Enemy& enemy = currentRoom.enemies[0];
                    // Let the player know what they're fighting.
                    cout << "You are battling " << enemy.name << "." << endl;

                    // Another loop. This one if for fighting.
                    // Player and enemy will take it in turn to attack each other until either is dead.
                    // This look is esentially "while neither the player or enemy are dead..."
                    while (!enemy.isDead() && !player.isDead()) {
                        // Player's turn
                        // We use the player attack value with the takeDamage method of the enemy.
                        // This is both the act of the player attacking and the enemy being attacked (receiving damage)
                        enemy.takeDamage(player.attack); 
                        // Provide a visual output of what's happenig above.
                        cout << "You attacked " << enemy.name << " for " << player.attack << " damage." << endl;

                        // Enemy's turn
                        // As the player goes first at the enemy might be dead as a result, we check
                        // to see if the enemy is dead before they have thier go, if they're dead, 
                        // then they don't get a go and this section is skipped over.
                        if (!enemy.isDead()) {
                            // Just like above but the other way around. 
                            // We use the ememy attack value with the takeDamage method of the player.
                            // This is both the act of the enemy attacking and the player being attacked (receiving damage)
                            player.takeDamage(enemy.attack);
                            // Provide a visual output of what's happenig above.
                            cout << enemy.name << " attacked you for " << enemy.attack << " damage." << endl;

                            // Note: Whie the readout is telling you now much you attack damage was delivered.
                            // This will not be the amout of health reduced, becuase it hasn't taken into account
                            // the defense value of either character that comes into play when they takeDamage()
                        }
                    }

                    // Eventually after taking enough turns hitting each other either the player or the enmy will be dead.
                    // We move out of the "fighting" loop and back to the level of the "battle" loop.

                    // If it's the enmy that is dead.
                    if (enemy.isDead()) {
                        cout << "You defeated " << enemy.name << "." << endl; // Let the player know they killed them.
                        player.experience += 10; // Increase the player experience points (we don't actually use this for anything else anywhere)
                        // Remove the enmy from the vector of enemies for this room.
                        // So,  currentRoom.enemies.erase( 'position in the vector' ) - Will remove the item from the vector at the spefied position.
                        //  currentRoom.enemies.begin() - this gives us the position where we want to remove the enemy.
                        // as mentioned above this means that the "next" will now be at the front once this is removed
                        // ready for the next iteration of the loop. Or if it was the only or last one, the vector will be empty.
                        // it will have a size of zero (the condition we check for to see if the loop will continue or not)
                        currentRoom.enemies.erase(currentRoom.enemies.begin());
                    }

                    // If it's the player that is dead.
                    if (player.isDead())
                    {
                        cout << "You are deaded " << endl;
                        return; // We exit the battle loop 
                    }
                }

                // Once we exit the battle loop...


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
                    cout << "Would you like to use a potion? (y / n)" << endl;
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