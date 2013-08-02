#include "xiangqi.h"

#include <iostream>

int main (int argc, char **argv)
{
	xiangqi x;
	x.initialize();
	if (argc >= 3)
	{
		x.set_players(argv[1][0] - 48, argv[2][0] - 48);
	}
	else
	{
		x.set_players(0, 0);

	}
	if (argc >= 5)
	{
		x.players[0]->set_type(argv[3][0] - 48);
		x.players[1]->set_type(argv[4][0] - 48);
	}
	else
	{
		x.players[0]->set_type(0);
		x.players[1]->set_type(0);
	}
	x.set_log("xiangqi.log");
	x.play();
}
