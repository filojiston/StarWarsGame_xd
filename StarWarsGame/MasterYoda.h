#pragma once
#include "Character.h"
class MasterYoda :
	public Character
{
public:
	MasterYoda();
public:
	// getters
	int getHealth() { return this->health; }
	// setters
	void setHealth(int health) { this->health = health; }

private:
	int health;
};