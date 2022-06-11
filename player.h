#include <iostream>
#include "level.h"


#pragma once
class player : public level
{
private:
	level* ptr; //create a level pointer to access level methods
protected:
	int player_pos_x; // store current player_pos_x in these members
	int player_pos_y;//
public:
	player(level*);//Start our constructor with level pointer;
	~player();
	void moveCharacter(); //For basic movement and instructions
	void dig(); //Special method for digging holes
	int validation(char move); //Validate all movement
};
