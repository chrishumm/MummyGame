#include "game.h" //includes the game class
#include <windows.h>
#include <conio.h>
using namespace std;


int main()		
{
SetConsoleTitle("Mummy Game - Chris Humm");
game game(5,3,2,1);		
try //this catches any errors after the game object
{
	throw 1;
}

catch(int i) //because the object is suppose to be created, there must be an error with compilaton
{			// catch "catches" the error.
	cout << "Error: " << i <<". Did you compile correctly?";
	_getch();
}
}			

/* I have created my entire game using objects.
 I do this because each object handles a seperate part of the game
 The game object serves as a "spring board" to the other objects.
 This removes the need to do a lot of code in main. I define each object
 with a specific function and program according to that. Having a lot of 
 code within main would mean that the code is ambigious and not belong to any class.
 I try to tie code specific to each class, so I removed the need to code heavily in main.*/
