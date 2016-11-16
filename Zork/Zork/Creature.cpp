#include <iostream>
#include "Globals.h"
#include "Room.h"
#include "Exit.h"
#include "Item.h"
#include "Creature.h"

// ----------------------------------------------------
Creature::Creature(const char* title, const char* description, Room* room) :
	Entity(title, description, (Entity*)room)
{
	type = CREATURE;
	hit_points = 1;
	min_damage = max_damage = min_protection = max_protection = 0;
}

// ----------------------------------------------------
Creature::~Creature()
{}

// ----------------------------------------------------
void Creature::Look(const vector<string>& args) const
{
	if (IsAlive())
	{
		cout << name << "\n";
		cout << description << "\n";
	}
	else
	{
		cout << name << "'s corpse\n";
		cout << "Here lies dead: " << description << "\n";
	}
}

// ----------------------------------------------------
bool Creature::Go(const vector<string>& args)
{
	if (!IsAlive())
		return false;

	Exit* exit = GetRoom()->GetExit(args[1]);

	if (exit == NULL)
		return false;

	if (PlayerInRoom())
		cout << name << "goes " << args[1] << "...\n";

	ChangeParentTo(exit->GetDestinationFrom((Room*)parent));

	return true;
}

// ----------------------------------------------------
bool Creature::Take(const vector<string>& args)
{
	if (!IsAlive())
		return false;

	Item* item = (Item*)parent->Find(args[1], ITEM);

	if (args.size() > 1)
	{
		// we could pick something from a container in our inventory ...
		if (item == NULL)
			item = (Item*)Find(args[1], ITEM);

		if (item == NULL)
			return false;

		Item* subitem = (Item*)item->Find(args[3], ITEM);

		if (subitem == NULL)
			return false;

		if (PlayerInRoom())
			cout << name << " looks into " << item->name << "...\n";

		item = subitem;
	}

	if (item == NULL)
		return false;

	if (PlayerInRoom())
		cout << name << " takes " << item->name << ".\n";

	item->ChangeParentTo(this);

	return true;
}

// ----------------------------------------------------
void Creature::Inventory() const
{
	list<Entity*> items;
	FindAll(ITEM, items);

	if (items.size() == 0)
	{
		cout << name << " does not own any items\n";
		return;
	}

	cout << "\n" << name << " owns:\n";
	for (list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it)
	{
		cout << (*it)->name << "\n";
	}
}

// ----------------------------------------------------
bool Creature::UnLock(const vector<string>& args)
{
	if (!IsAlive())
		return false;

	Exit* exit = GetRoom()->GetExit(args[1]);

	if (exit == NULL || exit->locked == false)
		return false;

	Item* item = (Item*)Find(args[3], ITEM);

	if (item == NULL || exit->key != item)
		return false;

	if (PlayerInRoom())
		cout << "\n" << name << "unlocks " << exit->GetNameFrom((Room*)parent) << "...\n";

	exit->locked = false;

	return true;
}

// ----------------------------------------------------
bool Creature::Drop(const vector<string>& args)
{
	if (!IsAlive())
		return false;

	Item* item = (Item*)Find(args[1], ITEM);

	if (item == NULL)
		return false;

	if (PlayerInRoom())
		cout << name << " drops " << item->name << "...\n";

	item->ChangeParentTo(parent);

	return true;
}

// ----------------------------------------------------
Room* Creature::GetRoom() const
{
	return (Room*)parent;
}

// ----------------------------------------------------
bool Creature::PlayerInRoom() const
{
	return parent->Find(PLAYER) != NULL;
}

// ----------------------------------------------------
bool Creature::IsAlive() const
{
	return hit_points > 0;
}
/*
// ----------------------------------------------------
void Creature::Tick()
{
	if (combat_target != NULL)
	{
		if (parent->Find(combat_target) == true)
			MakeAttack();
		else
			combat_target = NULL;
	}
}
*/
// ----------------------------------------------------
void Creature::Die()
{
	if (PlayerInRoom())
		cout << name << " dies.\n";
}

// ----------------------------------------------------
bool Creature::Loot(const vector<string>& args)
{
	Creature *target = (Creature*)parent->Find(args[1], CREATURE);

	if (target == NULL && target->IsAlive() == false)
		return false;

	list<Entity*> items;
	target->FindAll(ITEM, items);

	for (list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it)
	{
		Item* i = (Item*)(*it);
		i->ChangeParentTo(this);
	}

	cout << "\n" << name << " loots " << target->name << "'s corpse\n";

	return true;
}