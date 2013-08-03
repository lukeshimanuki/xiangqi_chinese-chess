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
	int initialboard [4][7] =
		{{	2,1,3,0,0,0,0		},
		{	0,4,0,0,0,0,0		},
		{	0,-4,0,0,0,0,0		},
		{	-3,-1,-2,0,0,0,0	}};
	for (int i = 0; i < 4; i ++)
	{
		board.push_back(std::vector<int>());
		for (int j = 0; j < 7; j ++)
		{
			board[i].push_back(initialboard[i][j]);
		}
	}
}

int dobutsu_shogi::game_type()
{
	return 1;
}

int dobutsu_shogi::winner (bool t) //t = whose turn it is
{
	int o = !t - t;
	bool has_lion = false;
	for (int i = 0; i < 4; i ++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == o) //player's lion
			{
				if (i == (3 + 2 * o) / 2) //on back row
				{
					return t;
				}
				has_lion = true;
			}
		}
	}
	if (!has_lion) // player doesn't have a lion
	{
		return !t; // enemy wins
	}
	return -1;
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
}

dobutsu_shogi::dobutsu_shogi ()
{

}
