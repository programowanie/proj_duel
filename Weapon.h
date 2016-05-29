#pragma once
#include "Armor.h"
class Weapon
{
	double Weight;
	int Damage;
public:
	Weapon(double Weight, int Damage);
	Weapon() {};
	~Weapon();

	int getDmg ();
	double getWeight ();
	int AtkDelay ();
	int PoiseDmg ();
	int EnergyConsumption();
};