#include <iostream>
#include "mummy.h"

class specialmummy : public mummy
{
private:
	level * currentlevel;
public:
	specialmummy(level * l, int mummy, int y, int x);
	int validation(int num);
	void mummyMoves(level*, int mummy, int y, int x);
	level* w;//We create a pointer back to the level class
	mummy* mummy_ptr;
	int mummy_pos_x;//we use mummy_pos_x
	int mummy_pos_y;//and mummy_pos_y
};
