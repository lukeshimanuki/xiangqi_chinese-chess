#ifndef POSITION_H__
#define POSITION_H__

#include <iostream>
#include <vector>

class position
{
public:
	/* 0 = empty
	 * 1 = general
	 * 2 = advisor
	 * 3 = elephant
	 * 4 = horse
	 * 5 = chariot
	 * 6 = cannon
	 * 7 = soldier
	 * positive = player 0
	 * negative = player 1
	 */
	std::vector<std::vector<int> > board;
	
	virtual void valid_moves (std::vector<std::vector<int> > &vec, bool player) = 0;
	
	virtual void initialize () = 0;
	
	virtual int winner (bool t) = 0;
	
	void copy (position &pos);
	
	void move(std::vector<int> &vec);
	
	void set_moves (std::vector<position*> &val_pos, std::vector<std::vector<int> > &vec, bool player);


	
	position ();
};

#endif
