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
	
	void valid_moves (std::vector<std::vector<int> > &vec, bool player);
	
	std::vector<position> val_pos;
	
	void copy (position &pos);
	
	void move(std::vector<int> &vec);
	
	void set_moves (std::vector<position> &val_pos, std::vector<std::vector<int> > &vec, bool player);

	void initialize (std::vector<std::vector<int> > initialposition);

	int winner (bool t);
	
	position ();
};

#endif
