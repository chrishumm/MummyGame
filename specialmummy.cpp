#include "specialmummy.h"
#include <iostream>

specialmummy::specialmummy(level * l, int mummy, int y, int x)
{
	currentlevel = l;
}

void specialmummy::mummyMoves(level * l, int mummy, int y, int x) //passes in levelmem address, what mummy is moving
{														   // and the x y pos of that mummy
	w = currentlevel; //Sets local level pointer to the memory address of the level object in use
	mummy_pos_x = x; //Sets the current mummy position 
	mummy_pos_y = y;//

	mummy::mummyno = mummy;//sets mummyno to the mummy that is passed in
	int valid = 0;//keeping the mummy looping
	int obstacle = 0;//sets no obstacles at the moment
	int randnum = 0;//create int randnum for random numbers
	randnum = rand() % 4 + 1;//gets a random number between 1-4
	if(capturedmummies[mummy] == 1)//If the current mummy is captured
	{
		mummy++;//go onto the next mummy
	}
	else//else if the mummy is not captured
	{
	switch(randnum)//start a switch statement to go to the specific movement direction
	{
		case 1:
			valid = validation(randnum); //calls validation method, with the randnum
			if(valid >= 1)//if the validation function is valid
			{
				obstacle = w->Obstacle(mummy_pos_y-2,mummy_pos_x); //check to see what obstacles are in the way
				if(obstacle == 5) //If it's a hole
					capturedmummies[mummy] = 1;//captyure the mummy
				w->moveMummy(5,obstacle, mummy);//else we use our level pointer to move our mummy, passing in obstacle, direction
				randnum = 0;//Reset randnum		//and mummy number
				break;
			}
			mummyMoves(w, mummy,y,x); //else if not valid, call method again until valid(recursive)
			break;

		case 2:
			valid = validation(randnum);
			if(valid >= 1)
			{
				obstacle = w->Obstacle(mummy_pos_y,mummy_pos_x-2);
				if(obstacle == 5)
					capturedmummies[mummy] = 1;
				w->moveMummy(6,obstacle, mummy);
				randnum = 0;
				break;
			}
			mummyMoves(w, mummy,y,x);
			break;

		case 3:
			valid = validation(randnum);
			if(valid >= 1)
			{
				obstacle = w->Obstacle(mummy_pos_y,mummy_pos_x+2);
				if(obstacle == 5)
					capturedmummies[mummy] = 1;
				w->moveMummy(7,obstacle, mummy);
				randnum = 0;
				break;
			}
			mummyMoves(w, mummy,y,x);
			break;
		case 4:
			valid = validation(randnum);
			if(valid >= 1)
			{
				obstacle = w->Obstacle(mummy_pos_y+2,mummy_pos_x);
				if(obstacle == 5)
					capturedmummies[mummy] = 1;
				w->moveMummy(8,obstacle, mummy);
				randnum = 0;
				break;
			}
			mummyMoves(w, mummy,y,x);
			break;
		
		default: //if none, loop the above code
			break;
	}
	}
}

int specialmummy::validation(int num) //takes an int num from movemummy
{
		int temp = 0; //temp integer for returning
		switch(num)//starts a switch statement, depending where the mummy is moving
	{
		case 1://if up,
			if(w->wallCheck(1,2,mummyno) == 1) //uses our level pointer again to access wallcheck method
			{								
						return 0;			//If wallcheck returns 1, return 0 to movemummy
			}
			else
				return 1; //if wallcheck is valid, return 1 to movemummy method as valid movement
			break;

		case 2:
			if(w->wallCheck(2,2,mummyno) == 1)
			{
						return 0;
			}
			else
				return 1;
			break;
		case 3:
			if(w->wallCheck(3,2,mummyno) == 1)
			{
					return 0;
			}
			else
				return 1;
			break;

		case 4:
			if(w->wallCheck(4,2,mummyno) == 1)
			{
					return 0;
			}
			else
			return 1;
			break;
	}
}
