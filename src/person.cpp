#include "player.h"

std::vector<int> person::choose_move (position &pos, bool p)
{
	draw(pos);
	message("You are ");
	if (p)
	{	
		message("red");
	}
	else
	{
		message("black");
	}
	message(".\n\nWhich piece do you want to move?\n");
	std::vector<int> o = choose_point();
	if (pos.board[o[0]][o[1]] * (2 *!p - 1) <= 0)
	{
		message("Please choose one of your pieces.\n\n");
		return choose_move(pos, p);
	}
	message("\nWhere do you want to move it?\n");
	std::vector<int> n = choose_point();
	std::vector<int> m;
	bool is_valid = false;
	std::vector<std::vector<int> > z;
	pos.valid_moves(z, p);
	for (int i = 0; i < z.size(); i ++)
	{
		if ((o[0] == z[i][0]) && (o[1] == z[i][1]) && (n[0] == z[i][2]) && (n[1] == z[i][3]))
		{
			is_valid = true;
		}
	}
	if (is_valid)
	{
		m.push_back(o[0]);
		m.push_back(o[1]);
		m.push_back(n[0]);
		m.push_back(n[1]);
		return m;
	}
	else
	{
		message("\nPlease choose a valid move.\n\n");
		return choose_move(pos, p);
	}
}

void person::set_io (int a)
{
	io_type = a;
}

void person::draw (position &pos)
{
	textio tio;
	switch (io_type)
	{
		case 0:
			tio.draw(pos);
			break;
		default:
			break;
	}
}

void person::message (std::string a)
{
	textio tio;
	switch (io_type)
	{
		case 0:
			tio.message(a);
			break;
		default:
			break;
	}
}

std::vector<int> person::choose_point ()
{
	textio tio;
	switch (io_type)
	{
		case 0:
			return tio.choose_point();
		default:
			break;
	}
}

person::person ()
{
}
