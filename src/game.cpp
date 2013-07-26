#include "game.h"

void game::set_type (bool a, bool b)
{
	type.clear();
	type.push_back(a);
	type.push_back(b);
}

void game::initialize (bool start) // decides if set board with initial position or empty
{
	pos.initialize();
	pp.clear();
	person new_pers;
	new_pers.set_io(0);
	computer new_comp;
	new_comp.set_depth(1);
	pp.push_back(new_pers);
	pp.push_back(new_pers);
	cp.push_back(new_comp);
	cp.push_back(new_comp);
	turn = 0;
}

void game::take_turn ()
{
	std::vector<int> mov;
	if (type[turn]) // true = person; false = computer
	{
		mov = pp[turn].choose_move(pos, turn);
	}
	else
	{
		mov = cp[turn].choose_move(pos, turn);
	}
	pos.move(mov[0], mov[1], mov[2], mov[3]);
}

void game::play ()
{
	while (true)
	{
		int winner = pos.winner(turn);
		if (winner != 0)
		{
			std::cout<<"Player "<<(int)turn<<" won!\n\n";
			return;
		}
		take_turn();
		turn = !turn;
	}
}

game::game ()
{
}
