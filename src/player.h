#ifndef PLAYER_H__
#define PLAYER_H__

#include <vector>

#include "position.h"
#include "io.h"

class player
{
public:
	std::vector<int> choose_move (position &pos, bool p);

	player()
	{
	}
};

class person : public player
{
public:
	int io_type; // 0 = text
	void set_io(int a);
	std::vector<int> choose_move (position &pos, bool p);
	
	// io
	void message(std::string a);
	void draw(position &pos);
	std::vector<int> choose_point ();
	
	person ();
};

class computer : public player
{
public:
	int depth;

	void set_depth(int a);

	double recurse_val(position &pos, bool p, bool t, int d);
	
	std::vector<std::vector<int> > filter (position &pos, std::vector<std::vector<int> > o, bool p);

	std::vector<int> choose_move (position &pos, bool p);

	double value (position &pos, bool p);

	computer ();
};

#endif
