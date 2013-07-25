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
	std::vector<std::vector<int> > val = pos.valid_moves(t);
	if (p == t) // if player's turn: take best case
	{
		if (d == 0) //reached end of recursion
		{
			double max = 0;
			for (int i = 0; i < val.size(); i ++)
			{
				position new_pos = pos;
				new_pos.move(val[i][0], val[i][1], val[i][2], val[i][3]);
				double value = new_pos.value();
				if ((double) value * !p + p / value >= max)
				{
					max = (double) value * !p + p / value;
				}
			}
			return max;
		}
		double max = 0;
		for (int i = 0; i < val.size(); i++)
		{
			position new_pos = pos;
			new_pos.move(val[i][0], val[i][1], val[i][2], val[i][3]);
			double value = recurse_val(new_pos, p, !t, d - 1);
			if ((double) value * !p + p / value >= max)
			{
				max = (double) value * !p + p / value;
			}
		}
		return max;
	}
	else // opponent's turn: take worst case
	{
		if (d == 0) //reached end of recursion
		{
			double min = 0;
			for (int i = 0; i < val.size(); i ++)
			{
				position new_pos = pos;
				new_pos.move(val[i][0], val[i][1], val[i][2], val[i][3]);
				double value = new_pos.value();
				if ((double) value * !p + p / value <= min)
				{
					min = (double) value * !p + p / value;
				}
			}
			return min;
		}
		double min = 0;
		for (int i = 0; i < val.size(); i++)
		{
			position new_pos = pos;
			new_pos.move(val[i][0], val[i][1], val[i][2], val[i][3]);
			double value = recurse_val(new_pos, p, !t, d - 1);
			if ((double) value * !p + p / value <= min)
			{
				min = (double) value * !p + p / value;
			}
		}
		return min;
	}
}

computer::computer()
{

}
