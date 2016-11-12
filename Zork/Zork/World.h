#ifndef __World__
#define __World__

#include <string>
#include <list>
#include <vector>
#include <time.h>

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

#endif //__World__