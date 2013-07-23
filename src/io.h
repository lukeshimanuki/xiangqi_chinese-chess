#include <string>
#include "position.h"

class io
{
public:
	void draw (position &pos);
	
	int input ();
	
	io ()
	{
	
	}
};

class textio : public io
{
public:
	void draw (position &pos);
	
	int input ();
	
	textio ();
};
