#include "position.h"

void position::copy (position &pos)
{
	pos.board = board;
}

void position::set_moves (std::vector<position*> &val_pos, std::vector<std::vector<int> > &vec, bool p)
{
	val_pos.clear();
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		position *new_pos;
		copy(*new_pos);
		new_pos->move(vec[i]);
		val_pos.push_back(new_pos);
	}
}

position::position ()
{

}

position::~position ()
{

}
