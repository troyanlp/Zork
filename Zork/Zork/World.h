#pragma once

#include <string>
#include <list>
#include <vector>
#include <time.h>

using namespace std;

#define TICK_FREQUENCY 0.5f

class World
{
public:
	
	World();
	~World();

	bool Tick(vector<string>& args);
	bool ParseCommand(vector<string>& args);
	void GameLoop();
};