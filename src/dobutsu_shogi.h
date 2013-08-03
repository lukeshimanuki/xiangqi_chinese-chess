#ifndef DOBUTSU_SHOGI_H__
#define DOBUTSU_SHOGI_H__

#include "position.h"

class dobutsu_shogi : public position
{
public:

	int game_type();

	double value (bool p);
	
	void move(std::vector<int> &vec);

	void valid_moves (std::vector<std::vector<int> > &vec, bool player);
	
	void initialize ();
	
	int winner (bool t);

	dobutsu_shogi();
	~dobutsu_shogi();
};

#endif
