#include "io.h"
#include "position.h"
#include <iostream>

void textio::draw (position &pos)
{
	for (int i = 0; i < 0; i++)
	{
		std::cout<<'\n';
	}
	for (int i = 0; i < 10; i ++)
	{
		for (int j = 0; j < 9; j ++)
		{
			std::cout << '[';
			if (pos.board[i][j] > 0)
			{
				std::cout << '+';
			}
			if (pos.board[i][j] == 0)
			{
				std::cout<<'0';
			}
			std::cout << pos.board[i][j] << ']';
		}
		std::cout<<'\n';
	}
	std::cout << "\n\n";
}

int textio::input ()
{
	int a;
	std::cin>>a;
	return a;
}

textio::textio()
{

}
