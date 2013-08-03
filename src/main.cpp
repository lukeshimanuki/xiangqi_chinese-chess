#include "game.h"

#include <iostream>
#include <stdlib.h>

int main (int argc, char **argv)
{
	std::vector<long int> args;
	for (int i = 1; i < argc; i ++)
	{
		args.push_back(strtol(argv[i], NULL, 10));
	}
	game g;
	if (args.size() >= 1)
	{
		g.set_game_type(args[0]);
	}
	else
	{
		g.set_game_type(0);
	}
	g.initialize();
	if (args.size() >= 3)
	{
		g.set_players(args[1], args[2]);
	}
	else
	{
		g.set_players(0, 0);

	}
	if (args.size() >= 5)
	{
		g.players[0]->set_type(args[3]);
		g.players[1]->set_type(args[4]);
	}
	else
	{
		g.players[0]->set_type(0);
		g.players[1]->set_type(0);
	}
	g.set_log("xiangqi.log");
	g.play();
}
