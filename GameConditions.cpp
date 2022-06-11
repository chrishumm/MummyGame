#include <iostream>
#include <cstdlib>
#include "GameConditions.h"
#include "win.h"
#include "gameover.h"

int GameConditions::end = 0;//To stop our infinite loop
GameConditions::GameConditions(int m_bars, int m_mummy, int m_lives) : level(m_bars,m_mummy,m_lives)
{ //Inherits the current values stored in the level object, and places them into protected variavles in gameconditions
	if(end == 0)//If the game HAS ended
	{
	end++;//increment
	WinorLose(m_bars,m_mummy,m_lives);//call the winorlose method
	}
	else{};//else do nothing
}

void GameConditions::WinorLose(int m_bars, int m_mummy, int m_lives) //taking in values inherited from level
{
	if(m_lives == 0) //If player is dead
	{
		gameover gameovermessage(m_bars, m_mummy, m_lives); //create a new gameover object 
		conditionmessage = &gameovermessage; //Use our gameconditions pointer, to point at the new object
		conditionmessage->message();//Using polymorphism, we call the method that outputs out message
	} //I used polymorphism as many different gameconditions have different output messages. Although they are different, they share
	  //similarities, so using polymorphism, I call the method specific to the object and due to virtual function
	else if(m_lives > 0) //If player is alive and reached the end
	{
		win winmessage(m_bars, m_mummy, m_lives);//create win object
		conditionmessage = &winmessage;//
		conditionmessage->message(); // use polymorphism to output win message
	}
	else //else, do nothing. This would be easily expanded on in the future by adding in more conditions.
	{
	}
}

void GameConditions::message() //This is our virtual function
{																//Other child classes "inherit" this method
	system("CLS");										//If the child class has no appropriate method, this method is called.
	cout << "Error, this is suppose to be overriden! Contact a programmer!";
}
