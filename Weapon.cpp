#include "Weapon.h"

Weapon::Weapon(double Weight, int Damage)
{
	this->Weight = Weight;
	this->Damage = Damage;
}

Weapon::~Weapon()
{
}

int Weapon::getDmg ()
{
	return Damage;
}

double Weapon::getWeight ()
{
	return Weight;
}

int Weapon::AtkDelay ()
{
	return Weight + Damage;
}

int Weapon::PoiseDmg ()
{
	return Weight * (Damage / 100);
}

int Weapon::EnergyConsumption ()
{
	return 10 + Weight;
}