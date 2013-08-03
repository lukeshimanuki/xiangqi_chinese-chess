#ifndef DOBUTSU_SHOGI_H__
#define DOBUTSU_SHOGI_H__

#include "position.h"

class dobutsu_shogi : public position
{
public:

	int game_type();

	void valid_moves (std::vector<std::vector<int> > &vec, bool player);
	
	void initialize ();
	
	int winner (bool t);

	dobutsu_shogi();
};

#endif
