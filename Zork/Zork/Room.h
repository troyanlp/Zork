#pragma once
#include <string>
#include <list>
#include "Entity.h"
#include "Globals.h"
#include "Exit.h"
#include "Item.h"
#include "Creature.h"

class Exit;
class Item;

using namespace std;

class Room : public Entity
{
public:
	Room(const char* name, const char* description);
	~Room();

	void Look() const;

	Exit* GetExit(const string& direction) const;

public:

};