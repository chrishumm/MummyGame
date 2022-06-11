#include <iostream>//Include input/ouput stream
#include <string>//I include strings as I will use them instead of character 
#include <vector>//I replace arrays with vectors

using namespace std; //so I don't type std::
#pragma once//I want my program to compile this header file once
class level //new class called level
{
private: //these our my private variables only accessible to this class
static int mummy_turn;//static int to determine which mummies move
int m_music; //to determine which music should play
int* p_x;
int* p_y;
protected:
	static int caughtmummies; //integer gets passed when game is over
	int m_no_of_mummies;     //
	int m_no_of_energybars;  //Basic ints that are passed from game
	int m_no_of_lives;       //
	static int m_no_of_spades; //random number will get generated in our level methods
	int player_pos_x; //stores current position of the player
	int player_pos_y; //
	int mummy_pos_x[20];//stores current position for our mummy
	int mummy_pos_y[20];//
	vector< vector<char> > world;//creates empty 2d vector for our board
	vector<char>::pointer ptr; //creates vector pointer to interact with our board values
	static	unsigned int energybars;//counts how many we have collected
	static int turn;//increments over each turn, showing the place
	static unsigned int TrappedMummies[6];//Keeps track of each trapped mummy
public:
	level();										//
	level(int bars, int mummy, int lives);			//
	level(int bar, int mummy, int lives, int turn); //* This constructor is used
	~level();

	void	generateLevel(); //Creates our level
	void	displayLevel();  //Displays our Level
	void	moveCharacter(int x, int obstacle, int y); //Moves our Character
	void	moveMummy(int x,  int obstacle, int mummy);//Moves our Mummy
	void	displayHud(); //Displays player instructions
	void	setColour(int);//Sets colour for our game
	int		getPosCoordx(int i, int mummy);//Returns coordinates for player and mummy
	int		getPosCoordy(int i, int mummy);//
	int	Obstacle(int y, int x); //Shows what the mummy/player is walking into
	int wallCheck(int code, int c, int mummy);//Stops player/mummy walking into invalid areas
	int mummyMoves();
	bool respawnPlayer(int*, int*);	//Respawns our player, taking two integer points
	friend void playMusic(level &);	//Plays music depending on our m_music value
};									//takes memory address, it can access our private variables and modify.
