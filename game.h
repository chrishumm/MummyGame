#include <iostream>
 //uses composition to include options
#include <string>	//include string for stringstream and other inputs
using namespace std;

#pragma once //use this to compile our header file once
class game
{
private:
 //option object pointer, for dynamically creating 
protected:
	string validation(string s_string); //validation function
	int m_no_of_mummies;		//
	int m_no_of_energybars;		//Basic changeable values we'll use in level
	int m_no_of_lives;			//
public:
	game();		//default constructor
	game(int bar, int mummies, int lives); //take 3 ints, when options interacts with the game class
	game(int bar, int mummies, int lives, int firststart);
	~game(); //destructor
	bool Init(); //causes all values to return to their defaults when called
	bool NewGame(); //newgame method for launching the level class 
	bool Menu(); //basic menu that is shown at the start of the game
	void ShowHiscores(); //outputs current hiscores to screen
};
