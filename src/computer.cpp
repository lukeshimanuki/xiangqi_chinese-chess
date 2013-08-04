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
	double max1 = 0;
	std::vector<double> v;
	for (unsigned int i = 0; i < val.size(); i++)
	{
		position *new_pos = new_position(pos.game_type());
		pos.copy(*new_pos);
		new_pos->move(val[i]);
		v.push_back(new_pos->value(p));
		if (v[i] > max1)
		{
			max1 = v[i];
		}
		delete new_pos;
	}
	int j = 0;
	for (unsigned int i = 0; i - j < val.size(); i ++)
	{
		if (v[i] < max1 * options[1])
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
		position *new_pos = new_position(pos.game_type());
		pos.copy(*new_pos);
		new_pos->move(val[i]);
		const double value = 1 / recurse_val(*new_pos, !p, options[0]);
		if (value >= max2)
		{
			max2 = value;
			best = val[i];
		}
		delete new_pos;
	}
	return best;
}

// game position, which player, how deep to recurse
double computer::recurse_val(position &pos, bool p, int d)
{
	const double w = 10000000;
	if (d == 0) //reached end of recursion
	{
		return pos.value(p);
	}
	int winner = pos.winner(p);
	if (winner == p)
	{
		return w * d;
	}
	if (winner == !p)
	{
		return 1 / w / d;
	}
	std::vector<std::vector<int> > val;
	pos.valid_moves(val, p);
	// filter
	double max1 = 0;
	std::vector<double> v;
	for (unsigned int i = 0; i < val.size(); i++)
	{
		position *new_pos = new_position(pos.game_type());
		pos.copy(*new_pos);
		new_pos->move(val[i]);
		v.push_back(new_pos->value(p));
		if (v[i] > max1)
		{
			max1 = v[i];
		}
		delete new_pos;
	}
	int j = 0;
	for (unsigned int i = 0; i - j < val.size(); i ++)
	{
		if (v[i] < max1 * options[2])
		{
			val.erase(val.begin() + i - j);
			j++;
		}
	}
	//recurse
	double max2 = 0;
	for (unsigned int i = 0; i < val.size(); i++)
	{
		position *new_pos = new_position(pos.game_type());
		pos.copy(*new_pos);
		new_pos->move(val[i]);
		const double value = 1 / recurse_val(*new_pos, !p, d - 1);
		if (value > max2)
		{
			max2 = value;
		}
		delete new_pos;
	}
	return max2;
}

position* computer::new_position (int type)
{
	switch (type)
	{
		case 0:
			return new xiangqi;
		case 1:
			return new dobutsu_shogi;
		default:
			return new xiangqi;
	}
}

int computer::player_type ()
{
	return 1;
}

void computer::set_options (std::vector<double> &o)
{
	options = o;
}

computer::computer()
{

}
