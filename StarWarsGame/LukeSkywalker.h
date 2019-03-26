#pragma once
#include "Character.h"
class LukeSkywalker :
	public Character
{
public:
	LukeSkywalker();

public:
	// getters
	int getHealth() { return health; }
	//setters
	void setHealth(int health) { this->health = health; }
private:
	int health;
};