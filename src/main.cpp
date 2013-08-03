#include "game.h"

#include <iostream>

int main (int argc, char **argv)
{
	game g;
	if (argc >= 2)
	{
		g.set_game_type(argv[1][0] - 48);
	}
	else
	{
		g.set_game_type(0);
	}
	g.initialize();
	if (argc >= 4)
	{
		g.set_players(argv[2][0] - 48, argv[3][0] - 48);
	}
	else
	{
		g.set_players(0, 0);

	}
	if (argc >= 6)
	{
		g.players[0]->set_type(argv[4][0] - 48);
		g.players[1]->set_type(argv[5][0] - 48);
	}
	else
	{
		g.players[0]->set_type(0);
		g.players[1]->set_type(0);
	}
	g.set_log("xiangqi.log");
	g.play();
}
