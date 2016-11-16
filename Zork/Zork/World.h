#pragma once

#include <string>
#include <list>
#include <vector>
#include <time.h>
#include "Globals.h"
#include "Entity.h"
#include "Player.h"
#include "Room.h"
#include "Exit.h"
#include "Item.h"

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

private:

	clock_t tick_timer;
	list<Entity*> entities;
	Player* player;
};