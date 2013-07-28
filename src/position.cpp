#include "position.h"
#include "val_moves.cpp"

void position::copy (position &pos)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			pos.board[i][j] = board[i][j];
		}
	}
}

void position::move(std::vector<int> &vec)
{
	int c = board[vec[0]][vec[1]];
	board[vec[0]][vec[1]] = 0;
	board[vec[2]][vec[3]] = c;
}

void position::initialize ()
{
	int initialboard [10][9] =
		{{	5,4,3,2,1,2,3,4,5		},
		{	0,0,0,0,0,0,0,0,0		},
		{	0,6,0,0,0,0,0,6,0		},
		{	7,0,7,0,7,0,7,0,7		},
		{	0,0,0,0,0,0,0,0,0		},
		{	0,0,0,0,0,0,0,0,0		},
		{	-7,0,-7,0,-7,0,-7,0,-7	},
		{	0,-6,0,0,0,0,0,-6,0		},
		{	0,0,0,0,0,0,0,0,0		},
		{	-5,-4,-3,-2,-1,-2,-3,-4,-5}};
	for (int i = 0; i < 10; i ++)
	{
		for (int j = 0; j < 9; j ++)
		{
			board[i][j] = initialboard[i][j];
		}
	}
}

void position::set_moves (std::vector<position> &val_pos, std::vector<std::vector<int> > &vec, bool p)
{
	val_pos.clear();
	for (int i = 0; i < vec.size(); i++)
	{
		position new_pos;
		copy(new_pos);
		new_pos.move(vec[i]);
		val_pos.push_back(new_pos);
	}
}

int position::winner (bool t) //t = whose turn it is
{
	std::vector<std::vector<int> > m;
	valid_moves(m, t);
	if (m.size() == 0) // if t has no moves
	{
		return 2 * t - 1; // player !t wins
	}
	return 0;
}

position::position ()
{
/*
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			board[i][j] = 0;
		}
	}
*/
}
