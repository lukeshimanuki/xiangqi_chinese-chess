#ifndef PLAYER_H__
#define PLAYER_H__

#include <vector>
#include <cstdlib>

#include "position.h"
#include "io.h"

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

class person : public player
{
public:
	int type ();
	void set_difficulty (int d);

	int io_type; // 0 = text
	void set_io(int a);
	std::vector<int> choose_move (position &pos, bool p);
	
	// io
	void message(std::string a);
	void draw(position &pos);
	std::vector<int> choose_point ();
	
	std::vector<io*> in_out;
	
	person ();
};

class computer : public player
{
public:
	int type ();

	int depth;

	void set_difficulty (int d);

	double recurse_val(position &pos, bool p, int d);

	std::vector<int> choose_move (position &pos, bool p);

	double value (position &pos, bool p);

	computer ();
};

#endif
