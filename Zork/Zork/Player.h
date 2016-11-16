#pragma once
#include <iostream>
#include "Exit.h"
#include "Globals.h"
#include "Room.h"
#include "Creature.h"
#include "Item.h"

class Player : public Creature
{
public:
	Player(const char* name, const char* description, Room* room);
	~Player();

	bool Go(const vector<string>& args);
	void Look(const vector<string>& args) const;
	bool Take(const vector<string>& args);
	bool Drop(const vector<string>& args);
	void Inventory() const;
	bool UnLock(const vector<string>& args);
};

