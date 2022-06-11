#include "maps.h" // I include the header file
#include <iostream>
// The main point for this class is to allow the player for options when choosing how they want to play
// The easy method of creating maps only requires a press of a key, as each tile is contained as a part of
// a larger array.
Maps::Maps()
{

}
Maps::Maps(int choice) // This constructor gets called, inputs value into maps::choice
{
}
Maps::~Maps()
{
}
vector< vector<char> > Maps::MapChoice(int choice) //this 2d vector method, returns 2d vector to the level class
{
	if(choice == 1) //Here I purely see what the player decides to choose
	{
char map[15][16]= {{'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W'}, //I use an initialisation list
                   {'W',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ','W'}, //to easily create a visual 
                   {'W',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ','W'}, //interpretation of my levels
                   {'W',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ','W'}, //This allows for easier editing for
                   {'W',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ','W'}, //the programmer
                   {'W',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ','W'},
                   {'W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W'},
                   {'W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W'},
				   {'W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W'},
				   {'W','W','W','W','W','W','W',' ',' ',' ',' ',' ',' ',' ','W'},
				   {'W',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
				   {'W',' ','W','W','W','W','W',' ',' ',' ',' ',' ',' ',' ','W'},
				   {'W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W','W','W','W'},
				   {'W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','B',' ',' ','X'},
					{'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','\0'}};
		GetMap.resize( 16, vector<char>( 16, ' ' ) ); // I now convert the 2d character array to a 2d vector
		for (int iLoop=0; iLoop < 15; iLoop++) //Loops the following FOR loop until iLoop == columns
	{
		for (int iLoop2=0; iLoop2< 15; iLoop2++) ( GetMap[iLoop][iLoop2] = map[iLoop][iLoop2]);//Loops second loop by the number of rows
		cout << "\n";//after every 5 character of the vector, a new line is added for the next row to be added
	};
	}
	else if (choice == 2) //else player chose second map
	{
char map[15][16]= {{'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W'}, /*note the 8 rows*/
                   {'W',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ','W'},
                   {'W',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ','W'},
                   {'W',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ','W'},
                   {'W',' ','W','W',' ',' ','W',' ',' ','W',' ',' ','W',' ','W'},
                   {'W',' ','W','W',' ',' ','W',' ',' ','W',' ',' ','W',' ','W'},
                   {'W',' ',' ',' ',' ',' ','W',' ',' ','W',' ',' ',' ',' ','W'},
                   {'W',' ',' ',' ',' ',' ','W',' ',' ','W',' ',' ',' ',' ','W'},
				   {'W',' ',' ',' ',' ',' ','W',' ',' ','W',' ','W',' ',' ','W'},
				   {'W','W','W','W','W','W','W',' ',' ',' ',' ','W',' ',' ','W'},
				   {'W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ','W'},
				   {'W',' ',' ',' ','W','W','W','W','W','W','W','W',' ',' ','W'},
				   {'W',' ',' ',' ','W',' ',' ',' ','W',' ',' ','W','W','W','W'},
				   {'W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','B',' ',' ','X'},
					{'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','\0'}};
		GetMap.resize( 16, vector<char>( 16, ' ' ) );
		for (int iLoop=0; iLoop < 15; iLoop++) //Loops the following FOR loop until iLoop == columns
	{
		for (int iLoop2=0; iLoop2< 15; iLoop2++) ( GetMap[iLoop][iLoop2] = map[iLoop][iLoop2]);//Loops second loop by the number of rows
		cout << "\n";//after every 5 character of the vector, a new line is added for the next row to be added
	};
	}
	else if(choice == 3)
	{
char map[15][16]= {{'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W'}, /*note the 8 rows*/
                   {'W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W'},
                   {'W',' ',' ',' ',' ',' ','W','W',' ',' ',' ',' ',' ',' ','W'},
                   {'W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W'},
                   {'W',' ',' ','W',' ',' ',' ',' ',' ','W',' ',' ',' ',' ','W'},
                   {'W',' ','W',' ','W',' ',' ',' ','W',' ','W',' ',' ',' ','W'},
                   {'W',' ','W',' ',' ','W',' ','W',' ',' ',' ','W',' ',' ','W'},
                   {'W',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ','W',' ','W'},
				   {'W',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ','W'},
				   {'W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ','W',' ','W'},
				   {'W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ','W'},
				   {'W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W'},
				   {'W',' ','W',' ',' ',' ',' ',' ',' ',' ',' ','W','W','W','W'},
				   {'W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','B',' ',' ','X'},
					{'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','\0'}};
		GetMap.resize( 16, vector<char>( 16, ' ' ) );
		for (int iLoop=0; iLoop < 15; iLoop++) //Loops the following FOR loop until iLoop == columns
	{
		for (int iLoop2=0; iLoop2< 15; iLoop2++) ( GetMap[iLoop][iLoop2] = map[iLoop][iLoop2]);//Loops second loop by the number of rows
		cout << "\n";//after every 5 character of the vector, a new line is added for the next row to be added
	};
	}
	else// default
	{
char map[15][16]= {{'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W'}, /*note the 8 rows*/
                   {'W',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ','W'},
                   {'W',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ','W'},
                   {'W',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ','W'},
                   {'W',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ','W'},
                   {'W',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ','W'},
                   {'W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W'},
                   {'W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W'},
				   {'W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W'},
				   {'W','W','W','W','W','W','W',' ',' ',' ',' ',' ',' ',' ','W'},
				   {'W',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
				   {'W',' ','W','W','W','W','W',' ',' ',' ',' ',' ',' ',' ','W'},
				   {'W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W','W','W','W'},
				   {'W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','B',' ',' ','X'},
					{'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','\0'}};
		GetMap.resize( 16, vector<char>( 16, ' ' ) );
		for (int iLoop=0; iLoop < 15; iLoop++) //Loops the following FOR loop until iLoop == columns
	{
		for (int iLoop2=0; iLoop2< 15; iLoop2++) ( GetMap[iLoop][iLoop2] = map[iLoop][iLoop2]);//Loops second loop by the number of rows
		cout << "\n";//after every 5 character of the vector, a new line is added for the next row to be added
	};
	}

		//I return the new vector named getmap, which is a 2D vector containing the new level that the player has chosen
		return GetMap;
}

char Maps::test(void)
{
	return map[15][16];
}
