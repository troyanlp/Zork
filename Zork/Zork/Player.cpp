
#include "Player.h"


// ----------------------------------------------------
Player::Player(const char* title, const char* description, Room* room) : 
	Creature(title, description, room)
{
	type = PLAYER;
}

// ----------------------------------------------------
Player::~Player()
{
}

// ----------------------------------------------------
void Player::Look(const vector<string>& args) const
{
	if (args.size() > 1)
	{
		for (list<Entity*>::const_iterator it = parent->container.begin(); it != parent->container.cend(); ++it)
		{
			if (Same((*it)->name, args[1]) || ((*it)->type == EXIT && Same(args[1], ((Exit*)(*it))->GetNameFrom((Room*)parent))))
			{
				(*it)->Look();
				return;
			}
		}

		if (Same(args[1], "me"))
		{
			cout << "\n" << name << "\n";
			cout << description << "\n";
		}
	}
	else
	{
		parent->Look();
	}
}

// ----------------------------------------------------
bool Player::Go(const vector<string>& args)
{
	Exit* exit = GetRoom()->GetExit(args[1]);

	if (exit == NULL)
	{
		cout << "\nThere is no exit at '" << args[1] << "'.\n";
		return false;
	}

	if (exit->locked)
	{
		cout << "\nThat exit is locked.\n";
		return false;
	}

	cout << "\nYou take direction " << exit->GetNameFrom((Room*)parent) << "...\n";
	ChangeParentTo(exit->GetDestinationFrom((Room*)parent));
	parent->Look();

	return true;
}

// ----------------------------------------------------
bool Player::Take(const vector<string>& args)
{
	if (args.size() == 4)
	{
		Item* item = (Item*)parent->Find(args[3], ITEM);

		// we could pick something from a container in our inventory ...
		if (item == NULL)
			item = (Item*)Find(args[3], ITEM);

		if (item == NULL)
		{
			cout << "\nCannot find '" << args[3] << "' in this room or in your inventory.\n";
			return false;
		}

		Item* subitem = (Item*)item->Find(args[1], ITEM);

		if (subitem == NULL)
		{
			cout << "\n" << item->name << " does not contain '" << args[1] << "'.\n";
			return false;
		}

		cout << "\nYou take " << subitem->name << " from " << item->name << ".\n";
		subitem->ChangeParentTo(this);
	}
	else if (args.size() == 2)
	{
		Item* item = (Item*)parent->Find(args[1], ITEM);

		if (item == NULL)
		{
			cout << "\nThere is no item here with that name.\n";
			return false;
		}

		cout << "\nYou take " << item->name << ".\n";
		item->ChangeParentTo(this);
	}

	return false;
}

// ----------------------------------------------------
bool Player::Drop(const vector<string>& args)
{
	if (args.size() == 2)
	{
		Item* item = (Item*)Find(args[1], ITEM);

		if (item == NULL)
		{
			cout << "\nThere is no item on you with that name.\n";
			return false;
		}

		cout << "\nYou drop " << item->name << "...\n";
		item->ChangeParentTo(parent);

		return true;
	}
	else if (args.size() == 4)
	{
		Item* item = (Item*)Find(args[1], ITEM);

		if (item == NULL)
		{
			cout << "\nCan not find '" << args[1] << "' in your inventory.\n";
			return false;
		}

		Item* container = (Item*)parent->Find(args[3], ITEM);

		if (container == NULL)
		{
			container = (Item*)Find(args[3], ITEM);
			cout << "\nCan not find '" << args[3] << "' in your inventory or in the room.\n";
			return false;
		}

		cout << "\nYou put " << item->name << " into " << container->name << ".\n";
		item->ChangeParentTo(container);

		return true;
	}

	return false;
}

// ----------------------------------------------------
void Player::Inventory() const
{
	list<Entity*> items;
	FindAll(ITEM, items);

	if (items.size() == 0)
	{
		cout << "\nYou do not own any item.\n";
		return;
	}

	for (list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it)
	{
		if (*it == weapon)
			cout << "\n" << (*it)->name << " (as weapon)";
		else if (*it == armour)
			cout << "\n" << (*it)->name << " (as armour)";
		else
			cout << "\n" << (*it)->name;
	}

	cout << "\n";
}

// ----------------------------------------------------
bool Player::UnLock(const vector<string>& args)
{
	if (!IsAlive())
		return false;

	Exit* exit = GetRoom()->GetExit(args[1]);

	if (exit == NULL)
	{
		cout << "\nThere is no exit at '" << args[1] << "'.\n";
		return false;
	}

	if (exit->locked == false)
	{
		cout << "\nThat exit is not locked.\n";
		return false;
	}

	Item* item = (Item*)Find(args[3], ITEM);

	if (item == NULL)
	{
		cout << "\nKey '" << args[3] << "' not found in your inventory.\n";
		return false;
	}

	if (exit->key != item)
	{
		cout << "\nKey '" << item->name << "' is not the key for " << exit->GetNameFrom((Room*)parent) << ".\n";
		return false;
	}

	cout << "\nYou unlock " << exit->GetNameFrom((Room*)parent) << "...\n";

	exit->locked = false;

	item->~Item();

	return true;
}