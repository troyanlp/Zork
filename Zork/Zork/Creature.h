#pragma once
#include <string>
#include <vector>
#include "Entity.h"

class Room;
class Item;

using namespace std;

class Creature : public Entity
{
public:
	Creature(const char* name, const char* description, Room* room);
	~Creature();

	virtual bool Go(const vector<string>& args);
	virtual void Look(const vector<string>& args) const;
	virtual bool Take(const vector<string>& args);
	virtual bool Drop(const vector<string>& args);
	virtual void Inventory() const;
	virtual bool UnLock(const vector<string>& args);
	//virtual void Tick();
	virtual void Die();
	virtual bool Loot(const vector<string>& args);

	Room* GetRoom() const;
	bool PlayerInRoom() const;
	bool IsAlive() const;

public:

	int hit_points;
	int min_damage;
	int max_damage;
	int min_protection;
	int max_protection;
};