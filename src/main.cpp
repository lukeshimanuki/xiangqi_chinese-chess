#include "game.h"

#include <iostream>
#include <stdlib.h>

int main (int argc, char **argv)
{
	if (argc == 1) // no arguments
	{
		std::cout<<"Please enter some arguments\n\nOption 1: game type\n0 - xiangqi\n1 - dobutsu shogi\n\nOptions 2 and 3: players\n0: human\n1: computer\n\nOptions 4 through 9: player settings\nif player is a human:\n0 - text based interface \nif player is a computer: general difficulty settings\n\n";//display help message
		return 1; // exit
	}
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
	if (args.size() >= 3)
	{
		g.set_players(args[1], args[2]);
	}
	else
	{
		g.set_players(0, 0);
	}
	g.initialize();
	
	for (unsigned int i = 0; i < 15 - args.size(); i ++)
	{
		args.push_back(0);
	}
	std::vector<std::vector<double> > opt (2, std::vector<double> ());
	for (unsigned int i = 3; i < args.size(); i ++) // skip first one, it refers to game_type
	{
		if ((i >= 5) && (i <= 8)) // needs to be converted to decimal
		{
			double d = args[i];
			while (d >= 1)
			{
				d /= 10;
			}
			opt[(i + 1) % 2].push_back(d);
		}
		else // normal case
		{
			opt[(i + 1) % 2].push_back(args[i]);
		}
	}
	
	g.players[0]->set_options(opt[0]);
	g.players[1]->set_options(opt[1]);
	
	g.set_log("xiangqi.log");
	g.play();
}
