#include <iostream>
#include "GameConditions.h" //inherits from gameconditions

#pragma once
class win : public GameConditions //uses inheritance
{
private:
	char decision; //decides on user input
	bool loop;    // keeps program loop running
	int score;	   //total score tally from our inherited values
	int captured;
	int lives;
	int bar;
protected:
	int m_bars; // Inherited from gameconditions
	int m_mummy; //(ultimately, inherited from level
	int m_lives; //
public:
	win(int, int, int); //constructor that sets inherited values
	void message(); //via polymorphism, our gamecondition pointer calls win message
	void saveHiscore(int f);//stores our 'score' into hiscores.txt file (or appends)
};
