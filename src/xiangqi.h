#ifndef XIANGQI_H__
#define XIANGQI_H__

#include "position.h"

class xiangqi : public position
{
public:

	void valid_moves (std::vector<std::vector<int> > &vec, bool player);
	
	void initialize ();
	
	int winner (bool t);

	xiangqi();
};

#endif
