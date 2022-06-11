#include <iostream>
#include <conio.h>
#include <cstdlib>
#include "gameover.h"
#include "game.h"//Compistion
#include<fstream>//Allows us to open/write files
#include <time.h>//Gets current time

struct hiscore//we create a struct to hold our values
{
	string name;//Player name is stored here
	int score;//Score is stored
};

gameover::gameover(int m_bars, int m_mummy, int m_lives) : GameConditions(m_bars,m_mummy,m_lives)
{
	captured = m_mummy;
	lives = m_lives;
	bar = m_bars;
	score = (m_lives + m_mummy) - m_bars;//Using inheritance, we get the values from our parent classes
}										 //I then work out the score based on them.

void gameover::message()//takes inherited variables
{
	system("CLS");//clears the screen
	cout <<"Sorry! You have lost!\nYou captured: " << captured <<" mummies!. You have: "<< lives << " lives left, but you have " << bar << " bars remaining!\nDo you want to play again?\n1) Yes \n2) Exit\n3) Save Hiscore";
	decision = NULL;//Above outputs gameover message and I set char to null
	loop = 0;// loop is set to 0 to start our while loop
	while(loop == 0)
	{
	decision = _getch();//we store decision from getch
	switch(decision)//start a switch statement based on that input
	{
	case '1'://if player chose new game
		loop++;//break loop
		level::turn = 1;
		level::m_no_of_spades = 100;//We reset the static variables
		level::caughtmummies = 0;
			for(int i = 0;i < 100;i++)
			{
				if(TrappedMummies[i] == 1)//As trapped mummies is also static
					TrappedMummies[i] = 0;//I need to reset each array member to 0
				else{}
			}
		GameConditions::end = 0;//I reset the static end variable so gameconditions can be called again
		game(3,3,2,1);// I start a new game using an empty constructor
	break;
	case '2'://If player chose to exit
		loop++;//break loop
		exit(0);//use exit function
	case '3'://If player decides to save their hiscore
		saveHiscore(score);// I call savehiscore method, using my score member
		cout << "Hiscore saved!\n";//output message once above method is completed
	break;
	default://repeat until option is chosen
	
	break;
	}
	}
}

void gameover::saveHiscore(int f)//After taking in the score variable
{
	hiscore newhiscore;//We create a new structure named newhiscore
	time_t rawtime;//we create a new time variable named rawtime
	struct tm * timeinfo;//We use this to be able to access localtime
	time (&rawtime);//we get the memory address of our time variable,
    timeinfo = localtime (&rawtime);//Using memory address, we fetch the localtime from our computer
	newhiscore.score = f;//We set the score in the structure to the value we have passed in
	cout << "\n\nPlease enter your name: ";
	getline(cin, newhiscore.name);//Using getline, we store a string variable in the structure.name section
	cin.sync();//by creating a new ofstream, we can create new files on our computer where our .exe is stored.
	ofstream playerInfo("hiscores.txt", ios::app);//This will create OR append our hiscore file
        playerInfo << "#---------------'" << "#" << "'--------------#" << endl
                      << "#--------Name: " << newhiscore.name << "'--------------#" << endl//We use these to save our
                      << "#--------Score Achieved: " << newhiscore.score << "'--------------#" << endl//structure contents
                      << "#--------Date Achieved: " << asctime(timeinfo) << "'--------------#" << endl//this allows us to output our time
                      << "#--------------------------------#" << endl;
        playerInfo.close();//we close the current file from editing.
}
