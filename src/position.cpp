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
	board[x2][y2] = board[x1][y1];
	board[x1][y1] = 0;
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

std::vector<position> position::set_valid_moves (bool player)
{
	std::vector<position> val_pos;
	std::vector<std::vector<int> > val_moves = valid_moves(player);
	for (int i = 0; i < val_moves.size(); i++)
	{
		position new_pos = copy();
		new_pos.move(val_moves[i][0], val_moves[i][1], val_moves[i][2], val_moves[i][3]);
		val_pos.push_back(new_pos);
	}
	return val_pos;
}

double position::value ()
{
	return valid_moves(0).size() / valid_moves(1).size();
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
