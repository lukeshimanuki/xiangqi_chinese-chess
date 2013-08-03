#ifndef POSITION_H__
#define POSITION_H__

#include <iostream>
#include <vector>

class position
{
public:
	std::vector<std::vector<int> > board;
	
	virtual void valid_moves (std::vector<std::vector<int> > &vec, bool player) = 0;
	
	virtual void initialize () = 0;
	
	virtual int winner (bool t) = 0;
	
	virtual int game_type() = 0;
	
	virtual double value (bool p) = 0;
	
	void copy (position &pos);
	
	virtual void move(std::vector<int> &vec) = 0;
	
	void set_moves (std::vector<position*> &val_pos, std::vector<std::vector<int> > &vec, bool player);
	
	position ();
	virtual ~position () = 0;
};

#endif
