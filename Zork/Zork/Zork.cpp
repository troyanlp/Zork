// Zork.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <conio.h>

using namespace std;

#define BACKSPACE "\033[D\033[K"

#define RED_ "\033[0;31m"
#define RED     "\033[31m"      /* Red */
#define _RED "\033[0m"


int main()
{

	char key;
	string player_input;
	vector<string> args;
	args.reserve(10);

	cout << "Welcome to The Legend of Zork!!\n";
	cout << "----------------\n";
	
	args.push_back("look");

	while (1)
	{
		if (_kbhit() != 0)
		{
			key = _getch();
			if (key == '\b') // backspace
			{
				if (player_input.length() > 0)
				{
					player_input.pop_back();
					//cout << BACKSPACE;
					cout << '\b';
					cout << " ";
					cout << '\b';
				}
			}
			else if (key != '\r') // return
			{
				player_input += key;
				cout << key;
			}
			else
				Tokenize(player_input, args);
		}

		if (args.size() > 0 && Same(args[0], "quit"))
			break;

		if (my_world.Tick(args) == false)
			cout << "\nSorry, I do not understand your command.\n";

		if (args.size() > 0)
		{
			args.clear();
			player_input = "";
			cout << "> ";
		}
	}

	cout << "\nThanks for playing, Bye!\n";

    return 0;
}

