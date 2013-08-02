#ifndef TEXTIO_H__
#define TEXTIO_H__

#include "io.h"

class textio : public io
{
public:
	void draw (position &pos);
	
	void message (std::string a);
	
	std::vector<int> choose_point ();	

	int innum ();
	
	textio ();
};

#endif
