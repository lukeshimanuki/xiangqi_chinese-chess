#ifndef PLAYER_H__
#define PLAYER_H__

#include <vector>
#include <cstdlib>

#include "position.h"

class player
{
public:
	virtual std::vector<int> choose_move (position &pos, bool p) = 0;
	
	virtual int type () = 0;
	
	virtual void set_difficulty (int d) = 0;

	player()
	{
	}
};

#endif
