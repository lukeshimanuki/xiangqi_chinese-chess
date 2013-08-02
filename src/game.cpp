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

void game::initialize () // decides if set board with initial position or empty
{
	std::vector<std::vector<int> > board;
	int initialboard [10][9] =
		{{	5,4,3,2,1,2,3,4,5		},
		{	0,0,0,0,0,0,0,0,0		},
		{	0,6,0,0,0,0,0,6,0		},
		{	7,0,7,0,7,0,7,0,7		},
		{	0,0,0,0,0,0,0,0,0		},
		{	0,0,0,0,0,0,0,0,0		},
		{	-7,0,-7,0,-7,0,-7,0,-7	},
		{	0,-6,0,0,0,0,0,-6,0		},
		{	0,0,0,0,0,0,0,0,0		},
		{	-5,-4,-3,-2,-1,-2,-3,-4,-5}};
	for (int i = 0; i < 10; i ++)
	{
		std::vector<int> p;
		for (int j = 0; j < 9; j ++)
		{
			p.push_back(initialboard[i][j]);
		}
		board.push_back(p);
	}
	pos.initialize(board);
	turn = 0;
}

void game::take_turn ()
{
	std::vector<std::vector<int> > val;
	std::vector<int> mov;
	valid_moves (val, pos, turn);
	bool is_valid = false;
	while (!is_valid)
	{
		mov = players[turn]->choose_move(pos, turn);
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
	pos.move(mov);
	log_move(mov);
}

void game::play ()
{
	while (true)
	{
		int winner = pos.winner(turn);
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

int game::winner (position &pos, bool t) //t = whose turn it is
{
	std::vector<std::vector<int> > m;
	valid_moves(m, pos, t);
	if (m.size() == 0) // if t has no moves
	{
		return !t; // player !t wins
	}
	return -1;
}

void game::valid_moves (std::vector<std::vector<int> > &val_moves, position &pos, bool p) // p: 0 = black/top/positive; 1 = red/bottom/negative
{
	std::vector<std::vector<int> > board = pos.board;
	val_moves.clear();
	bool flag;
	bool has_gen = false;
	int o = !p * 2 - 1; // o = +1 for p 0 or top or positive, -1 for  p 1 or bottom or negative
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j ++)
		{
			switch (o * board[i][j])
			{
				case 1: //general
					has_gen = true;
					for (int k = -1; k <= 1; k++)
					{
						for (int l = -1; l <= 1; l++)
						{
							if ((k == 0) && (l == 0))
							{
								continue;
							}
							if ((!p) && (i + k <= 2) && (i + k >= 0) && (j + l >= 3) && (j + l <= 5) && (board[i + k][j + l] * o <= 0)) //if on top
							{
								std::vector<int> list;
								list.push_back(i);
								list.push_back(j);
								list.push_back(i + k);
								list.push_back(j + l);
								val_moves.push_back(list);
							}
							else if ((p) && (i + k >= 7) && (i + k <= 9) && (j + l >= 3) && (j + l <= 5) && (board[i + k][j + l] * o <= 0)) //if on bottom
							{
								std::vector<int> list;
								list.push_back(i);
								list.push_back(j);
								list.push_back(i + k);
								list.push_back(j + l);
								val_moves.push_back(list);
							}
						}
					}
					// flying general move
					for (int k = 0; k <= 9; k++)
					{
						if ((!p) && (i + k <= 9)) //if on top
						{
							if (board[i + k][j] == -1)
							{
								std::vector<int> list;
								list.push_back(i);
								list.push_back(j);
								list.push_back(i + k);
								list.push_back(j);
								val_moves.push_back(list);
							}
							else if (board[i + k][j] ==0)
							{
								continue;
							}
							else
							{
								break;
							}
						}
						if ((p) && (i - k >= 0)) //if on bottom
						{
							if (board[i - k][j] == 1)
							{
								std::vector<int> list;
								list.push_back(i);
								list.push_back(j);
								list.push_back(i - k);
								list.push_back(j);
								val_moves.push_back(list);
							}
							else if (board[i - k][j] ==0)
							{
								continue;
							}
							else
							{
								break;
							}
						}
					}
					break;
				case 2: //advisor
					for (int k = -1; k <= 1; k += 2)
					{
						for (int l = -1; l <= 1; l += 2)
						{
							if ((!p) && (i + k <= 2) && (i + k >= 0) && (j + l >= 3) && (j + l <= 5) && (board[i + k][j + l] * o <= 0)) //if on top
							{
								std::vector<int> list;
								list.push_back(i);
								list.push_back(j);
								list.push_back(i + k);
								list.push_back(j + l);
								val_moves.push_back(list);
							}
							else if ((p) && (i + k >= 7) && (i + k <= 9) && (j + l >= 3) && (j + l <= 5) && (board[i + k][j + l] * o <= 0)) //if on bottom
							{
								std::vector<int> list;
								list.push_back(i);
								list.push_back(j);
								list.push_back(i + k);
								list.push_back(j + l);
								val_moves.push_back(list);
							}
						}
					}
					break;
				case 3: //elephant
					for (int k = -2; k <= 2; k += 4)
					{
						for (int l = -2; l <= 2; l += 4)
						{
							if ((!p) && (i + k <= 4) && (i + k >= 0) && (j + l >= 0) && (j + l <= 8) && (board[i + k / 2][j + l / 2] == 0) && (board[i + k][j + l] * o <= 0)) //if on top
							{
								std::vector<int> list;
								list.push_back(i);
								list.push_back(j);
								list.push_back(i + k);
								list.push_back(j + l);
								val_moves.push_back(list);
							}
							else if ((p) && (i + k >= 5) && (i + k <= 9) && (j + l >= 0) && (j + l <= 8) && (board[i + k / 2][j + l / 2] == 0) && (board[i + k][j + l] * o <= 0)) //if on bottom
							{
								std::vector<int> list;
								list.push_back(i);
								list.push_back(j);
								list.push_back(i + k);
								list.push_back(j + l);
								val_moves.push_back(list);
							}
						}
					}
					break;
				case 4: //horse
					if ((i + 2 <= 9) && (board[i + 1][j] == 0))
					{
						if ((j + 1 <= 8) && (board[i + 2][j + 1] * o <= 0))
						{
							std::vector<int> list;
							list.push_back(i);
							list.push_back(j);
							list.push_back(i + 2);
							list.push_back(j + 1);
							val_moves.push_back(list);
						}
						if ((j - 1 >= 0) && (board[i + 2][j - 1] * o <= 0))
						{
							std::vector<int> list;
							list.push_back(i);
							list.push_back(j);
							list.push_back(i + 2);
							list.push_back(j - 1);
							val_moves.push_back(list);
						}
					}
					if ((i - 2 >= 0) && (board[i - 1][j] == 0))
					{
						if ((j + 1 <= 8) && (board[i - 2][j + 1] * o <= 0))
						{
							std::vector<int> list;
							list.push_back(i);
							list.push_back(j);
							list.push_back(i - 2);
							list.push_back(j + 1);
							val_moves.push_back(list);
						}
						if ((j - 1 >= 0) && (board[i - 2][j - 1] * o <= 0))
						{
							std::vector<int> list;
							list.push_back(i);
							list.push_back(j);
							list.push_back(i - 2);
							list.push_back(j - 1);
							val_moves.push_back(list);
						}
					}
					if ((j + 2 <= 8) && (board[i][j + 1] == 0))
					{
						if ((i + 1 <= 9) && (board[i + 1][j + 2] * o <= 0))
						{
							std::vector<int> list;
							list.push_back(i);
							list.push_back(j);
							list.push_back(i + 1);
							list.push_back(j + 2);
							val_moves.push_back(list);
						}
						if ((i - 1 >= 0) && (board[i - 1][j + 2] * o <= 0))
						{
							std::vector<int> list;
							list.push_back(i);
							list.push_back(j);
							list.push_back(i - 1);
							list.push_back(j + 2);
							val_moves.push_back(list);
						}
					}
					if ((j - 2 >= 0) && (board[i][j - 1] == 0))
					{
						if ((i + 1 <= 9) && (board[i + 1][j - 2] * o <= 0))
						{
							std::vector<int> list;
							list.push_back(i);
							list.push_back(j);
							list.push_back(i + 1);
							list.push_back(j - 2);
							val_moves.push_back(list);
						}
						if ((i - 1 >= 0) && (board[i - 1][j - 2] * o <= 0))
						{
							std::vector<int> list;
							list.push_back(i);
							list.push_back(j);
							list.push_back(i - 1);
							list.push_back(j - 2);
							val_moves.push_back(list);
						}
					}
					break;
				case 5: //chariot
					for (int k = 1; k <= 9; k++)
					{
						if ((i + k <= 9) && (board[i + k][j] == 0))
						{
							std::vector<int> list;
							list.push_back(i);
							list.push_back(j);
							list.push_back(i + k);
							list.push_back(j);
							val_moves.push_back(list);
						}
						else if ((i + k <= 9) && (board[i + k][j] * o <= 0))
						{
							std::vector<int> list;
							list.push_back(i);
							list.push_back(j);
							list.push_back(i + k);
							list.push_back(j);
							val_moves.push_back(list);
							break;
						}
						else
						{
							break;
						}
					}
					for (int k = 1; k <= 9; k++)
					{
						if ((i - k >= 0) && (board[i - k][j] == 0))
						{
							std::vector<int> list;
							list.push_back(i);
							list.push_back(j);
							list.push_back(i - k);
							list.push_back(j);
							val_moves.push_back(list);
						}
						else if ((i - k >= 0) && (board[i - k][j] * o <= 0))
						{
							std::vector<int> list;
							list.push_back(i);
							list.push_back(j);
							list.push_back(i - k);
							list.push_back(j);
							val_moves.push_back(list);
							break;
						}
						else
						{
							break;
						}
					}
					for (int k = 1; k <= 8; k++)
					{
						if ((j + k <= 8) && (board[i][j + k] == 0))
						{
							std::vector<int> list;
							list.push_back(i);
							list.push_back(j);
							list.push_back(i);
							list.push_back(j + k);
							val_moves.push_back(list);
						}
						else if ((j + k <= 8) && (board[i][j + k] * o <= 0))
						{
							std::vector<int> list;
							list.push_back(i);
							list.push_back(j);
							list.push_back(i);
							list.push_back(j + k);
							val_moves.push_back(list);
							break;
						}
						else
						{
							break;
						}
					}
					for (int k = 1; k <= 8; k++)
					{
						if ((j - k >= 0) && (board[i][j - k] == 0))
						{
							std::vector<int> list;
							list.push_back(i);
							list.push_back(j);
							list.push_back(i);
							list.push_back(j - k);
							val_moves.push_back(list);
						}
						else if ((j - k >= 0) && (board[i][j - k] * o<= 0))
						{
							std::vector<int> list;
							list.push_back(i);
							list.push_back(j);
							list.push_back(i);
							list.push_back(j - k);
							val_moves.push_back(list);
							break;
						}
						else
						{
							break;
						}
					}
					break;
				case 6: //cannon
					flag = true;
					for (int k = 1; k <= 9; k++)
					{
						if ((flag) && (i + k <= 9) && (board[i + k][j] == 0))
						{
							std::vector<int> list;
							list.push_back(i);
							list.push_back(j);
							list.push_back(i + k);
							list.push_back(j);
							val_moves.push_back(list);
						}
						else if ((flag) && (i + k <= 9) && (board[i + k][j] != 0))
						{
							flag = false;
						}
						else if ((!flag) && (i + k <= 9) && (board[i + k][j] == 0))
						{
							continue;
						}
						else if ((!flag) && (i + k <= 9) && (board[i + k][j] != 0))
						{
							std::vector<int> list;
							list.push_back(i);
							list.push_back(j);
							list.push_back(i + k);
							list.push_back(j);
							val_moves.push_back(list);
							break;
						}
						else
						{
							break;
						}
					}
					flag = true;
					for (int k = 1; k <= 9; k++)
					{
						if ((flag) && (i - k >= 0) && (board[i - k][j] == 0))
						{
							std::vector<int> list;
							list.push_back(i);
							list.push_back(j);
							list.push_back(i - k);
							list.push_back(j);
							val_moves.push_back(list);
						}
						else if ((flag) && (i - k >= 0) && (board[i - k][j] != 0))
						{
							flag = false;
						}
						else if ((!flag) && (i - k >= 0) && (board[i - k][j] == 0))
						{
							continue;
						}
						else if ((!flag) && (i - k >= 0) && (board[i - k][j] != 0))
						{
							std::vector<int> list;
							list.push_back(i);
							list.push_back(j);
							list.push_back(i - k);
							list.push_back(j);
							val_moves.push_back(list);
							break;
						}
						else
						{
							break;
						}
					}
					flag = true;
					for (int k = 1; k <= 8; k++)
					{
						if ((flag) && (j + k <= 8) && (board[i][j + k] == 0))
						{
							std::vector<int> list;
							list.push_back(i);
							list.push_back(j);
							list.push_back(i);
							list.push_back(j + k);
							val_moves.push_back(list);
						}
						else if ((flag) && (j + k <= 8) && (board[i][j + k] != 0))
						{
							flag = false;
						}
						else if ((!flag) && (j + k <= 8) && (board[i][j + k] == 0))
						{
							continue;
						}
						else if ((!flag) && (j + k <= 8) && (board[i][j + k] != 0))
						{
							std::vector<int> list;
							list.push_back(i);
							list.push_back(j);
							list.push_back(i);
							list.push_back(j + k);
							val_moves.push_back(list);
							break;
						}
						else
						{
							break;
						}
					}
					flag = true;
					for (int k = 1; k <= 8; k++)
					{
						if ((flag) && (j - k >= 0) && (board[i][j - k] == 0))
						{
							std::vector<int> list;
							list.push_back(i);
							list.push_back(j);
							list.push_back(i);
							list.push_back(j - k);
							val_moves.push_back(list);
						}
						else if ((flag) && (j - k >= 0) && (board[i][j - k] != 0))
						{
							flag = false;
						}
						else if ((!flag) && (j - k >= 0) && (board[i][j - k] == 0))
						{
							continue;
						}
						else if ((!flag) && (j - k >= 0) && (board[i][j - k] != 0))
						{
							std::vector<int> list;
							list.push_back(i);
							list.push_back(j);
							list.push_back(i);
							list.push_back(j - k);
							val_moves.push_back(list);
							break;
						}
						else
						{
							break;
						}
					}
					break;
				case 7: //soldier
					if ((i + o <= 9) && (i + o >= 0) && (board[i + o][j]  * o <= 0))
					{
						std::vector<int> list;
						list.push_back(i);
						list.push_back(j);
						list.push_back(i + o);
						list.push_back(j);
						val_moves.push_back(list);
					}
					if ((((!p) && (i >= 5)) || ((p) && (i <= 4))) && (j + 1 <= 8) && (j + 1 >= 0) && (board[i][j + 1]  * o <= 0))
					{
						std::vector<int> list;
						list.push_back(i);
						list.push_back(j);
						list.push_back(i);
						list.push_back(j + 1);
						val_moves.push_back(list);
					}
					if ((((!p) && (i >= 5)) || ((p) && (i <= 4))) && (j - 1 <= 8) && (j - 1 >= 0) && (board[i][j - 1]  * o <= 0))
					{
						std::vector<int> list;
						list.push_back(i);
						list.push_back(j);
						list.push_back(i);
						list.push_back(j - 1);
						val_moves.push_back(list);
					}
					break;
				default:
					break;
			}
		}
	}
	// if no general, you lose, so no valid moves
	if (!has_gen)
	{
		val_moves.clear();
	}
}

game::game ()
{

}
