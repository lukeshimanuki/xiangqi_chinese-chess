#ifndef GAME_H__
#define GAME_H__

#include <vector>
#include <cstdlib>
#include <string>
#include <fstream>

#include "position.h"
#include "person.h"
#include "computer.h"
#include "xiangqi.h"

class game
{
public:
	std::vector<player*> players;
	
	std::string log;
	
	bool turn;
	
	int turncount;
	
	position *pos;
	
	void set_game_type (int t);
	
	void take_turn ();
	
	void play ();
	
	void set_players (int a, int b);
	
	void initialize ();
	
	void set_log (std::string filename);
	
	void log_move (std::vector<int> mov);
	
	game ();
	~game ();
};

#endif
