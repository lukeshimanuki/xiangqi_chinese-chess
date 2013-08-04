#ifndef COMPUTER_H__
#define COMPUTER_H__

#include <vector>
#include <cstdlib>

#include "player.h"
#include "xiangqi.h"
#include "dobutsu_shogi.h"

class computer : public player
{
public:
	int player_type ();

	// options: {depth, threshold, recursive threshold}
	void set_options (std::vector<double> &o);
	
	position *new_position (int type);

	double recurse_val(position &pos, bool p, int d);

	std::vector<int> choose_move (position &pos, bool p);

	computer ();
};

#endif
