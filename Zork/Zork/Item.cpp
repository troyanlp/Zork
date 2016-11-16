#include <iostream>
#include "Room.h"
#include "Exit.h"
#include "Globals.h"
#include "Item.h"

// ----------------------------------------------------
Item::Item(const char* title, const char* description, Entity* parent, ItemType item_type) :
	Entity(title, description, parent), item_type(item_type)
{
	type = ITEM;
	min_value = max_value = 0;
	pickable = true;
	readable = false;
	weight = 0;
}

// ----------------------------------------------------
Item::~Item()
{}

// ----------------------------------------------------
void Item::Look() const
{
	cout << "\n" << name << "\n";
	if(weight > 0) cout << "\n(" << weight << "Kg)\n";
	cout << description << "\n";

	list<Entity*> stuff;
	FindAll(ITEM, stuff);

	if (stuff.size() > 0)
	{
		cout << "It contains: " << "\n";
		for (list<Entity*>::const_iterator it = stuff.begin(); it != stuff.cend(); ++it) {
			cout << (*it)->name;
			if ((*it)->weight > 0) {
				cout << " (" << weight << "Kg)\n";
			}
			else
			{
				cout << "\n";
			}
		}
	}
}

// ----------------------------------------------------
int Item::GetValue() const
{
	return 0;
	//return Roll(min_value, max_value);
}

// ----------------------------------------------------
void Item::Read() const
{
	if (readable) {
		cout << name << "says:\n";
		cout << text;
	} else{
		cout << "You can't read " << name;
	}
}

// ----------------------------------------------------
bool Item::RightWeigth() const
{
	float count = 0;
	for (list<Entity*>::const_iterator it = parent->container.begin(); it != parent->container.cend(); ++it)
	{
		//cout << "The entity is: " << (*it)->name << "\n";
		if (Same((*it)->name, "Button")) {
			for (list<Entity*>::const_iterator itt = (*it)->container.begin(); itt != (*it)->container.cend(); ++itt)
			{
				count += (*it)->weight;
			}
		}
	}

	if (count == 5) {
		return true;
	}
	else {
		return false;
	}
}