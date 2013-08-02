#include "player.h"
#include "computer.h"

// returns move with highest recurse_val
std::vector<int> computer::choose_move(position &pos, bool p)
{
	std::vector<std::vector<int> > val;
	pos.valid_moves(val, p);
	if (val.size() == 0) // something wrong happened
	{
		std::cout<<"Error: no moves for player " << p << "\n"; // so print error message
		std::exit(1); //and exit
	}
	// filter
	const double threshold = 0.9; // threshold to filter out obviously bad moves
	double max1 = 0;
	std::vector<double> v;
	for (unsigned int i = 0; i < val.size(); i++)
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
	for (unsigned int i = 0; i - j < val.size(); i ++)
	{
		if (v[i] < max1 * threshold)
		{
			val.erase(val.begin() + i - j);
			j++;
		}
	}
	//recurse
	double max2 = 0;
	std::vector<int> best;
	for (unsigned int i = 0; i < val.size(); i++)
	{
		position new_pos;
		pos.copy(new_pos);
		new_pos.move(val[i]);
		const double value = 1 / recurse_val(new_pos, !p, depth);
		if (value >= max2)
		{
			max2 = value;
			best = val[i];
		}
	}
	return best;
}

// game position, which player, how deep to recurse
double computer::recurse_val(position &pos, bool p, int d)
{
	if (d == 0) //reached end of recursion
	{
		return value(pos, p);
	}
	std::vector<std::vector<int> > val;
	pos.valid_moves(val, p);
	if (val.size() == 0) //you have no moves
	{
		return 0.00000001; // you lose, so very bad position
	}
	// filter
	const double threshold = 0.6; // threshold to filter out obviously bad moves
	double max1 = 0;
	std::vector<double> v;
	for (unsigned int i = 0; i < val.size(); i++)
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
	for (unsigned int i = 0; i - j < val.size(); i ++)
	{
		if (v[i] < max1 * threshold)
		{
			val.erase(val.begin() + i - j);
			j++;
		}
	}
	//recurse
	double max2 = 0;
	for (unsigned int i = 0; i < val.size(); i++)
	{
		position new_pos;
		pos.copy(new_pos);
		new_pos.move(val[i]);
		const double value = 1 / recurse_val(new_pos, !p, d - 1);
		if (value > max2)
		{
			max2 = value;
		}
	}
	return max2;
}

double computer::value (position & pos, bool p)
{
	const double e = 0.0000001;// prevents divide by 0
	std::vector<std::vector<int> > v0, v1;
	pos.valid_moves(v0, p);
	pos.valid_moves(v1, !p);
	return (v0.size() + e) / (v1.size() + e);
}

int computer::type ()
{
	return 1;
}

void computer::set_difficulty (int d)
{
	depth = d;
}

computer::computer()
{

}
