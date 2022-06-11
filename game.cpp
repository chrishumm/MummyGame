#include <iostream>	//cout/etc
#include <cstdlib>	//clearing screen
#include <conio.h>	//_getch
#include "game.h"  //includes header file
#include "level.h" //compisition
#include "options.h"
#include <sstream> //stringstream
#include <fstream> //reading/writing file
using namespace std; //no need to type std::
options * newopt;
stringstream ss; //write things in and out of the stringstream

game::game() //defaults for starting the game
{
	 Menu(); //calls menu method
}
game::game(int bar, int mummy, int lives, int firststart) //constructor that interacts with options
{
	 m_no_of_mummies = mummy;
	 m_no_of_energybars = bar;
	 m_no_of_lives = lives;
	 Menu();
}
game::game(int bar, int mummy, int lives) //constructor that interacts with options
{
	 m_no_of_mummies = mummy;
	 m_no_of_energybars = bar;
	 m_no_of_lives = lives;
}
 game::~game() //destructor
 {
	 newopt = NULL;
	 delete newopt;
	 cout << "Deleted!"; //shows that the object has been deleted
 }
 bool game::Init() //resets to default values and calls menu again
 {
	 m_no_of_mummies = 3;
	 m_no_of_energybars = 2;
	 m_no_of_lives = 3;
	 Menu();
	 return 1;
 }

bool game::Menu() //basic menu that is shown at the start of the game
{
	newopt = NULL;
	delete newopt;
	system("CLS"); //clears the screen
	string sDecision = " "; //creates new string variable for input
	cout << "Welcome to Chris Humm's top-down dungeon crawler! \n\n1) New Game\n2) Options\n3) Hi Scores\n4) Exit";
	sDecision = _getch(); //outputs menu message then gets input using _getch
	cin.sync(); //clears any error flags, syncs the stream
	cin.clear();//this helps if we use multiple inputs via cin at once
	char *c = (char*)sDecision.c_str(); //I convert character pointer using type conversion, i use this because string can't be used in switch
	ifstream temp("hiscores.txt");//create new ifstream object that reads from the file hiscores.txt
	for(;;) //infinite for loop
	{
	switch(*c) //start switch statement using the value that the char*c is pointing to
	{
		case '1': //if 1
			c = NULL; //assign null to pointer
			delete c; //delete pointer
			NewGame();//launch new game method
		break;
		case '2':
			c = NULL;
			delete c;
			newopt = new options(m_no_of_energybars,m_no_of_mummies,m_no_of_lives); //dynamically create new options object, passing in 
		break;																		//the variables from game.cpp
		case '3':
			c = NULL; 
			delete c;
			system("CLS"); //clears the menu and other stuff from screen
			
			if(temp) //checks to see if temp exists (if file is found using ifstream)
			{
			ShowHiscores(); //call the show hiscores method
			}
			else //else no file is found..
			{
			cout << "Save some hi scores first! Press any key to continue...";
			_getch(); //output error message
			}
			Menu(); //call menu again
		break;
		case '4':
			c = NULL;
			delete c;
			exit(1); //causes the player to exit the program
		break;
		default:
			sDecision = validation(sDecision); //validate the menu option if the above is not met
	}
	}
	delete newopt; //deletes newopt object
	newopt = NULL;
	return 0; //returns 0 to the program, if the program exits for some reason.
	
}

string game::validation(string s_string) //new string method, taking string that is passed in from menu
{
	string temp = " "; //create a new temporary string to use in validation process
	ss << s_string; //stores our invalid input into the stringstream
	string valid[4] = { "1", "2", "3", "4"}; //creates an array of possible "valid" reponses
	bool success = 0; //create boolean variable to loop our program
	while(success != 1) //we start a while loop 
	{
	system("CLS"); //clears the screen, outputs the error message below WITH the users input stored in stringstream
	cout << ss.str() << " is an invalid input! Please input a valid option: \n"; //outputs contents of ss string
	cout << "Welcome to Chris Humm's top-down dungeon crawler! \n\n1) New Game\n2) Options\n3) Hi Scores\n4) Exit";
	temp = _getch(); //gets input
	
	for(int i = 0; i < 4; i++)			//This loop compares my input
	{									//with each "valid" value inside
		if(temp.compare(valid[i]) != 1) //the valid array using an inbuilt
		{								//string compare function
			success = 1;
			break;
		}
		else;
	}
	cin.sync(); //helps us read input AFTER spaces
	cin.clear(); //clears any errors
	}
	s_string = temp; //stores valid input into our s_string value
	return s_string; //return the valid 
}
	bool game::NewGame() //this is called when the player chooses to start a new game
	{
		char decision = NULL; //assign default null value to our decision
		int choice = 0; //set the choice for our loop to 0
		system("CLS"); //we clear the screen, so new input is shown
		cout << "1) Easy\n2) Medium\n3) Hard"; //output options for our new level
		decision = _getch();// get input from the options
		switch(decision)//start a switch statement
		{
		case '1':
			choice = 1;// these are for level class, when we decide what map we want
		break;		   // I used a switch statement because it was easy to add additional
		case '2':		// options as it was more readable.
			choice = 2;
		break;
		case '3':
			choice = 3;
		break;
		default:
			choice = 1;
		break;
		}
		level newlevel(m_no_of_energybars,m_no_of_mummies,m_no_of_lives, choice); //after a decision is made, create a new level object
		return 0;																	// with the values in game
}
void game::ShowHiscores() //this is called when the player already has hiscores.txt created
{						//it outputs our hiscores
int count = 0;
string line = "";
	cout	 << "#--------------------------------#" << endl; // title for our outpiut
	cout	 << "#-----******HIGHSCORES******-----#" << endl;//
	cout << "#--------------------------------#" << endl;//
  ifstream hiscore; //create a new ifstream object so we can open our file

  hiscore.open ("hiscores.txt", std::ifstream::in); //using open function, we open out file

  char c = hiscore.get(); //gets single character from our file

  while (hiscore.good()) { //while there are no errorse
    std::cout << c;		// output the contents of c
    c = hiscore.get();	//gets next character
  }		// this loop outputs our file, character at a time
  _getch();//waits for user input to read the file
  hiscore.close();// closes the file
}
