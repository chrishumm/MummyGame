#include <iostream>
#include "level.h"
#include "player.h"
#include "mummy.h"
#include <windows.h>
#include "GameConditions.h"
#include <vector>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maps.h" //so we can load new maps for our game
#include <windows.h>
#include <mmsystem.h> 
#include <exception> //for throwing exceptions and catching errors
#pragma comment(lib,"winmm.lib") // this allows my program to use the library that allows music to be played
using namespace std; //So I don't have to type std::
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////Globals////////////////////////////////////////////////////////////
enum music					  //
{dungeon = 1, finish} playing;// I create an enumeration for music, so I can differentiate between dungeon and
//when the game is finished. This could be expanded upon if I were to expand my game.
int level::turn = 1;          //Static Variables that are accessable to entire program
int level::mummy_turn = 0;    //These are declared once, I use increment and decrement
int level::m_no_of_spades= 2; //operators to change them. I use level:: prefix to show
int level::caughtmummies = 0; //tht these variables belong to the level class
unsigned int level::TrappedMummies[6]; // This is to keep count of how many mummies I have caught
player* newplayer; //These two class pointers allow me to dynamically create new objects when
mummy* newmummy[6];//I'm playing. I have a maximum of six mummies, so I create an array of pointers.

/////////////////////////////////////////Methods//////////////////////////////////////////////////////////////
level::level()
{			//Default constructor is defined for basic programming purposes
}
level::level(int bar, int mummy, int lives, int choice) //This constructor is based on four parameters
{														//They are passed in from the game object, which can be altered
														//in options. The choice variable also denotes what map I will
	//system("color fc");								//be using.
	Maps NewMap(choice); //I create a new map object, using my choice integer as a parameter
	world = NewMap.MapChoice(choice);//This fetches the newmap method to return the vector contents into our level vector
	system("CLS");//This clears the screen of any previous data
	m_music = dungeon;//I set the music equal to the dungeon music, for later use.
	playMusic(*this);//I use a This pointer to my playMusic method, showing I want music to be played in the memory address of this object
	srand ( (unsigned int)time(NULL) ); //Seeding for random numbers later
	m_no_of_energybars = bar;//
	m_no_of_lives = lives;   //These three assign the members of level with the variable values we have passed in from
	m_no_of_mummies = mummy; // the game function.
	player_pos_x = 0;        //
	player_pos_y = 0;        //These two variables temporary set our player location to 0 when we create a level
	try
	{
		newplayer = new player(this);//This dynamically creates a new player object, passing in the value of our current level object.
	}
	catch(bad_alloc&)
	{
		cout << "Error, memory corruption!";
		_getch();
		exit(1);
	}
	generateLevel(); //This calls the generate level method
	for(;;) //This is an infinite For loop, see the lack of any other parameters
	{
		displayLevel(); //These two will be our main methods that allow our game to flow seemlessly.
		displayHud();   //These are constantly called upon when we play our game
	}
}
level::~level() //When our level object is destroyed, these will be called upon.
{
	/*
	delete newplayer;
	newplayer = NULL; //Assigns any newplayer points to null.
	
	for(int i = 0; i < m_no_of_mummies;i++)
	{
		delete newmummy[i];
		newmummy[i] = NULL;
	}
	*/
}

level::level(int bar, int mummy, int lives) //another basic constructor, used when we call it in game
{
	bar = bar;
	mummy = mummy;
	lives = lives;
}
void level::generateLevel() //This is our generate level method in level class.
{
int posx, posy; //Define two integers for position
	int  temp = rand() % 4 + 10; // These two temps will be used for our x and y axis spawning for the player
	int  temp2 = rand() % 4 + 10; // I have decided the player to spawn roughly in the same bottom place.
	for(int i = 0; i < 2;) //For loop, looping twice.
	{
	if(world[temp][temp2] == 'W' || world[temp][temp2] == 'B'|| temp > 11 && temp2 > 11) 
		{																				
			temp = rand() % 10 + 2;			//This if statement ensures my player does not spawn in the wall,
			temp2 = rand() % 10 + 2;		//or in the area near the exit, so new coordinates are generated
		}
	else //else the position is valid
		{
			i = 5;//This breaks the loop
			ptr = &world[temp][temp2];//we assign our vector pointer to the current vector and coordinates
			*ptr = 'P';//we use reference to change the value in the vector that the pointer is pointing to
			ptr = NULL;//We stop the pointer from pointing at that memory address
		}
	}
	int temp4 = rand() % 10 + 2;//Here I define another set of random integers
	int temp3 = rand() % 10 + 2;//These are for the mummies position

	for(int i = 0; i < m_no_of_mummies;)//Here we start a for loop, looping depending on how many
	{									//mummies we have chosen.
	if(world[temp4][temp3] == 'W' || temp4 == 12 && temp3 == 12 || world[temp4][temp3] == 'P') 
		{ 
			temp4 = rand() % 10 + 2;//Once again, same as the players spawning
			temp3 = rand() % 10 + 2;//This time we now include player as an invalid space
		}
	else //if valid..
		{
			mummy_pos_y[i] = temp4;//the current mummy now is assigned an x
			mummy_pos_x[i] = temp3;//and y position
			try
			{
				newmummy[i] = new mummy(mummy_pos_y[i],mummy_pos_x[i]); //We create new object for this mummy
			}
			catch(bad_alloc&)
			{
				cout << "Error, memory is corrupted";
				_getch;
				exit(0);
			}
			i++;//this increments our i variable
			ptr = &world[temp4][temp3];//same as before, we point the pointer at our vector
			*ptr = 'M';//we assign the value that the pointer is pointing to to 'M'
			ptr = NULL;// and finally we stop the pointer pointing at that object
			temp4 = rand() % 10 + 2; //We now assign new values to our temps for mummy
			temp3 = rand() % 10 + 2;// this is because we can have multiple mummies in one game
		}
	}

	//Now we spawn our objects
		for(int i = 0; i < m_no_of_energybars;) 
	{
		posy = rand() % 10 + 3; //I used the posy and posx from earlier for all item spawnns
		posx = rand() % 10 + 3; //I follow a similar random method, but make sure they are not too close to the player
	if(world[posy][posx] == 'W' || posy == 12 && posx == 12 || world[posy][posx] == 'P' || world[posy][posx] == 'M' ||  world[posy][posx] == 'E')
		{
			posy = rand() % 10 + 2; //Now we add the mummy to the blacklist
			posx = rand() % 10 + 2; // Because we spawn more than one energy bar, we must also add that
		}
	else if(i == m_no_of_energybars) //If it reaches the limit, do nothing and continue
		{
	
		}
	else //if input is valid
		{
			i++; //increment for our loop
			ptr = &world[posy][posx]; //
			*ptr = 'E';				  // Assign value using pointer
			ptr = NULL;				 //
		}
	}
	//		Assigning spades
		for(int i = 0; i < rand() % 3;) //I wanted random spade spawns to make each game unique
	{
		posy = rand() % 10 + 3;
		posx = rand() % 10 + 3;
		if(world[posy][posx] == 'W' || posy == 12 && posx == 12 || world[posy][posx] == 'P' || world[posy][posx] == 'M' || world[posy][posx] == 'E' || world[posy][posx] == 'S')
		{
			posy = rand() % 10 + 2; //Much like before, checking to see if the space in the vector is empty and valid
			posx = rand() % 10 + 2;
		}
		else // if valid..
		{
			i++;//icrement for our loop
			ptr = &world[posy][posx];  //
			*ptr = 'S';				  //Assign value via pointer.
			ptr = NULL;				 //
		}
		delete ptr; //We do not need the pointer now, so to avoid null pointers, I delete it.
		ptr = NULL;	
	}
		cout << "Loading! Please wait..."; //This outputs a message whilst this is happening
		player_pos_x = temp2; //Now I officially assign the member values in level
		player_pos_y = temp; // to the temp player values from earlir
	}
void level::displayLevel()
{
	system("CLS"); //I clear the screen again 
	for (int iLoop=0; iLoop < 16; iLoop++) //Loops the following FOR loop until iLoop == columns
	{
		for (int iLoop2=0; iLoop2< 16; iLoop2++) //I use a double for loop here to output a 2D vector
			if(world[iLoop][iLoop2] == 'P')		//The following code is to detect individual characters
			{
				setColour(2); //If I have found the player tile, colour the player
				cout << " " << world[iLoop][iLoop2]; //Add a space, then output the current position
				setColour(15);//Resort back to the default colour
			}
			else if (world[iLoop][iLoop2] == 'M')
			{
				if(mummy_pos_y[1] == iLoop && mummy_pos_x[1] == iLoop2 || mummy_pos_y[3] == iLoop && mummy_pos_x[3] == iLoop2 || mummy_pos_y[5] == iLoop && mummy_pos_x[5] == iLoop2)
				{
					setColour(1);
				}
				else
				{
				setColour(4);//If I have found the monster tile, colour the monster
				}
				cout << " " << world[iLoop][iLoop2];
				setColour(15);
			}
			else if(world[iLoop][iLoop2] == 'E')
			{
				setColour(5);//If I have found the energy bar tile, colour the energy bar
				cout << " " << world[iLoop][iLoop2];
				setColour(15);
			}
			else if(world[iLoop][iLoop2] == 'W')
			{
				setColour(8);//If I have found the wall tile, colour the wall
				cout << " " << world[iLoop][iLoop2];
				setColour(15);
			}
			else if(world[iLoop][iLoop2] == 'S')
			{
				setColour(6);//If I have found the spade tile, colour the spade
				cout << " " << world[iLoop][iLoop2];
				setColour(15);
			}
			else{cout << " " << world[iLoop][iLoop2];}; //else all other characters are default
		//Loops second loop by the number of rows
		cout << "\n";//after every 5 character of the vector, a new line is added for the next row to be added
	}
		cout <<"\n" << "This is " << turn << " turn." << " You have " << m_no_of_energybars << " energy bars remaining.\nYou have " << m_no_of_spades << " spades left, press H to dig a hole!\nYou have " << m_no_of_lives <<" lives left!\n";
} //This outputs the current turn, the current number of energy bars and level.

void level::moveCharacter(int x, int obstacle, int y) //This accepts three variables called from player class.
{	//First variable is the direction the player moves, second what obstacle the player have walked into and third
	p_y = &player_pos_y; // I can assign values to player_pos_y via pointers
	p_x = &player_pos_x;
	if(world[*p_y][*p_x] == 'P') //If the current player position contains player
	{
		world[*p_y][*p_x] = ' ';//Hide player. This is useful to avoid duplicate p's on the board
	}
	else if(world[*p_y][*p_x] == 'H') //If I used the dig method, I don't render myself invisible
	turn++; //Increment turn as I have moved a space 
	if(x == 0 && obstacle == 0) //This is reserved for dig method
	{
		world[*p_y][*p_x] = 'H';//PLace the current player position to be a hole and do not move
	}
	if(x == 1 && obstacle != 4) //Obstacle four is reserved for the boulder, so I ensure I do not include that here
	{						   //If I have chosen to move upwards
		(*p_y)--;//I use parathensis in order to execute my code properly, according to order of precedence 
		world[*p_y][*p_x] = 'P';//the new player position is now created, so I add p in the position in the vector
	}
	if(x == 2 && obstacle != 4) //If I have chosen to move left
	{
		(*p_x)--;
		world[*p_y][*p_x] = 'P';
	}
	if(x == 3 && obstacle != 4) //If I have chosen to move right
	{
		(*p_x)++;
		world[*p_y][*p_x] = 'P';
	}
	if(x == 4 && obstacle != 4) //If I have chosen to move downwards
	{
		(*p_y)++;
		world[*p_y][*p_x] = 'P';
	}
	if(obstacle == 4) //If the obstacle is a boulder
		if(m_no_of_energybars == 0)//I check to see if their are any energy bars left
		{
			this->player_pos_x++; //If correct, I move the player position right
			world[*p_y][*p_x] = 'P'; // I add a new P to denote the player
		}
		else //if it is invalid
		{
			world[*p_y][*p_x] = 'P'; //recreate the P in current position
			cout <<  "\nEat more energy bars!"; //Output a message to eat more
		}
	if(obstacle == 3) //If the player runs into a mummy
		{
			world[*p_y][*p_x] = 'M';//the player is replaced by an 'M'
			m_no_of_lives--;//I decrement the lives
			player_pos_y = rand() % 2 + 10; // I generate random positions again
			player_pos_x = rand() % 2 + 10; // for our player to respawn
			while(respawnPlayer(&player_pos_y,&player_pos_x) != 1); //I use validation to ensure this is correct
			world[*p_y][*p_x] = 'P'; //If returns correct, I assign the new position a 'P'
		}	//due to this not being output, if player has -1 lives, I deal with this at the end of this method
	if(obstacle == 5)//If the player falls into a hole..
		{
			world[*p_y][*p_x] = 'H'; //player position becomes a hole
			player_pos_y = rand() % 2 + 10; //respawning player
			player_pos_x = rand() % 2 + 10; //
			while(respawnPlayer(&player_pos_y,&player_pos_x) != 1); //validating player via respawn method using loop
			world[*p_y][*p_x] = 'P'; //if returns valid, position in vector is now 'P'
			m_no_of_lives--; //deincrement the lives
		}
	if(obstacle == 6) //if player walks over a spade
		{
			m_no_of_spades++; //increment spades

		}
	if(obstacle == 7)//if player walks over an energy bar
	{
		m_no_of_energybars--;//deincrement static variable for energy bars
	}
	if(obstacle == 8) //if player has reached the end
	{
		for(int i = 0;i < m_no_of_mummies;i++) //start a for loop
		{
			if(TrappedMummies[i] == 1)//check static int array to see what mummies are caught
				caughtmummies++; //increment int caught mummies 
			else //else do nothing
			{}
		}

	delete newplayer;
	newplayer = NULL; //Assigns any newplayer points to null.
	for(int i = 0; i < m_no_of_mummies;i++)
	{
		delete newmummy[i];
		newmummy[i] = NULL;
	}
		p_x = NULL;
		p_y = NULL;

		mciSendString("stop C:\\Windows\\Media\\onestop.mid",NULL,0,NULL); //Stop dungeon music
		this->m_music = finish; //Change m_music to finish, for our end game theme
		playMusic(*this); //call playmusic method again to update
		GameConditions message1(this->m_no_of_energybars, caughtmummies, this->m_no_of_lives); //create a new object for gameconditions
	}																						  //passing in our variables for our winning screen
	else if(m_no_of_lives <= 0)//else if lives are 0 or less than 0
	{
	delete newplayer;
	newplayer = NULL; //Assigns any newplayer points to null.

	for(int i = 0; i < m_no_of_mummies;i++)
	{
		delete newmummy[i];
		newmummy[i] = NULL;
	}
		p_x = NULL;
		p_y = NULL;
	
		mciSendString("stop C:\\Windows\\Media\\onestop.mid",NULL,0,NULL); //stops the music
		this->m_music = finish; 
		playMusic(*this);
		GameConditions message1(this->m_no_of_energybars, caughtmummies, this->m_no_of_lives);
	}
	else{} //do nothing
	turn++;//increment turn
	if(turn  % 2 == 1) //if modudlo % 2 has a remainer of 1, execute following code
	{				  //this allows me to have our mummy move everyone other turn
		for(int i = 0;i < m_no_of_mummies;i++) //incrementing each mummy
		{
		if(TrappedMummies[i] == 1) //if our mummy is currently caught
		{i++;} //do nothing, move onto next mummy
		else
		{
		newmummy[i]->mummyMoves(this, i,mummy_pos_y[i],mummy_pos_x[i]); //access mummymoves method
		}																//via class pointer, for that mummy
		}
	}
	displayLevel(); //we display the level and hud methods.
	displayHud();
}

void level::moveMummy(int x, int obstacle, int mummy) //For this, we pass in the direction, obstacle and mummy number
{
	int jump = 1;
	if(mummy % 2 == 1)
	{
		jump = 2;
	}
	world[mummy_pos_y[mummy]][mummy_pos_x[mummy]] = ' '; //We render our mummy invisible, so no duplicate mummies
	if(obstacle == 5)//If the mummy walks into a hole
	{
		TrappedMummies[mummy] = 1; //assign the current mummy in the static int array to 1
		newmummy[mummy]->~mummy();//Call mummy destructor for that object in the array
	}
	if(x == 5) //These are the basic movement directions for our mummy // Up
	{
		for(int i = 0;i < jump;i++)
		{
		this->mummy_pos_y[mummy]--; //Follows same principle for move character method of movement
		}
		world[mummy_pos_y[mummy]][mummy_pos_x[mummy]] = 'M';//replaces new position with 'm'
	}
	if(x == 6) //left
	{
		for(int i = 0;i < jump;i++)
		{
		this->mummy_pos_x[mummy]--;
		}
		world[mummy_pos_y[mummy]][mummy_pos_x[mummy]] = 'M';
	}
	if(x == 7) //right
	{
		for(int i = 0;i < jump;i++)
		{
		this->mummy_pos_x[mummy]++;
		}
		world[mummy_pos_y[mummy]][mummy_pos_x[mummy]] = 'M';
	}
	if(x == 8)//down
	{
		for(int i = 0;i < jump;i++)
		{
		this->mummy_pos_y[mummy]++;
		}
		world[mummy_pos_y[mummy]][mummy_pos_x[mummy]] = 'M';
	}
	if(obstacle == 9)//If the mummy walks into the player..
	{
			world[player_pos_y][player_pos_x] = 'M';//player position in vector now places 'M'
			player_pos_y = rand() % 2 + 10;//Random numbers
			player_pos_x = rand() % 2 + 10;//for player respawn
			while(respawnPlayer(&player_pos_y,&player_pos_x) != 1);//calls respawnplayer function
			world[player_pos_y][player_pos_x] = 'P';//adds in new 'P' to respawned position
			m_no_of_lives--;//deincrement players lives
	}

	 while(mummy_turn < m_no_of_mummies-1)// This while loop ensures every mummy is moved on each turn
	{
		mummy_turn++;//increments through each mummy
		newmummy[mummy_turn]->mummyMoves(this,mummy_turn,mummy_pos_y[mummy_turn],mummy_pos_x[mummy_turn]); //calls mummymove method
	}
	mummy_turn = 0; //Once all have been moved, it resets to 0
	displayLevel();//Calls display level and hud methods
	displayHud();//
}

void level::displayHud()//display hud creates our character and outputs our instructors
{
	try
	{
    newplayer = new player(this);//we dynamically create our player each time, with the memory address of the current level object
	}
	catch(bad_alloc&)
	{
		cout << "Error! Memory corruption";
		_getch();
		exit(1);
	}
	newplayer->moveCharacter();//we then call upon the movecharacter method to get input seemlessly
}

int level::getPosCoordy(int i, int mummy) //returns coordinates for player and mummy
{
	if(i = 1) //if player?
	{
	return player_pos_y; //return y coordinates
	}
	else if(i = 2) //if mummy?
	{
	return mummy_pos_y[mummy]; //return current mummy numbers coorindates via mummy integer
	}
}

int level::getPosCoordx(int i,int mummy) 
{
	if(i = 1)
	{
	return player_pos_x;
	}
	else if(i = 2)
	{
	return mummy_pos_x[0];
	}
}

int level::Obstacle(int y, int x) //Our obstacle list. Contains the "next" place our mummy or player wants to move
{
	int temp = 0; //assign temp value that we want to return
	if(world[y][x] == 'M')
		temp = 3;
	else if(world[y][x] == 'B')
		temp = 4;
	else if(world[y][x] == 'H')//
		temp = 5;			   //this basic list gives us a "code" that we can send to our moveplayer/mummy methods
	else if(world[y][x] == 'S')//It allows us to set certain conditions when our character moves into a certain object
		temp = 6;			   //We can define these conditions in movement methods. This list allows new objects to be
	else if(world[y][x] == 'E')//added easily, with their own code. So expanding upon this in the future is easy
		temp = 7;			   //It reduces the need to look up the specific object in the movement method, keeping code clean
	else if(world[y][x] == 'X')//and also move efficient.
		temp = 8;
	else if(world[y][x] == 'P')
		temp = 9;
	else{temp = 1;} //If no obstacle is found, return 1 denoting empty space
	return temp;//returns temp.
}

int level::wallCheck(int code, int c, int mummy) //This takes in is player/mummy, direction and mummy number
{
	int jump = 1;
	if(mummy % 2 == 1)
	{
		jump = 2;
	}
	if(code == 1 && c == 1) //c 1 means player
	{
		if(world[player_pos_y-jump][player_pos_x] == 'W') //I check to see if the next tile is a wall
		{
			return 1; //I return 1 to the class, meaning the validation method will be called,
		}
	}
	else if(code == 2 && c == 1)
	{
		if(world[player_pos_y][player_pos_x-jump] == 'W')
		{
			return 1;
		}
	}
	else if(code == 3 && c == 1)
	{
		if(world[player_pos_y][player_pos_x+jump] == 'W')
		{
			return 1;
		}
	}
	else if(code == 4 && c == 1)
	{
		if(world[player_pos_y+jump][player_pos_x] == 'W')
		{
			return 1;
		}
	}
	//
		if(code == 1 && c == 2) //c 2 means mummy
	{
		if(mummy_pos_y[mummy]-jump < 0)
		{return 1;}
		else if(world[mummy_pos_y[mummy]-jump][mummy_pos_x[mummy]] == 'W' || world[mummy_pos_y[mummy]-jump][mummy_pos_x[mummy]] == 'B' || world[mummy_pos_y[mummy]-jump][mummy_pos_x[mummy]] == 'S'|| world[mummy_pos_y[mummy]-jump][mummy_pos_x[mummy]] == 'E' || world[mummy_pos_y[mummy]-jump][mummy_pos_x[mummy]] == 'M'|| world[mummy_pos_y[mummy]-jump][mummy_pos_x[mummy]] == 'X')
		{
			return 1; //I do the same with mummy, but I allow the mummy to move into much less objects.
		}			  //I also use the mummy number for each position, to ensure I calculate each mummies collision.
	}
	else if(code == 2 && c == 2)
	{
		if(mummy_pos_x[mummy]-jump < 0)
		{return 1;}
		else if(world[mummy_pos_y[mummy]][mummy_pos_x[mummy]-jump] == 'W' || world[mummy_pos_y[mummy]][mummy_pos_x[mummy]-jump] == 'B' || world[mummy_pos_y[mummy]][mummy_pos_x[mummy]-jump] == 'S' || world[mummy_pos_y[mummy]][mummy_pos_x[mummy]-jump] == 'E' || world[mummy_pos_y[mummy]][mummy_pos_x[mummy]-jump] == 'M'|| world[mummy_pos_y[mummy]][mummy_pos_x[mummy]-jump] == 'X')
		{
			return 1;
		}
	}
	else if(code == 3 && c == 2)
	{
		if(mummy_pos_x[mummy]+jump > world.size()-2)
		{return 1;}
		else if(world[mummy_pos_y[mummy]][mummy_pos_x[mummy]+jump] == 'W' || world[mummy_pos_y[mummy]][mummy_pos_x[mummy]+jump] == 'B' || world[mummy_pos_y[mummy]][mummy_pos_x[mummy]+jump] == 'S' || world[mummy_pos_y[mummy]][mummy_pos_x[mummy]+jump] == 'E' || world[mummy_pos_y[mummy]][mummy_pos_x[mummy]+jump] == 'M'|| world[mummy_pos_y[mummy]][mummy_pos_x[mummy]+jump] == 'X')
		{
			return 1;
		}

	}
	else if(code == 4 && c == 2)
	{
		if(mummy_pos_y[mummy]+jump > world.size()-2)
		{return 1;}
		else if(world[mummy_pos_y[mummy]+jump][mummy_pos_x[mummy]] == 'W' || world[mummy_pos_y[mummy]+jump][mummy_pos_x[mummy]] == 'B' || world[mummy_pos_y[mummy]+jump][mummy_pos_x[mummy]] == 'S' || world[mummy_pos_y[mummy]+jump][mummy_pos_x[mummy]] == 'E' || world[mummy_pos_y[mummy]+jump][mummy_pos_x[mummy]] == 'M'|| world[mummy_pos_y[mummy]+jump][mummy_pos_x[mummy]] == 'X')
		{
			return 1;
		}
	}
	else
		return 0; //If everything is fine and no walls/invalidobstacles are detected, i return 0
}

void level::setColour(int color)// I create a setcolour method that allows me to change colour on the fly
{								//I take an integer that represents a certain colour
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);//using an inbuilt function into windows.h
}																	//I change the specific colour of the character

bool level::respawnPlayer(int *y, int *x)// I take two pointer variables that point to the generated position
{
	int valid = 0;//Creates integer for our while loop
	while(valid != 1)
	{
		if(world[*y][*x] == 'E' || world[*y][*x] == 'S' || world[*y][*x] == 'M' || world[*y][*x] == 'W')
			{
				*y = rand() % 2 + 10; //much like the generate method, I generate new values for our pointers
				*x = rand() % 2 + 10; //integer that they're pointing to, ensuring the new position is valid
			}
		else //if the new position is valid
		{
			valid =1;//I break the looop
		}
	}
	return 1; //I return 1, breaking the respawnplayer loop in other methods.
}

void playMusic(level &access) //I take the memory address of our current object and pass it into the playmusic
{
	mciSendString("stop C:\\Windows\\Media\\flourish.mid",NULL,0,NULL);
	if(access.m_music == dungeon)//I see if the m_music member variable is equal to dungeon enumeration value
	{
		mciSendString("play C:\\Windows\\Media\\onestop.mid",NULL,0,NULL); // I play the current music
	}
	else if(access.m_music == finish) //Else I check if m_music is equal to the endgame/finish music
	{
		mciSendString("play C:\\Windows\\Media\\flourish.mid",NULL,0,NULL); //I play that
	}
	else //else do nothing
	{

	}
} //I designed this section so it would be easier to add music to the enumeration and this method, giving more control to the programmers.
