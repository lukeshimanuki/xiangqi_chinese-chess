#include "position.h"
#include "val_moves.cpp"

position position::copy ()
{
	position new_pos;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			new_pos.board[i][j] = board[i][j];
		}
	}
	return new_pos;
}

void position::move(int x1, int y1, int x2, int y2)
{
	int c = board[x1][y1];
	board[x1][y1] = 0;
	board[x2][y2] = c;
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

std::vector<position> position::set_valid_moves (bool p)
{
	std::vector<position> val_pos;
	for (int i = 0; i < val_cache.size(); i++)
	{
		position new_pos = copy();
		new_pos.move(val_cache[i][0], val_cache[i][1], val_cache[i][2], val_cache[i][3]);
		val_pos.push_back(new_pos);
	}
	return val_pos;
}

int position::winner (bool t) //t = whose turn it is
{
	if (valid_moves(t).size() == 0) // if t has no moves
	{
		return 2 * t - 1; // player !t wins
	}
	return 0;
}

position::position ()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			board[i][j] = 0;
		}
	}
}
