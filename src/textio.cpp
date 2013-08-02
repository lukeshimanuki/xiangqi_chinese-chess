#include "io.h"
#include "textio.h"

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
				std::cout << '+'<<pos.board[i][j];
			}
			if (pos.board[i][j] == 0)
			{
				std::cout<<"  ";
			}
			if (pos.board[i][j] < 0)
			{
				std::cout<<pos.board[i][j];
			}
			std::cout<<']';
		}
		std::cout<<'\n';
	}
	std::cout << "\n\n";
}

int textio::innum ()
{
	int a;
	std::cin>>a;
	return a;
}

void textio::message (std::string a)
{
	std::cout<<a;
}

std::vector<int> textio::choose_point ()
{
	std::vector<int> point;
	point.push_back(innum());
	point.push_back(innum());
	return point;
}

textio::textio()
{

}
