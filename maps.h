#include <iostream>
#include "level.h" //Composite relationship with level class 
#pragma once //only want to create our class header file once
class Maps
{
private:
	char map[15][16]; //basic 2d array to keep our levels in
	vector<vector<char>> GetMap; //We return a vector, so we convert to above variabe to vector
public:
	Maps(int choice); //Constructors
	Maps();			  //
	vector< vector<char> > MapChoice(int choice);//Uses choice to determine which map will be chosen
	~Maps();
	char test(void);
protected:

};
