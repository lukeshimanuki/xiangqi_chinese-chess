#ifndef GAME_H__
#define GAME_H__

#include <vector>
#include <cstdlib>

#include "position.h"
#include "player.h"

class game
{
public:
	std::vector<person> pp;
	
	std::vector<computer> cp;
	
	std::vector<bool> type; // true = person, false = computer
	
	bool turn;
	
	position pos;
	
	void take_turn ();
	
	void play ();
	
	void set_type (bool a, bool b);
	
	void initialize (bool start);
	
	game ();
};

#endif
