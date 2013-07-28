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
	
	// FILTER
	/*
	{
		const double threshold = 0.9; // threshold to filter out obviously bad moves
		double max = 0;
		std::vector<double> v;
		std::vector<std::vector<int> > valo = val;
		for (int i = 0; i < val.size(); i++)
		{
			position new_pos;
			pos.copy(new_pos);
			new_pos.move(val[i]);
			v.push_back(value(new_pos, p));
			if (v[i] > max)
			{
				max = v[i];
			}
		}
		val.clear();
		for (int i = 0; i < valo.size(); i ++)
		{
			if (v[i] >= max * threshold)
			{
				val.push_back(valo[i]);
			}
		}
	}
	*/
	
	{
		const double threshold = 0.9; // threshold to filter out obviously bad moves
		double max = 0;
		std::vector<double> v;
		for (int i = 0; i < val.size(); i++)
		{
			position new_pos;
			pos.copy(new_pos);
			new_pos.move(val[i]);
			v.push_back(value(new_pos, p));
			if (v[i] > max)
			{
				max = v[i];
			}
		}
		int j = 0;
		for (int i = 0; i - j < val.size(); i ++)
		{
			if (v[i] <= max * threshold)
			{
				val.erase(val.begin() + i - j);
				j++;
			}
		}
	}	
	

	const double w = 65536; //large number to indicate win/loss
	if (p == t) // if player's turn: take best case
	{
		if (val.size() == 0) //you have no moves
		{
			return (double) 1 / w; // you lose, so very bad position
		}
		double max = 0;
		for (int i = 0; i < val.size(); i++)
		{
			position new_pos;
			pos.copy(new_pos);
			new_pos.move(val[i]);
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
			position new_pos;
			pos.copy(new_pos);
			new_pos.move(val[i]);
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
