#include "game.h"

void game::set_players (int a, int b)
{
	players.clear();
	std::vector<player*> p;
	
	// This sets up all possible players
	p.push_back(new person);
	p.push_back(new computer);
	
	// Puts the selected ones into the set of players
	players.push_back(p[a]);
	players.push_back(p[b]);
}


// 0: xiangqi
void game::set_game_type (int t)
{
	std::vector<position*> p;
	//set up all game types
	p.push_back(new xiangqi);
	
	pos = p[t];
}

void game::initialize () // decides if set board with initial position or empty
{
	pos->initialize();
	turn = 0;
}

void game::take_turn ()
{
	std::vector<std::vector<int> > val;
	std::vector<int> mov;
	pos->valid_moves (val, turn);
	bool is_valid = false;
	while (!is_valid)
	{
		mov = players[turn]->choose_move(*pos, turn);
		for (unsigned int i = 0; i < val.size(); i++)
		{
			bool flag = true;
			for (unsigned int j = 0; j < val[i].size(); j++)
			{
				if (mov[j] != val[i][j])
				{
					flag = false;
				}
			}
			if (flag)
			{
				is_valid = true;
			}
		}
	}
	pos->move(mov);
	log_move(mov);
}

void game::play ()
{
	while (true)
	{
		int winner = pos->winner(turn);
		if (winner != -1)
		{
			std::cout<<"Player "<<winner<<" won!\n\n";
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

void game::log_move (std::vector<int> mov)
{
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
			if (pos->board[i][j] > 0)
			{
				logfile << '+'<<pos->board[i][j];
			}
			if (pos->board[i][j] == 0)
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
			if (pos->board[i][j] < 0)
			{
				logfile << pos->board[i][j];
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

game::game ()
{

}
