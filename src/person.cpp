#include "player.h"

std::vector<int> person::choose_move (position &pos, bool p)
{
	in_out[io_type].draw(pos);
	in_out[io_type].message("You are ");
	if (p)
	{	
		in_out[io_type].message("red");
	}
	else
	{
		in_out[io_type].message("black");
	}
	in_out[io_type].message(".\n\nWhich piece do you want to move?\n");
	std::vector<int> o = in_out[io_type].choose_point();
	in_out[io_type].message("\nWhere do you want to move it?\n");
	std::vector<int> n = in_out[io_type].choose_point();
	std::vector<int> m;
std::cout<<"hi\n\n";
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
		in_out[io_type].message("\nPlease choose a valid move.\n");
		return choose_move(pos, p);
	}
}

void person::set_io (int a)
{
	io_type = a;
}

person::person ()
{
	textio tio;
	in_out.push_back(tio);
}
