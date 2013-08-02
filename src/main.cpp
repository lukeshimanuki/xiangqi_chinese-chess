#include "position.h"
#include "io.h"
#include "player.h"
#include "game.h"
#include "xiangqi.h"

#include <iostream>

int main (int argc, char **argv)
{
	xiangqi x;
	x.g.initialize(1);
	if (argc >= 3)
	{
		x.g.set_type(argv[1][0] - 48, argv[2][0] - 48);
	}
	else
	{
		x.g.set_type(1, 1);

	}
	if (argc >= 4)
	{
		x.g.cp[0].set_depth(argv[3][0] - 48);
		x.g.cp[1].set_depth(argv[3][0] - 48);
	}
	else
	{
		x.g.cp[0].set_depth(5);
		x.g.cp[1].set_depth(5);
	}
	x.g.set_log("xiangqi.log");
	x.g.play();
}
