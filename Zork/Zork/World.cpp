#include <iostream>
#include "World.h"
#include "Room.h"

// ----------------------------------------------------
World::World()
{
	tick_timer = clock();

	// Rooms ----
	Room* outside = new Room("Outside", "You are surrounded by trees and bushes. There's and old house in front of you");
	Room* mainRoom = new Room("Main Room", "You are inside a dark and smelly room.");
	Room* chestRoom = new Room("Chest Room", "You are inside a room with a chest.");
	Room* enemyRoom = new Room("Enemy Room", "You are inside a room with more light than the others. There's someone.");
	Room* transitionRoom = new Room("Transition Room", "You are in a hallway.");
	Room* gardenRoom = new Room("Garden", "You are in a garden.");
	Room* bossRoom = new Room("Boss Room", "You are in a basement.");

	Exit* ex1 = new Exit("north", "south", "Little path", outside, mainRoom); //From outside to the main room
	ex1->locked = true;
	Exit* ex2 = new Exit("north", "south", "Stairs", mainRoom, gardenRoom); //From the main room to the garden
	ex2->locked = true;
	Exit* ex3 = new Exit("east", "west", "Little path", mainRoom, chestRoom); //From the main room to the chest room
	Exit* ex4 = new Exit("north", "south", "Stairs", chestRoom, enemyRoom); //From the chest room to the enemy room
	Exit* ex5 = new Exit("east", "west", "Little path", mainRoom, transitionRoom); //From the main room to the transition room
	ex5->locked = true;
	Exit* ex6 = new Exit("down", "up", "Stairs", transitionRoom, bossRoom); //From the transition room to the boss room
	ex6->locked = true;

	entities.push_back(outside);
	entities.push_back(mainRoom);
	entities.push_back(chestRoom);
	entities.push_back(enemyRoom);
	entities.push_back(transitionRoom);
	entities.push_back(gardenRoom);
	entities.push_back(bossRoom);
	
	entities.push_back(ex1);
	entities.push_back(ex2);
	entities.push_back(ex3);
	entities.push_back(ex4);
	entities.push_back(ex5);
	entities.push_back(ex6);

	// Creatures ----

	// Items -----
	Item* mailbox = new Item("Mailbox", "Looks like it might contain something.", outside);
	Item* key1 = new Item("Key", "Old iron key.", mailbox);
	ex1->key = key1;
	Item* note = new Item("Note", "A piece of paper with something written on it", mailbox);
	Item* shovel = new Item("Shovel", "A dirty shovel.", outside);
	Item* box = new Item("Box", "A box.", mainRoom);
	Item* key2 = new Item("Key", "Old iron key.", box);
	ex2->key = key2;
	Item* button = new Item("Button", "A button with '5Kg' written on it", mainRoom);
	Item* chest = new Item("Chest", "A shiny chest.", chestRoom);
	Item* sword = new Item("Sword", "A sharp sword.", chest);
	Item* key3 = new Item("Key", "A big key with 'BOSS' written on it.", mailbox);
	ex6->key = key3;

	entities.push_back(mailbox);
	entities.push_back(key1);
	entities.push_back(note);
	entities.push_back(shovel);
	entities.push_back(box);
	entities.push_back(key2);
	entities.push_back(button);
	entities.push_back(chest);
	entities.push_back(sword);
	entities.push_back(key3);
	

	// Player ----
	player = new Player("Hero", "You are a thief looking for gold!", outside);
	entities.push_back(player);

}

// ----------------------------------------------------
World::~World()
{
	for (list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		delete *it;

	entities.clear();
}

// ----------------------------------------------------
bool World::Tick(vector<string>& args)
{
	bool ret = true;
	
	if (args.size() > 0 && args[0].length() > 0)
		ret = ParseCommand(args);

	GameLoop();

	return ret;
}

// ----------------------------------------------------
void World::GameLoop()
{
	clock_t now = clock();

	if ((now - tick_timer) / CLOCKS_PER_SEC > TICK_FREQUENCY)
	{
		for (list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
			(*it)->Tick();

		tick_timer = now;
	}
}

// ----------------------------------------------------
bool World::ParseCommand(vector<string>& args)
{
	bool ret = true;

	switch (args.size())
	{
		case 1: //Commands with no argument
			if (Same(args[0], "look") || Same(args[0], "l"))
			{
				player->Look(args);
			}
			else if (Same(args[0], "north") || Same(args[0], "n"))
			{
				(args.size() == 1) ? args.push_back("north") : args[1] = "north";
				player->Go(args);
			}
			else if (Same(args[0], "south") || Same(args[0], "s"))
			{
				(args.size() == 1) ? args.push_back("south") : args[1] = "south";
				player->Go(args);
			}
			else if (Same(args[0], "east") || Same(args[0], "e"))
			{
				(args.size() == 1) ? args.push_back("east") : args[1] = "east";
				player->Go(args);
			}
			else if (Same(args[0], "west") || Same(args[0], "w"))
			{
				(args.size() == 1) ? args.push_back("west") : args[1] = "west";
				player->Go(args);
			}
			else if (Same(args[0], "up") || Same(args[0], "u"))
			{
				(args.size() == 1) ? args.push_back("up") : args[1] = "up";
				player->Go(args);
			}
			else if (Same(args[0], "down") || Same(args[0], "d"))
			{
				(args.size() == 1) ? args.push_back("down") : args[1] = "down";
				player->Go(args);
			}
			else if (Same(args[0], "inventory") || Same(args[0], "i"))
			{
				player->Inventory();
			}
			else
				ret = false;
			break;
		case 2: //Commands with one argument
			if (Same(args[0], "look") || Same(args[0], "l"))
			{
				player->Look(args);
			}
			else if (Same(args[0], "go"))
			{
				player->Go(args);
			}
			else if (Same(args[0], "take") || Same(args[0], "pick"))
			{
				player->Take(args);
			}
			else if (Same(args[0], "drop") || Same(args[0], "put"))
			{
				player->Drop(args);
			}
			break;
		case 3: //Commands with two argument
			break;
		case 4: //Commands with three argument
			if (Same(args[0], "unlock") || Same(args[0], "unlk"))
			{
				player->UnLock(args);
			}
			else if (Same(args[0], "take") || Same(args[0], "pick"))
			{
				player->Take(args);
			}
			else if (Same(args[0], "drop") || Same(args[0], "put"))
			{
				player->Drop(args);
			}
			else {
				ret = false;
			}
			break;
		default:
			ret = false;
	}

	return ret;
}