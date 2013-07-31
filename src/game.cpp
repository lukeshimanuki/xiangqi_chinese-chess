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
	new_comp.set_depth(2);
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
	pos.move(mov);
	
	// log
	std::ofstream logfile(log.c_str(), std::ios::app);
	logfile<<"It is now player "<<(int)turn<<"'s turn.\nPlayer "<<(int) turn<<" moves piece ("<<mov[0]<<','<<mov[1]<<") to ("<<mov[2]<<','<<mov[3]<<").\n";
	for (int i = 0; i < 10; i ++)
	{
		for (int j = 0; j < 9; j ++)
		{
			if ((i == mov[2]) && (j == mov[3]))
			{
				logfile << '$';
			}
			else
			{
				logfile << '[';
			}
			if (pos.board[i][j] > 0)
			{
				logfile << '+'<<pos.board[i][j];
			}
			if (pos.board[i][j] == 0)
			{
				if ((i == mov[0]) && (j == mov[1]))
				{
					logfile << "00";
				}
				else
				{
					logfile << "  ";
				}
			}
			if (pos.board[i][j] < 0)
			{
				logfile << pos.board[i][j];
			}
			if ((i == mov[2]) && (j == mov[3]))
			{
				logfile << '$';
			}
			else
			{
				logfile << ']';
			}
		}
		logfile<<'\n';
	}
	logfile << "\n\n";
}

void game::play ()
{
	while (true)
	{
		int winner = pos.winner(turn);
		if (winner != -1)
		{
			std::cout<<"Player "<<winner<<" won!\n\n";
			std::ofstream logfile(log.c_str(), std::ios::app);
			logfile << "Player " << winner << " won!\n";
			std::exit(0);
		}
		take_turn();
		turn = !turn;
	}
}

void game::set_log(std::string filename)
{
	log = filename;
	std::ofstream logfile(log.c_str(), std::ios::trunc);
}

game::game ()
{

}
