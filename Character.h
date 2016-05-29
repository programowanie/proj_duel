#pragma once
#include "Armor.h"
#include "Weapon.h"
class Character
{
	//static const int BaseHp = 1000, BaseEnergy = 100;
	//int	Hp, Energy;
	static double MaxBurden;
public:
	Character(Armor *a, Weapon *b);	//konstruktor przyjmujacy wskazniki na obiekty klas Armor i Weapon
	Character() {};
	~Character();
	double BurdenPercent (Armor a, Weapon b);
	int DealDmg (Armor a, Weapon b);
	Weapon Weapon1;
	Armor Armor1;
	static const int BaseHp = 1000, BaseEnergy = 100;
	int	Hp, Energy;
	bool SkipRound = false;
};