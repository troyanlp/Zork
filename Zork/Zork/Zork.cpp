// Zork.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include "Globals.h"
#include "World.h"

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

	World my_world;
	
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
					cout << BACKSPACE;
					cout << " ";
					/*cout << '\r';
					cout << "You wrote: " << player_input;
					cout << '\r';*/
				}
			}
			else if (key != '\r') // return
			{
				player_input += key;
				cout << key;
			}
			else {
				inputToArguments(player_input, args);
				//cout << '\n';
				//cout << "Los argumentos son: " << args.size() << "\n";
				//for (int i = 0; i < args.size(); ++i)
					//cout << args[i] << '\n';
				
				//args.push_back(player_input);
				/*cout << '\n';
				cout << "You wrote: " << player_input;
				cout << '\n';
				cout << "The args are: " << args[0] << " and " << args[1];
				cout << '\n';*/
			}
				
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

