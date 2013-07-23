#include "position.h"

position position::copy ()
{
	position new_pos;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			new_pos.board[i][j] = board[i][j];
		}
	}
	return new_pos;
}

void position::move(int x1, int y1, int x2, int y2)
{
	board[x2][y2] = board[x1][y1];
	board[x1][y1] = 0;
}

void position::initialize ()
{
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
		for (int j = 0; j < 9; j ++)
		{
			board[i][j] = initialboard[i][j];
		}
	}
}

std::vector<std::vector<int> > position::valid_moves (bool player) // player: 0 = black/top/positive; 1 = white/bottom/negative
{
	std::vector<std::vector<int> > val_moves;
	bool flag;
	int o = !player * 2 - 1; // o = +1 for player 0 or top or positive, -1 for  player 1 or bottom or negative
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j ++)
		{
			switch (o * board[i][j])
			{
				case 1: //general
					for (int k = -1; k <= 1; k++)
					{
						for (int l = -1; l <= 1; l++)
						{
							if ((k == 0) && (l == 0))
							{
								continue;
							}
							if ((!player) && (i + k <= 2) && (i + k >= 0) && (j + l >= 3) && (j + l <= 5) && (board[i + k][j + l] * o <= 0)) //if on top
							{
								std::vector<int> list;
								list.push_back(i);
								list.push_back(j);
								list.push_back(i + k);
								list.push_back(j + l);
								val_moves.push_back(list);
							}
							else if ((player) && (i + k >= 7) && (i + k <= 9) && (j + l >= 3) && (j + l <= 5) && (board[i + k][j + l] * o <= 0)) //if on bottom
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
						if ((!player) && (i + k <= 9)) //if on top
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
						if ((player) && (i - k >= 0)) //if on bottom
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
					break;
				case 2: //advisor
					for (int k = -1; k <= 1; k += 2)
					{
						for (int l = -1; l <= 1; l += 2)
						{
							if ((!player) && (i + k <= 2) && (i + k >= 0) && (j + l >= 3) && (j + l <= 5) && (board[i + k][j + l] * o <= 0)) //if on top
							{
								std::vector<int> list;
								list.push_back(i);
								list.push_back(j);
								list.push_back(i + k);
								list.push_back(j + l);
								val_moves.push_back(list);
							}
							else if ((player) && (i + k >= 7) && (i + k <= 9) && (j + l >= 3) && (j + l <= 5) && (board[i + k][j + l] * o <= 0)) //if on bottom
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
							if ((!player) && (board[i + k / 2][j + l / 2] == 0) && (i + k <= 4) && (i + k >= 0) && (j + l >= 0) && (j + l <= 8) && (board[i + k][j + l] * o <= 0)) //if on top
							{
								std::vector<int> list;
								list.push_back(i);
								list.push_back(j);
								list.push_back(i + k);
								list.push_back(j + l);
								val_moves.push_back(list);
							}
							else if ((!player) && (board[i + k / 2][j + l / 2] == 0) && (i + k >= 5) && (i + k <= 9) && (j + l >= 0) && (j + l <= 8) && (board[i + k][j + l] * o <= 0)) //if on bottom
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
					if ((i - 2 <= 9) && (board[i - 1][j] == 0))
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
					if ((((!player) && (i >= 5)) || ((player) && (i <= 4))) && (j + 1 <= 8) && (j + 1 >= 0) && (board[i][j + 1]  * o <= 0))
					{
						std::vector<int> list;
						list.push_back(i);
						list.push_back(j);
						list.push_back(i);
						list.push_back(j + 1);
						val_moves.push_back(list);
					}
					if ((((!player) && (i >= 5)) || ((player) && (i <= 4))) && (j - 1 <= 8) && (j - 1 >= 0) && (board[i][j - 1]  * o <= 0))
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
	return val_moves;
}

std::vector<position> position::set_valid_moves (bool player)
{
	std::vector<position> val_pos;
	std::vector<std::vector<int> > val_moves = valid_moves(player);
	for (int i = 0; i < val_moves.size(); i++)
	{
		position new_pos = copy();
		new_pos.move(val_moves[i][0], val_moves[i][1], val_moves[i][2], val_moves[i][3]);
		val_pos.push_back(new_pos);
	}
	return val_pos;
}

double position::value ()
{
	return valid_moves(0).size() / valid_moves(1).size();
}

void position::draw ()
{
	for (int i = 0; i < 0; i++)
	{
		std::cout<<'\n';
	}
	for (int i = 0; i < 10; i ++)
	{
		for (int j = 0; j < 9; j ++)
		{
			std::cout << '[';
			if (board[i][j] > 0)
			{
				std::cout << '+';
			}
			if (board[i][j] == 0)
			{
				std::cout<<'0';
			}
			std::cout << board[i][j] << ']';
		}
		std::cout<<'\n';
	}
	std::cout << "\n\n";
}

position::position ()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			board[i][j] = 0;
		}
	}
}
