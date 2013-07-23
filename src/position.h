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
	int board[10][9];
	
	std::vector<position> list;
	
	position copy ();
	
	void move(int x1, int y1, int x2, int y2);
	
	void initialize ();
	
	void valid_moves (bool player);
	
	int valid_moves_count (bool player);
	
	double value ();
	
	void draw ();
	
	position ();
};

#endif
