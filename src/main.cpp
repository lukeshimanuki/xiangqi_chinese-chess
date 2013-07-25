#include "position.h"
#include "io.h"
#include "player.h"
#include "game.h"

#include <iostream>

int main (int argc, char **argv)
{
//	position pos;
/*	pos.board[4][4] = 6;
	pos.board[4][5] = 7;
	pos.board[4][3] = 7;
	pos.board[3][4] = 7;
	pos.board[6][4] = 7;
	pos.board[8][4] = -7;
	pos.board[1][4] = -7;
	pos.board[4][1] = -7;
	pos.board[4][7] = -7;*/
//	pos.initialize();
/*	std::cout<<pos.valid_moves(0).size()<<'\n';
	std::cout<<pos.set_valid_moves(0).size()<<'\n';
	std::vector<position> val_pos = pos.set_valid_moves(0);
	for (int i = 0; i < val_pos.size(); i++)
	std::cout<<pos.value()<<'\n';*/
/*	person p;
	p.set_io(0);
	p.choose_move(pos, 0);*/
	game g;
	g.set_type(0,1);
	g.initialize(1);
	g.play();
}
