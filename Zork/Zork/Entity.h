#pragma once
#include <string>
#include <list>

using namespace std;

enum EntityType
{
	ENTITY,
	ROOM,
	EXIT,
	ITEM,
	CREATURE,
	PLAYER
};

class Entity
{
public:
	Entity(const char* name, const char* description, Entity* parent);
	virtual ~Entity();

	virtual void Look() const;
	virtual void Tick();

	void	ChangeParentTo(Entity* new_parent);
	bool    Find(Entity* entity) const;
	Entity* Find(EntityType type) const;
	Entity* Find(const string& name, EntityType type) const;
	void	FindAll(EntityType type, list<Entity*>& list_to_fill) const;
	virtual void Read() const;

public:
	EntityType type;
	string name;
	string description;
	int weight;

	Entity* parent;
	list<Entity*> container;
};