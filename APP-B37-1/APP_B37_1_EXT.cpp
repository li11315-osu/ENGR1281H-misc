// ENGR 1281H
// APP B37-1 EXT
// 19 November 2020
// Thomas Li, Annie Getts, Drew Ripberger
// Clingan 10:20

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include <iostream>

using namespace std;

#define CHARACTER_HEALTH_TO_LEVEL_RATIO 10
#define CHARACTER_STRENGTH_TO_LEVEL_RATIO 2

#define PLAYER_PUNCH_TO_STRENGTH_RATIO 1/4
#define PLAYER_SWORD_TO_STRENGTH_RATIO 1/2
#define PLAYER_HEAL_TO_HEALTH_RATIO 1/5
#define PLAYER_LEVEL_MIN 10
#define PLAYER_LEVEL_MAX 50

#define GOBLIN_ATTACK_TO_STRENGTH_RATIO 1/6
#define GOBLIN_LEVEL_MIN 10
#define GOBLIN_LEVEL_RANGE 10

#define SPIDER_ATTACK_TO_STRENGTH_RATIO 1/5
#define SPIDER_LEVEL_MIN 15
#define SPIDER_LEVEL_RANGE 10

#define DRAGON_ATTACK_TO_STRENGTH_RATIO 1/3
#define DRAGON_ATTACK_SPECIAL 20
#define DRAGON_LEVEL 30

#define NUM_MONSTERS 2

/* Character parent class */
class character
{
	public:
		/* Constructor function to set stats based on name and level */
		character(char nm[25], int l);
		/* Function to return max health given current level */
		int get_max_health();
		/* Character name, level, health, and strength stats */
		char name[25];
		int level, health, strength;
};

/* Player child class of character parent class */
class player : public character
{
	public:
		/* Constructor function to set stats by using parent constructor */
		player(char nm[25], int l) : character(nm, l)
		{
			/* Initialize generic player weapon message text */
			strcpy(weapon_message, "You attack.");
		};
		/* Functions for attack options, displaying stats, and leveling up */
		int punch();
		int sword();
		int heal();
		void display_stats();
		void level_up();
		/* String for weapon message based on player attack */
		char weapon_message[100];
};

/* Enemy child class of character parent class */
class enemy : public character
{
	public:
		/* Constructor function to set stats by using parent constructor */
		enemy(char nm[25], int l) : character(nm, l)
		{
			/* Initialize generic enemy wound message text */
			strcpy(wound_message, "The enemy attacks.");		
		};
		/* Virtual attack function for children to use */
		virtual int attack() {};
		/* String for wound message based on enemy attack */
		char wound_message[100];
};

/* Goblin child class of enemy parent class */
class goblin : public enemy
{
	public:
		/* Constructor function to set stats by using parent constructor */
		goblin(char nm[25], int l) : enemy(nm, l) {};
		/* Attack function unique to goblin */
		int attack();
};

/* Spider child class of enemy parent class */
class spider : public enemy
{
	public:
		/* Constructor function to set stats by using parent constructor */
		spider(char nm[25], int l) : enemy(nm, l) {};
		/* Attack function unique to spider */
		int attack();
};

/* Dragon child class of enemy parent class */
class dragon : public enemy
{
	public:
		/* Constructor function to set stats by using parent constructor */
		dragon(char nm[25], int l) : enemy(nm, l) {};
		/* Attack function unique to dragon */
		int attack();
};

/* Function prototype for battle function */
void battle(player *hero, enemy *monster);

int main()
{
    /* Seed random number generator */
    srand(time(NULL));
    
    /* Declare variables to retrieve user-inputted player name and level */
    char player_name[25];
    int player_level;
        
    /* Prompt user for player name */
    cout << "\nEnter player name: ";
    cin >> player_name;
    
    /* Prompt user for player level within range */
    cout << "\nEnter player level (" << PLAYER_LEVEL_MIN;
    cout << "-" << PLAYER_LEVEL_MAX << "): ";
    cin >> player_level;
    
    /* Make sure player level is within appropriate range */
    if (player_level < PLAYER_LEVEL_MIN)
    {
    	player_level = PLAYER_LEVEL_MIN;
    }
    else if (player_level > PLAYER_LEVEL_MAX)
    {
    	player_level = PLAYER_LEVEL_MAX;
    }
    
    /* Create hero object for player character */
    player hero(player_name, player_level);
    
    /* Initialize menu choice and clear screen */
    int menu = 0;
    system("clear");
    
    /* Loop through dungeon menu choices until the user leaves the dungeon */
    while (menu != 4)
    {
    	/* Display dungeon menu choices */
    	cout << "\n\nDungeon:";
    	cout << "\n\t(1) Fight Monsters";
    	cout << "\n\t(2) Fight Boss";
    	cout << "\n\t(3) Display Player Stats";
    	cout << "\n\t(4) Leave Dungeon";
    	cout << "\nEnter choice: ";
    	
    	/* Read in user dungeon menu choice and clear screen */
    	cin >> menu;
    	system("clear");
    	
    	/* Declare variables for temporary monster instances */
    	int e;
    	char monster_name[25];
    	int monster_level;
    	
    	/* Switch the user dungeon menu choice */
    	switch (menu)
    	{
    		case 1:
    			/* Create pointer to an enemy called monster */
    			enemy *monster;
    		
    			/* Randomize which monster will appear */
    			e = rand()%NUM_MONSTERS;
    			
    			/* Switch on which monster will appear */
    			switch (e)
    			{
    				case 0:
    					/* Set goblin monster name */
    					strcpy(monster_name,"Goblin");
    					/* Randomize goblin monster level within range */
    					monster_level = rand()%GOBLIN_LEVEL_RANGE+GOBLIN_LEVEL_MIN;
    					/* Create new instance of goblin class and assign monster to it */
    					monster = new goblin(monster_name, monster_level);
    					break;
    				case 1:
					/* Set spider monster name */
    					strcpy(monster_name,"Goblin");
    					/* Randomize goblin monster level within range */
    					monster_level = rand()%GOBLIN_LEVEL_RANGE+GOBLIN_LEVEL_MIN;
    					/* Create new instance of goblin class and assign monster to it */
    					monster = new goblin(monster_name, monster_level);
    					break;
    					
    			}
    			
    			/* Enter battle function with hero and monster */
    			battle(&hero, monster);
    			
    			/* Delete the monster after the battle to free up memory */
    			delete monster;
    			
    			break;
    		case 2:
    			/* Create pointer to an enemy called boss */
    			enemy *boss;
    		
    			/* Set dragon boss monster name */
    			strcpy(monster_name,"Dragon");
    			/* Set dragon boss monster level */
    			monster_level = DRAGON_LEVEL;
    			/* Create new instance of dragon class and assign boss to it */
    			boss = new dragon(monster_name, monster_level);
    			
    			/* Enter battle function with hero and boss */
    			battle(&hero, boss);
    			
    			/* Delete the boss after the battle to free up memory */
    			delete boss;
    			
    			break;
    		case 3:
    			/* Display hero's stats */
    			hero.display_stats();
    			break;
    		case 4:
    			/* Leave the dungeon */
    			cout << "\nYou left the dungeon...you coward...";
    			break;	
    		default:
    			/* Inform user of invalid menu choice */
    			cout << "\nInvalid menu choice.";
    			break;
    	}
    }
    /* End */
    cout << "\n\n";
}

/* Battle function between the player hero and an enemy monster */
void battle(player *hero, enemy *monster)
{
	/*Declare and initialize control variables and health-related variables */
    int choice = 1, battle = 1;
    int damage = 0, recovery = 0;
    
    /* Clear the screen */
    //system("clear");
    
    /* Loop until the battle is over */
    while (battle==1)
    {
    	/* Display hero name and health */
    	cout << "\n\n" << hero->name;
    	cout << "\t" << hero->health << " / " << hero->get_max_health();
    	
    	/* Display monster name and health */
    	cout << "\t\t" << monster->name;
    	cout << "\t" << monster->health << " / " << monster->get_max_health();
    	
    	/* Display battle menu choices */
    	cout << "\n\nBattle:";
    	cout << "\n\t(1) Punch";
    	cout << "\n\t(2) Sword";
    	cout << "\n\t(3) Heal";
    	cout << "\nEnter choice: ";
    	
    	/* Read in user battle menu choice and clear the screen */
    	cin >> choice;
    	system("clear");
    	
    	/* Switch on user battle menu choice */
    	switch (choice)
    	{
    		case 1:
    			/* Retrieve punch damage */
    			damage = hero->punch();
    			/* Decrease monster health by damage */
    			monster->health = monster->health - damage;
    			/* Display weapon message text and damage dealt */
    			cout << "\n\n" << hero->weapon_message;
    			cout << "\nYou deal " << damage << " damage!";
    			break;
    		
    		case 2:
    			/* Retrieve sword damage */
    			damage = hero->sword();
    			/* Decrease monster health by damage */
    			monster->health = monster->health - damage;
    			/* Display weapon message text and damage dealt */
    			cout << "\n\n" << hero->weapon_message;
    			cout << "\nYou deal " << damage << " damage!";
    			break;
    		
    		case 3:
    			/* Retrieve health amount recovered */
    			recovery = hero->heal();
    			/* Increase hero health by amount recovered */
    			hero->health = hero->health + recovery;
    			/* Display recovery message */
    			cout << "\n\nYou heal for " << recovery << " health!";
    			break;
    	}
    	
    	/* Check if the monster has been defeated */
    	if (monster->health <= 0)
    	{
    		/* Display victory message */
    		cout << "\n\nYou defeated " << monster->name << "!";
    		/* Level up hero */
			hero->level_up();
    		/* Set battle control to 0 to end battle */
    		battle = 0;
    	}
    	/* Else the monster has not been defeated */
    	else
    	{
    		/* Retrieve monster attack damage */
    		damage = monster->attack();
    		/* Decrease hero health by damage */
    		hero->health = hero->health - damage;
    		
    		/* Display wound message text and damage taken */
    		cout << "\n\n" << monster->wound_message;
    		cout << "\nYou take " << damage << " damage.";
			
			/* Check if hero has been defeated */
    		if (hero->health <= 0)
    		{
    			/* Display failure message */
    			cout << "\n\nYou are defeated by " << monster->name << "...";
    			/* Refill hero health and display heal message */
    			hero->health = hero->get_max_health();
    			cout << "\nYou heal your wounds...";
    			/*Set battle control to 0 to end battle */
    			battle = 0;
    		}
    	}
    }
}

/* Character constructor function to set name and stats based on input level */
character::character(char nm[25], int l)
{
	/* Set name and level as inputs */
	strcpy(name, nm);
	level = l;
	/* Set health and strength based on level */
	health = level*CHARACTER_HEALTH_TO_LEVEL_RATIO;
	strength = level*CHARACTER_STRENGTH_TO_LEVEL_RATIO;
}

/* Character function to retrieve maximum health based on current level */
int character::get_max_health()
{
	/* Output max health */
	return level*CHARACTER_HEALTH_TO_LEVEL_RATIO;
}

/* Player punch attack function */
int player::punch()
{
	/* Set weapon message text for punch */
	strcpy(weapon_message, "You throw a punch.");
	/* Output randomized punch damage */
	return rand()%(strength*PLAYER_PUNCH_TO_STRENGTH_RATIO);
}

/* Player sword attack function */
int player::sword()
{
	/* Set weapon message text for sword */
	strcpy(weapon_message, "You swing your sword.");
	/* Output randomized sword damage */
	return rand()%(strength*PLAYER_SWORD_TO_STRENGTH_RATIO);
}

/* Player heal function */
int player::heal()
{
	/* Randomly generate amount to heal */
	int hp = rand()%(get_max_health()*PLAYER_HEAL_TO_HEALTH_RATIO);
	/* Check that health does not go over maximum and change amount
		to heal if needed */
	if (health+hp>get_max_health())
	{
		hp = get_max_health()-health;
	}
	/* Output health amount healed */
	return hp;
}

/* Player function to display stats */
void player::display_stats()
{
	/* Display player name, level, health, and strength */
	cout << "\nPlayer Name: " << name;
	cout << "\nPlayer Level: " << level;
	cout << "\nPlayer Health: " << health;
	cout << "\nPlayer Strength: " << strength;
}

/* Player function to update stats upon leveling up */
void player::level_up()
{
	/* Increment level, and update health and strength to new maximums */
	level = level+1;
	health = get_max_health();
	strength = level*CHARACTER_STRENGTH_TO_LEVEL_RATIO;
	/* Print level up message to screen */
	cout << "\nLevel up! Health replenished! Strength increased!";
}

/* Goblin attack function */
int goblin::attack()
{
	/* Set wound message text for goblin attack */
	strcpy(wound_message, "The goblin hits you with a club.");
	/* Output radnomized goblin attack damage */
	return rand()%(strength*GOBLIN_ATTACK_TO_STRENGTH_RATIO);
}

/* Spider attack function */
int spider::attack()
{
	/* Set wound message text for spider attack */
	strcpy(wound_message, "The spider bites you.");
	/* Output randomized spider attack damage */
	return rand()%(strength*SPIDER_ATTACK_TO_STRENGTH_RATIO);
}

/* Dragon attack function */
int dragon::attack()
{
	/* Check if dragon has above half health */
	if (health > get_max_health()/2)
	{
		/* Set wound message text for standard dragon attack */
		strcpy(wound_message, "The dragon attacks you with its claws.");
		/* Output randomized standard dragon attack damage */
		return rand()%(strength*DRAGON_ATTACK_TO_STRENGTH_RATIO);
	}
	/* Else check if dragon has less than half health */
	else if (health <= get_max_health()/2)
	{
		/* Set wound message text for special dragon attck */
		strcpy(wound_message, "The dragon breathes fire on you.");
		/* Output randomized special dragon attack damage */
		/* Note the blank below is the same as the blank above for the standard attack */
		return rand()%(strength*SPIDER_ATTACK_TO_STRENGTH_RATIO)+DRAGON_ATTACK_SPECIAL;
	}
}
