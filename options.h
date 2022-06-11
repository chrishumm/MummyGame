#include <iostream>
#include "game.h"//Composite
using namespace std;

#pragma once //we include to only compile header file once
class options : public game
{
protected:
private:
	int bar; //these are our private attributes
	int mummy;//These get passed in via game class
	int lives;//We will modify these and pass them back into the game class
	int* change;
public:
	options(int mbar, int mmummy, int mlives); //options constructor, assigns local variables
	~options();
	void omenu(); //This method outputs our new menu for options
	int newbars(int bar);//
	int newmummy(int mummy);//These are our seperate methods for setting new values
	int newlives(int lives);//
	string validation(string s_string); // I use a string method for validation
};
