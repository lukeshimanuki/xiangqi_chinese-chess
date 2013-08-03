#include "position.h"

void position::copy (position &pos)
{
	pos.board = board;
}

void position::move(std::vector<int> &vec)
{
	int c = board[vec[0]][vec[1]];
	board[vec[0]][vec[1]] = 0;
	board[vec[2]][vec[3]] = c;
}

void position::set_moves (std::vector<position*> &val_pos, std::vector<std::vector<int> > &vec, bool p)
{
	val_pos.clear();
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		position *new_pos;
		copy(*new_pos);
		new_pos->move(vec[i]);
		val_pos.push_back(new_pos);
	}
}

// x is rows, y is columns
position::position ()
{/*
	std::vector<int> p (y, 0);
	std::vector<std::vector<int> > q (x, p);
	board = q;
*/
}
