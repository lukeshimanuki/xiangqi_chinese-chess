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
	message("\nWhere do you want to move it?\n");
	std::vector<int> n = choose_point();
	std::vector<int> m;
	if (pos.is_valid(o[0], o[1], n[0], n[1], p))
	{
		m.push_back(o[0]);
		m.push_back(o[1]);
		m.push_back(n[0]);
		m.push_back(n[1]);
		return m;
	}
	else
	{
		message("\nPlease choose a valid move.\n");
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
