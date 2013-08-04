#ifndef PERSON_H__
#define PERSON_H__

#include <vector>
#include <cstdlib>

#include "player.h"
#include "textio.h"

class person : public player
{
public:
	int player_type ();
	
	// options: {io}
	void set_options (std::vector<double> &o);
	
	std::vector<int> choose_move (position &pos, bool p);
	
	std::vector<io*> in_out;
	
	person ();
};

#endif
