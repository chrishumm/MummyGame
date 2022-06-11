#include <iostream>
#include "level.h"//we inherit from level, so we include the header file
#pragma once
class GameConditions : public level //public shows we inherit
{
private:
	GameConditions* conditionmessage; //private gameconditiosn pointer for polymorphism
protected:
	int m_bar; //These our the inherited values
	int m_mummy;//These are used in our child classes when we output our gameover/win message
	int m_lives;//
public:
	static int end; //This is to keep track and make sure we only all winorlose once
	GameConditions(int,int,int);//The constructor takes three integers, the inherited values
	void WinorLose(int,int,int);//WinorLose takes these as well, as it is directly called from the constructor
	virtual void message(); 
	//The virtual void message method is a common method I want to use in all of my output messages
	//It also uses the inherited variables.
};
