#include "Character.h"

Character::Character(Armor *a, Weapon *b)
{
	this->Armor1 = *a;
	this->Weapon1 = *b;
}

Character::~Character()
{
}

double Character::BurdenPercent (Armor a, Weapon b)
{
	double EquipBurden = (a.getWeight() + b.getWeight()) / MaxBurden * 100;

	return EquipBurden;
}

int Character::DealDmg (Armor a, Weapon b)
{
	int DmgOutput = (double)b.getDmg() * (1 - a.ReduceDmgPercent());
	//std::cout << "obrazenia: " << DmgOutput << endl;
	return DmgOutput;
}

double Character::MaxBurden = 50;