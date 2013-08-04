#ifndef PLAYER_H__
#define PLAYER_H__

#include <vector>
#include <cstdlib>

#include "position.h"

class player
{
public:
	virtual std::vector<int> choose_move (position &pos, bool p) = 0;
	
	virtual int player_type () = 0;
	
	virtual void set_options (std::vector<double> &o) = 0;
	
	std::vector<double> options;

	player()
	{
	}
};

#endif
