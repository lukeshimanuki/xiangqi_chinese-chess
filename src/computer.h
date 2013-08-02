#ifndef COMPUTER_H__
#define COMPUTER_H__

#include <vector>
#include <cstdlib>

#include "player.h"

class computer : public player
{
public:
	int player_type ();

	int depth;

	void set_difficulty (int d);

	double recurse_val(position &pos, bool p, int d);

	std::vector<int> choose_move (position &pos, bool p);

	double value (position &pos, bool p);

	computer ();
};

#endif
