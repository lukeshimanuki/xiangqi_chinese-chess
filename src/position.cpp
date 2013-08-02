#include "position.h"

void position::copy (position &pos)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			pos.board[i][j] = board[i][j];
		}
	}
}

void position::move(std::vector<int> &vec)
{
	int c = board[vec[0]][vec[1]];
	board[vec[0]][vec[1]] = 0;
	board[vec[2]][vec[3]] = c;
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

void position::set_moves (std::vector<position> &val_pos, std::vector<std::vector<int> > &vec, bool p)
{
	val_pos.clear();
	for (int i = 0; i < vec.size(); i++)
	{
		position new_pos;
		copy(new_pos);
		new_pos.move(vec[i]);
		val_pos.push_back(new_pos);
	}
}

int position::winner (bool t) //t = whose turn it is
{
	std::vector<std::vector<int> > m;
	valid_moves(m, t);
	if (m.size() == 0) // if t has no moves
	{
		return !t; // player !t wins
	}
	return -1;
}

void position::valid_moves (std::vector<std::vector<int> > &val_moves, bool p) // p: 0 = black/top/positive; 1 = red/bottom/negative
{
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
							if ((!p) && (board[i + k / 2][j + l / 2] == 0) && (i + k <= 4) && (i + k >= 0) && (j + l >= 0) && (j + l <= 8) && (board[i + k][j + l] * o <= 0)) //if on top
							{
								std::vector<int> list;
								list.push_back(i);
								list.push_back(j);
								list.push_back(i + k);
								list.push_back(j + l);
								val_moves.push_back(list);
							}
							else if ((!p) && (board[i + k / 2][j + l / 2] == 0) && (i + k >= 5) && (i + k <= 9) && (j + l >= 0) && (j + l <= 8) && (board[i + k][j + l] * o <= 0)) //if on bottom
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


// x is rows, y is columns
position::position ()
{/*
	std::vector<int> p (y, 0);
	std::vector<std::vector<int> > q (x, p);
	board = q;
*/
}
