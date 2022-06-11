#include "options.h"//includes the options header
#include <iostream>
#include <cstdlib>
#include <conio.h>
using namespace std;

options::options(int mbar, int mmummy, int mlives) : game(mbar,mmummy,mlives)
{
	bar = mbar;		  //Assigns our local variables in the options class
	mummy = mmummy;   //inherit the values from game
	lives = mlives;   //
	options::omenu(); //
}

options::~options()
{
}
void options::omenu()  //output menu method
{
	for(;;) //we start our infinite for loop
	{
	system("CLS");//clears the screen
	string sDecision = " ";//Create a string for validation
	cout << "Welcome to the options! \n\n1) Change Energy Bars\n2) Change Mummies\n3) Change Lives\n4) Back";
	sDecision = _getch(); //Here we output our menu message and get input into our sdecision variable via _getch
	char *x = (char*)sDecision.c_str();//we convert the character stored in the string via character pointer
	switch(*x)//now we can use the value in our switch statement via pointer
	{
		case '1'://if the user chose 1
			x = NULL;//point the pointer to nothing
			delete x;//delete the pointer
			change = &bar;
			newbars(*change);//call the newbar method 
		break;
		case '2':
			x = NULL;
			delete x;
			change = &mummy;
			newmummy(*change);
		break;
		case '3':
			x = NULL;
			delete x;
			change = &lives;
			newlives(*change);
		break;
		case '4':
			x = NULL;
			delete x;
			change = NULL;
			delete change;
			game(bar,mummy,lives,1);
		default:
			sDecision = validation(sDecision); //if none of the options are correct, call the validation method
		break;
	}
	}
	}
	

int options::newbars(int temp) //This outputs intstructions to the screen for changing new energy bars. I use the same system for all of 
{								// my objects/items in game
	system("CLS");// clears the screen	
	cout << "There are currently " << temp << " amount of energy bars. \n\nPlease enter a new value: "; //asks for user inpiut
while((!(cin >> temp)) || temp > 6 || temp < 1) //while the input is not a number
{
cout <<"Please enter a valid number and continue: "; //Displays instructions //Takes user input again, hoping they conform to rules
cin >> temp; //using cin, i get input into the temp variable
cin.clear();//resets error flag. We do this AFTER input (otherwise line will loop)
cin.ignore(100,'\n'); //Ignores 100 characters input and adds a new line (so error message doesn't spill over)
//loops back around until correct input
}
	bar = temp; //sets the bar variable to the value in temp
	return bar;//returns bar
}

int options::newmummy(int temp)
{
	system("CLS");
	cout << "There are currently " << temp << " amount of mummys. \n\nPlease enter a new value: ";
while((!(cin >> temp)) || temp > 5 || temp < 0) //while the input is not a number
{
cout <<"Please enter a valid number and continue: "; //Displays instructions //Takes user input again, hoping they conform to rules
cin >> temp;
cin.clear();//resets error flag. We do this AFTER input (otherwise line will loop)
cin.ignore(100,'\n'); //Ignores 100 characters input and adds a new line (so error message doesn't spill over)
//loops back around until correct input
}
	mummy = temp;
	return mummy;
}

int options::newlives(int temp)
{
	system("CLS");
	cout << "You currently have " << temp << " lives. \n\nPlease enter a new value: ";
while((!(cin >> temp)) || temp < 1 || temp > sizeof(int)) //while the input is not a number, below 1 or above maximum size of integer
{
cout <<"Please enter a valid number and continue: "; //Displays instructions //Takes user input again, hoping they conform to rules
cin >> temp;
cin.clear();//resets error flag. We do this AFTER input (otherwise line will loop)
cin.ignore(100,'\n'); //Ignores 100 characters input and adds a new line (so error message doesn't spill over)
//loops back around until correct input
}

	lives = temp;
	return lives;
}

string options::validation(string s_string) //my validation function for menu, acts identical to my game validatio 
{
	string temp = " "; //create temp string
	string valid[4] = { "1", "2", "3", "4"}; //these are valid inputs
	bool success = 0;//use variable to keep loop running
	while(success != 1)//start while loop
	{
	system("CLS"); //clears the screen
	cout << s_string << " is an invalid input! Please input a valid option: \n"; //shows players input as invalid
	cout << "Welcome to the options! \n\n1) Change Energy Bars\n2) Change Mummies\n3) Change Lives\n4) Exit";
	temp = _getch(); //gets input
	
	for(int i = 0; i < 4; i++)				//
	{										//Using inbuilt string function
		if(temp.compare(valid[i]) != 1)		//I compare the value in temp to each of
		{									//the valid members in the valid array
			success = 1;					//
			break;
		}
		else;
	}
	cin.sync(); //sync and clear the stringstream
	cin.clear();
	}
	s_string = temp;	//Return the valid input
	return s_string;	//
}
