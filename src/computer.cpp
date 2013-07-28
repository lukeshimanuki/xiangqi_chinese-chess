#include "player.h"

void computer::set_depth (int a)
{
	depth = a;
}

// returns move with highest recurse_val
std::vector<int> computer::choose_move(position &pos, bool p)
{
	std::vector<std::vector<int> > val;
	pos.valid_moves(val, p);
	double max = 0;
	std::vector<int> best;
	for (int i = 0; i < val.size(); i++)
	{
		position new_pos;
		pos.copy(new_pos);
		new_pos.move(val[i]);
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
	std::vector<std::vector<int> > val;
	pos.valid_moves(val, t);
	const double w = 65536; //large number to indicate win/loss
	if (p == t) // if player's turn: take best case
	{
		if (val.size() == 0) //you have no moves
		{
			return (double) 1 / w; // you lose, so very bad position
		}
		// filter
		const double threshold = 0.9; // threshold to filter out obviously bad moves
		double max1 = 0;
		std::vector<double> v;
		for (int i = 0; i < val.size(); i++)
		{
			position new_pos;
			pos.copy(new_pos);
			new_pos.move(val[i]);
			v.push_back(value(new_pos, p));
			if (v[i] > max1)
			{
				max1 = v[i];
			}
		}
		int j = 0;
		for (int i = 0; i - j < val.size(); i ++)
		{
			if (v[i] < max1 * threshold)
			{
				val.erase(val.begin() + i - j);
				j++;
			}
		}
		//recurse
		double max2 = 0;
		for (int i = 0; i < val.size(); i++)
		{
			position new_pos;
			pos.copy(new_pos);
			new_pos.move(val[i]);
			double value = recurse_val(new_pos, p, !t, d - 1);
			if (value > max2)
			{
				max2 = value;
			}
		}
		return max2;
	}
	else // opponent's turn: take worst case
	{
		if (val.size() == 0) //enemy has no moves
		{
			return w; // you win, so very good position
		}
		// filter
		const double threshold = 1.1; // threshold to filter out obviously bad moves
		double min1 = w + 1;
		std::vector<double> v;
		for (int i = 0; i < val.size(); i++)
		{
			position new_pos;
			pos.copy(new_pos);
			new_pos.move(val[i]);
			v.push_back(value(new_pos, p));
			if (v[i] < min1)
			{
				min1 = v[i];
			}
		}
		int j = 0;
		for (int i = 0; i - j < val.size(); i ++)
		{
			if (v[i] > min1 * threshold)
			{
				val.erase(val.begin() + i - j);
				j++;
			}
		}
		// recurse
		double min2 = w + 1;
		for (int i = 0; i < val.size(); i++)
		{
			position new_pos;
			pos.copy(new_pos);
			new_pos.move(val[i]);
			double value = recurse_val(new_pos, p, !t, d - 1);
			if (value < min2)
			{
				min2 = value;
			}
		}
		return min2;
	}
}

double computer::value (position & pos, bool p)
{
	const double e = 0.0000001;// prevents divide by 0
	std::vector<std::vector<int> > v0, v1;
	pos.valid_moves(v0, 0);
	pos.valid_moves(v1, 1);
	double val = (v0.size() + e) / (v1.size() + e);
	return val * !p + p / val;
}

computer::computer()
{

}
