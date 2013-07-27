#include "player.h"

void computer::set_depth (int a)
{
	depth = a;
}

// returns move with highest recurse_val
std::vector<int> computer::choose_move(position &pos, bool p)
{
	std::vector<std::vector<int> > val = pos.valid_moves(p);
	double max = 0;
	std::vector<int> best;
	for (int i = 0; i < val.size(); i++)
	{
		position new_pos = pos;
		new_pos.move(val[i][0], val[i][1], val[i][2], val[i][3]);
		double value = recurse_val(new_pos, p, p, depth);
		if ((double) value * !p + p / value >= max)
		{
			max = (double) value * !p + p / value;
			best = val[i];
		}
	}
	return best;
}

// game position, which player, whose turn on that position, how deep to recurse
double computer::recurse_val(position &pos, bool p, bool t, int d)
{
	if (d == 0) //reached end of recursion
	{
		return value(pos, p);
	}
	std::vector<std::vector<int> > val = pos.valid_moves(t);
	double w = 100000000; //large number to indicate win/loss
	if (p == t) // if player's turn: take best case
	{
		if (val.size() == 0) //you have no moves
		{
			return (double) 1 / w; // you lose, so very bad position
		}
		double max = -1;
		for (int i = 0; i < val.size(); i++)
		{
			position new_pos = pos;
			new_pos.move(val[i][0], val[i][1], val[i][2], val[i][3]);
			double value = recurse_val(new_pos, p, !t, d - 1);
			if (value >= max)
			{
				max = value;
			}
		}
		return max;
	}
	else // opponent's turn: take worst case
	{
		if (val.size() == 0) //enemy has no moves
		{
			return w; // you win, so very good position
		}
		double min = w + 1;
		for (int i = 0; i < val.size(); i++)
		{
			position new_pos = pos;
			new_pos.move(val[i][0], val[i][1], val[i][2], val[i][3]);
			double value = recurse_val(new_pos, p, !t, d - 1);
			if (value <= min)
			{
				min = value;
			}
		}
		return min;
	}
}

double computer::value (position & pos, bool p)
{
	double e = 0.0000001;// prevents divide by 0
	double val = (pos.valid_moves(0).size() + e) / (pos.valid_moves(1).size() + e);
	return val * !p + p / val;
}

computer::computer()
{

}
