#ifndef IO_H__
#define IO_H__

#include <string>
#include "position.h"

class io
{
public:
	void draw (position &pos);
	
	void message (std::string a);
	
	std::vector<int> choose_point ();
	
	io ();
};

class textio : public io
{
public:
	void draw (position &pos);
	
	void message (std::string a);
	
	int innum ();
	
	std::vector<int> choose_point ();
	
	textio ();
};

#endif
