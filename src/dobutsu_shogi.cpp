#include "dobutsu_shogi.h"

void dobutsu_shogi::initialize ()
{
	board.clear();
	
	/* 0 = empty
	 * 1 = lion
	 * 2 = giraffe
	 * 3 = elephant
	 * 4 = chick
	 * 5 = chicken
	 * positive = player 0
	 * negative = player 1
	 */
	int initialboard [4][3] =
		{{	2,1,3	},
		{	0,4,0	},
		{	0,-4,0	},
		{	-3,-1,-2	}};
	for (int i = 0; i < 4; i ++)
	{
		board.push_back(std::vector<int>());
		for (int j = 0; j < 3; j ++)
		{
			board[i].push_back(initialboard[i][j]);
		}
	}
}

int dobutsu_shogi::game_type()
{
	return 1;
}

void dobutsu_shogi::move(std::vector<int> &vec)
{
	bool p = (board[vec[0]][vec[1]] < 0);
	int o = !p - p;
	if (vec[1] >= 3) // drop
	{
		int c = board[vec[0]][vec[1]];
		board[vec[0]].erase(board[vec[0]].begin() + vec[1]);
		board[vec[2]][vec[3]] = c;
	}
	else if ((board[vec[0]][vec[1]] * o == 4) && (vec[2] == 3 * !p)) //chick promotes
	{
		if (board[vec[2]][vec[3]] == 0) // move and promote
		{
			board[vec[0]][vec[1]] = 0;
			board[vec[2]][vec[3]] = 5 * (!p - p);
		}
		else // capture and promote
		{
			board[p].push_back(0 - board[vec[2]][vec[3]]);
			board[vec[0]][vec[1]] = 0;
			board[vec[2]][vec[3]] = 5 * (!p - p);
		}
	}
	else // no promote or drop
	{
		if (board[vec[2]][vec[3]] == 0) // regular move
		{
			int c = board[vec[0]][vec[1]];
			board[vec[0]][vec[1]] = 0;
			board[vec[2]][vec[3]] = c;
		}
		else // capture
		{
			board[p].push_back(0 - board[vec[2]][vec[3]]);
			int c = board[vec[0]][vec[1]];
			board[vec[0]][vec[1]] = 0;
			board[vec[2]][vec[3]] = c;
		}
	}
	if ((board[p].size() >= 4) && (board[p][board[p].size() - 1] * o == 5)) // if chicken is captured
	{
		board[p][board[p].size() - 1] -= o; // turn it into a chick
	}
}

int dobutsu_shogi::winner (bool t) //t = whose turn it is
{
	bool has_lion0 = false, has_lion1 = false;
	for (int i = 0; i < 4; i ++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == 1)
			{
				if (i == 3)
				{
					return 0;
				}
				has_lion0 = true;
			}
			if (board[i][j] == -1)
			{
				if (i == 0)
				{
					return 1;
				}
				has_lion1 = true;
			}
		}
	}
	if (!has_lion0)
	{
		return 1;
	}
	if (!has_lion1)
	{
		return 0;
	}
	return -1;
}

double dobutsu_shogi::value (bool p)
{
	std::vector<int> v(2, 0);
	int o = !p - p;
	const double w = 100000000;
	
	// winning clause
	int win = winner(p);
	if (win != -1)
	{
		if (win == p)
		{
			return w;
		}
		if (win == !p)
		{
			return  1 / w;
		}
	}
	
	// options clause
	std::vector<std::vector<int> > v0, v1;
	valid_moves(v0, p);
	for (unsigned int i = 0; i < v0.size(); i ++)
	{
		if (v0[i][1] <= 2)
		{
			v[0] += 1;
		}
	}
	valid_moves(v1, !p);
	for (unsigned int i = 0; i < v1.size(); i ++)
	{
		if (v1[i][1] <= 2)
		{
			v[1] += 1;
		}
	}
	
	// pieces clause
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j ++)
		{
			switch (board[i][j] * o)
			{
				case 1:
					v[0] += 50;
				case 2:
					v[0] += 3;
					break;
				case 3:
					v[0] += 3;
					break;
				case 4:
					v[0] += 1;
					break;
				case 5:
					v[0] += 5;
					break;
				default:
					break;
			}
			switch (board[i][j] * -o)
			{
				case 1:
					v[1] += 50;
				case 2:
					v[1] += 3;
					break;
				case 3:
					v[1] += 3;
					break;
				case 4:
					v[1] += 1;
					break;
				case 5:
					v[1] += 5;
					break;
				default:
					break;
			}
		}
	}
	return (v[0] + 1 / w) / (v[1] + 1 / w);
}

void dobutsu_shogi::valid_moves (std::vector<std::vector<int> > &val_moves, bool p) // p: 0 = black/top/positive; 1 = red/bottom/negative
{
	val_moves.clear();
	int o = !p * 2 - 1; // o = +1 for p 0 or top or positive, -1 for  p 1 or bottom or negative
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j ++)
		{
			switch (o * board[i][j])
			{
				case 1: //lion
					for (int k = -1; k <= 1; k++)
					{
						for (int l = -1; l <= 1; l++)
						{
							if ((k == 0) && (l == 0))
							{
								continue;
							}
							if ((i + k <= 3) && (i + k >= 0) && (j + l >= 0) && (j + l <= 2) && (board[i + k][j + l] * o <= 0))
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
				case 2: //giraffe
					for (int k = -1; k <= 1; k += 2)
					{
						if ((i + k >= 0) && (i + k <= 3) && (board[i + k][j] * o <= 0))
						{
							std::vector<int> list;
							list.push_back(i);
							list.push_back(j);
							list.push_back(i + k);
							list.push_back(j);
							val_moves.push_back(list);
						}
						if ((j + k >= 0) && (j + k <= 2) && (board[i][j + k] * o <= 0))
						{
							std::vector<int> list;
							list.push_back(i);
							list.push_back(j);
							list.push_back(i);
							list.push_back(j + k);
							val_moves.push_back(list);
						}
					}
					break;
				case 3: //elephant
					for (int k = -1; k <= 1; k += 2)
					{
						for (int l = -1; l <= 1; l += 2)
						{
							if ((i + k <= 3) && (i + k >= 0) && (j + l >= 0) && (j + l <= 2) && (board[i + k][j + l] * o <= 0))
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
				case 4: //chick
					if ((i + o <= 3) && (i + o >= 0) && (board[i + o][j] * o <= 0))
					{
						std::vector<int> list;
						list.push_back(i);
						list.push_back(j);
						list.push_back(i + o);
						list.push_back(j);
						val_moves.push_back(list);
					}
					break;
				case 5: //chicken
					for (int k = -1; k <= 1; k++)
					{
						for (int l = -1; l <= 1; l++)
						{
							if (((k == 0) && (l == 0)) || ((k == -o) && (l != 0)))
							{
								continue;
							}
							if ((i + k <= 3) && (i + k >= 0) && (j + l >= 0) && (j + l <= 2) && (board[i + k][j + l] * o <= 0))
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
			}
		}
	}
	//drop
	for (unsigned int i = 3; i < board[p].size(); i ++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 3; k ++)
			{
				if (board[j][k] == 0)
				{
					std::vector<int> list;
					list.push_back(p);
					list.push_back(i);
					list.push_back(j);
					list.push_back(k);
					val_moves.push_back(list);
				}
			}
		}
	}
}

dobutsu_shogi::dobutsu_shogi ()
{

}

dobutsu_shogi::~dobutsu_shogi ()
{

}
