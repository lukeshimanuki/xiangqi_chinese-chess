#ifndef GAME_H__
#define GAME_H__

#include <vector>
#include <cstdlib>
#include <string>
#include <fstream>

#include "position.h"
#include "person.h"
#include "computer.h"

class game
{
public:
	std::vector<player*> players;
	
	std::string log;
	
	bool turn;
	
	position pos;
	
	void take_turn ();
	
	void play ();
	
	void set_players (int a, int b);
	
	void valid_moves (std::vector<std::vector<int> > &vec, position &pos, bool player);
	
	int winner (position &pos, bool t);
	
	void initialize ();
	
	void set_log (std::string filename);
	
	void log_move (std::vector<int> mov);
	
	game ();
};

#endif
