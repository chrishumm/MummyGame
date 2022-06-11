#include <iostream>
#include "level.h"

#pragma once
class mummy
{
private:
	; //for showing what number of mummy is moving
	//to see which mummies are captured
protected:
	level* w;//We create a pointer back to the level class
	mummy* mummy_ptr;
	int mummyno;
	int mummy_pos_x;//we use mummy_pos_x
	int mummy_pos_y;//and mummy_pos_y
public:
	static int capturedmummies[20];
	mummy();//Basic constructors to assign position values
	mummy(int y, int x);//
	~mummy();
	virtual void mummyMoves(level*, int mummy, int y, int x);//Main method that controls how our mummy moves
	virtual int validation(int num); //Validates all moves
	void pos(int y, int x);
};
