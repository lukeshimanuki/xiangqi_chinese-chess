#include "game.h"

#include <iostream>
#include <stdlib.h>

void print_disclaimer()
{
	std::cout<<"\nXiangqi Chinese Chess\nCopyright (C) 2013\n\nThis program is free software; you can redistribute it and/or modify\nit under the terms of the GNU General Public License as published by\nthe Free Software Foundation; either version 2 of the License, or\n(at your option) any later version.\n\nThis program is distributed in the hope that it will be useful,\nbut WITHOUT ANY WARRANTY; without even the implied warranty of\nMERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\nGNU General Public License for more details.\n\nYou should have received a copy of the GNU General Public License along\nwith this program; if not, write to the Free Software Foundation, Inc.,\n51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.\n\n";

}

int main (int argc, char **argv)
{
	print_disclaimer();

	if (argc >= 2 && argv[1][0] == 'h')
	{
		std::cout<<"Please enter some arguments\n\nOption 1: game type\n0 - xiangqi\n1 - dobutsu shogi\n\nOptions 2 and 3: players\n0: human\n1: computer\n\nOptions 4 through 9: player settings\nif player is a human:\n+0 - text based interface\n+1 - not in use\n+2 - not in use\nif player is a computer:\n+0 - recursion level\n+1 - trimming factor (first time)\n+2 - trimming factor (every other time)\n\n";//display help message
		return 1; // exit
	}

	std::cout<<"Execute with h to see settings (difficulty, pvp, etc)\n\n";

	std::cout<<"How to Play:\n1: King\n2: Guard\n3: Elephant\n4: Knight\n5: Rook\n6: Cannon\n7: Pawn\n\n";
	std::cout<<"Black: +    Red: -\n";
	std::cout<<"Select a position by (row, column), with (0, 0) as the top left corner\n\n";

	std::vector<long int> args;
	// set defaults
	args.push_back(0);
	args.push_back(0);
	args.push_back(1);
	args.push_back(0);
	args.push_back(4);
	args.push_back(0);
	args.push_back(9);
	args.push_back(0);
	args.push_back(9);
	
	for (int i = 1; i < argc; i ++)
	{
		args[i] = strtol(argv[i], NULL, 10);
	}

	game g;
	if (args.size() >= 2)
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
