#include "position.h"
#include "io.h"
#include "player.h"
#include "game.h"

#include <iostream>

int main (int argc, char **argv)
{
	game g;
	g.initialize(1);
	if (argc >= 3)
	{
		g.set_type(argv[1][0] - 48, argv[2][0] - 48);
	}
	else
	{
		g.set_type(1, 1);

	}
	if (argc >= 4)
	{
		g.cp[0].set_depth(argv[3][0] - 48);
		g.cp[1].set_depth(argv[3][0] - 48);
	}
	else
	{
		g.cp[0].set_depth(5);
		g.cp[1].set_depth(5);
	}
	g.set_log("xiangqi.log");
	g.play();
}
