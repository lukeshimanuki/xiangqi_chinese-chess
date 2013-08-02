#include "person.h"

std::vector<int> person::choose_move (position &pos, bool p)
{
	in_out[io_type]->draw(pos);
	in_out[io_type]->message("You are ");
	if (p)
	{	
		in_out[io_type]->message("red");
	}
	else
	{
		in_out[io_type]->message("black");
	}
	in_out[io_type]->message(".\n\nWhich piece do you want to move?\n");
	std::vector<int> o = in_out[io_type]->choose_point();
	if (pos.board[o[0]][o[1]] * (2 *!p - 1) <= 0)
	{
		in_out[io_type]->message("Please choose one of your pieces.\n\n");
		return choose_move(pos, p);
	}
	in_out[io_type]->message("\nWhere do you want to move it?\n");
	std::vector<int> n = in_out[io_type]->choose_point();
	o.push_back(n[0]);
	o.push_back(n[1]);
	return o;
}

int person::player_type ()
{
	return 0;
}

void person::set_type(int t)
{
	io_type = t;
}

person::person ()
{
	in_out.push_back (new textio);
}
