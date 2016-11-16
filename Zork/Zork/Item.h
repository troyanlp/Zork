#pragma once
#include <string>
#include "Entity.h"

class Room;

using namespace std;

enum ItemType
{
	COMMON,
	WEAPON,
	ARMOUR
};

class Item : public Entity
{
public:
	Item(const char* name, const char* description, Entity* parent, ItemType item_type = COMMON);
	~Item();

	void Look() const;
	int GetValue() const;
	void Read() const;

public:
	int min_value;
	int max_value;
	ItemType item_type;
	bool pickable;
	bool readable;
	string text;
};
