#include "player.h" //
#include "level.h"	//Compisition 
#include <iostream>
#include <conio.h>
#include <cstdlib>
using namespace std;


player::player(level* m) //constructor assigns the level object memory address to our level pointer
{
	ptr = m;
}

player::~player() //we delete the ptr to avoid null pointers
{
	ptr = NULL;
}
void player::moveCharacter() //our main movecharacter method that is called from level
{
	int valid = 0; //used to keep loop running
	int obstacle = 1;//default obstacle value
	char temp = ' ';//temporary value for user input
	cout << "\nPress W for forward, A for left, D for right or S for down\r";
	while(valid != 1)
	{
	temp = _getch();//gets input
	switch(temp)//start switch statement for our input
	{
		case 'W'://Using two cases, I can grab multiple inputs instead of just one
		case 'w'://I use upper and lowercase for compatability
			valid = validation(temp); //we call our validation method
			if(valid >= 1)//if the input is valid
			{
				obstacle = ptr->Obstacle(ptr->getPosCoordy(1,-1)-1,ptr->getPosCoordx(1,-1)); //call the level obstacle method, using getposition methods!
				ptr->moveCharacter(1,obstacle, 0);//Call movement method from level, with direction, obstacle and blank.
				
				break;
			}
			//moveCharacter(); //else if not valid, call this method again (recursive)
			break;

		case 'A':
		case 'a':
			valid = validation(temp);
			if(valid >= 1)
			{
				obstacle = ptr->Obstacle(ptr->getPosCoordy(1,-1),ptr->getPosCoordx(1,-1)-1);
				ptr->moveCharacter(2,obstacle, 0);
				break;
			}
		//	moveCharacter();
			break;

		case 'D':
		case 'd':
			valid = validation(temp);
			if(valid >= 1)
			{
				obstacle = ptr->Obstacle(ptr->getPosCoordy(1,-1),ptr->getPosCoordx(1,-1)+1);
				ptr->moveCharacter(3,obstacle, 0);
				break;
			}
		//	moveCharacter();
			break;
		
		case 'S':
		case 's':
			valid = validation(temp);
			if(valid >= 1)
			{
				obstacle = ptr->Obstacle(ptr->getPosCoordy(1,-1)+1,ptr->getPosCoordx(1,-1));
				ptr->moveCharacter(4,obstacle, 0);
				break;
			}
			//moveCharacter();
			break;
		case 'h': //if the player chooses to dig
		case 'H':
			valid = 1;
			dig(); //call dig method
		default:// else loop
			break;
	}
	}
	
}

int player::validation(char direction) //this method validates all user inputs for moveplayer
{										// I take a char variable depending on the direction
	int temp = 0;
	int y = ptr->getPosCoordy(1,-1); //I get the position from level for our current player positions
	int x = ptr->getPosCoordx(1,-1);
		switch(direction) //I use the character decision to check which direction the player is heading
	{
		case 'W'://again, I use this for compatability
		case 'w'://
			if(ptr->wallCheck(1,1,-1) == 1) //I call the wallcheck method, first number denotes the player,
			{								// second number shows direction and third is used for mummies, so it's unused
						return 0; //if player moves into invalid object, return 0
			}
			else
				return 1; // else if the players new position is valid, return 1
			break;

		case 'A':
		case 'a':
			if(ptr->wallCheck(2,1,-1) == 1)
			{
						return 0;
			}
			else
				return 1;
			break;
		case 'D':
		case 'd':
			if(ptr->wallCheck(3,1,-1) == 1)
			{
					return 0;
			}
			else
				return 1;
			break;

		case 'S':
		case 's':
			if(ptr->wallCheck(4,1,-1) == 1)
			{
					return 0;
			}
			else
			return 1;
			break;
	}
}

void player::dig() //this is the dig function that is called when player presses 'h'
{
	if(m_no_of_spades < 1) //checks to see if the player has spades to begin with
	{
		cout << "\nGet more spades!"; //if no spades are found, output error message
	_getch();							// use getch so player reads message
	}
	else //else player has spades
	{
	m_no_of_spades--; //deincrement the static variable spades
	ptr->moveCharacter(0,0,0);//call movement method specific for the dig method
	}						  //I use 0,0,0 as i'm not moving in any direction
}
