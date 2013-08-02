#include "position.h"
#include "io.h"
#include "player.h"
#include "game.h"
#include "xiangqi.h"

#include <iostream>

int main (int argc, char **argv)
{
	xiangqi x;
	x.g.initialize();
	if (argc >= 3)
	{
		x.g.set_players(argv[1][0] - 48, argv[2][0] - 48);
	}
	else
	{
		x.g.set_players(0, 0);

	}
	if (argc >= 4)
	{
		x.g.players[0]->set_difficulty(argv[3][0] - 48);
	}
	else
	{
		x.g.players[0]->set_difficulty(5);
	}
	x.g.set_log("xiangqi.log");
	x.g.play();
}
