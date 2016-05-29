//Work In Progress-------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "Armor.h"
#include "Character.h"
#include "Weapon.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

bool Fight (Character&, Character&);
void WarriorXAtk (Character&, Character&);

int main(int argc, char **argv)
{
	Weapon StraightSword (4.5, 210), GreatSword (9, 360), Halberd (8, 350), Ulumulu (6.66, 420);
	Armor KnightSet (28.5, 170, 20), ArtoriasSet (18, 140, 15), HavelSet (45, 500, 50), ThiefSet (12, 90, 10), OpPlzNerf (13.37, 666, 420);
	Weapon *wpn1 = 0, *wpn2 = 0;
	Armor *arm1 = 0, *arm2 = 0;
	if (argc < 5)
	{
		cout << "Wprowadz ponizsze argumenty programu i uruchom ponownie:\n"
			<< "- argument 1 - bron pierwszego wojownika\n"
			<< "- argument 2 - pancerz pierwszego wojownika\n"
			<< "- argument 3 - bron drugiego wojownika\n"
			<< "- argument 4 - pancerz drugiego wojownika\n";
		exit (0);
	}
	if (argv[1] == "StraightSword") *wpn1 = StraightSword;
	else if (argv[1] == "GreatSword") *wpn1 = GreatSword;
	else if (argv[1] == "Halberd") *wpn1 = Halberd;
	else if (argv[1] == "Ulumulu") *wpn1 = Ulumulu;
	if (argv[2] == "KnightSet") *arm1 = KnightSet;
	else if (argv[2] == "ArtoriasSet") *arm1 = ArtoriasSet;
	else if (argv[2] == "HavelSet") *arm1 = HavelSet;
	else if (argv[2] == "ThiefSet") *arm1 = ThiefSet;
	else if (argv[2] == "OpPlzNerf") *arm1 = OpPlzNerf;
	if (argv[3] == "StraightSword") *wpn2 = StraightSword;
	else if (argv[3] == "GreatSword") *wpn2 = GreatSword;
	else if (argv[3] == "Halberd") *wpn2 = Halberd;
	else if (argv[3] == "Ulumulu") *wpn2 = Ulumulu;
	if (argv[4] == "KnightSet") *arm2 = KnightSet;
	else if (argv[4] == "ArtoriasSet") *arm2 = ArtoriasSet;
	else if (argv[4] == "HavelSet") *arm2 = HavelSet;
	else if (argv[4] == "ThiefSet") *arm2 = ThiefSet;
	else if (argv[4] == "OpPlzNerf") *arm2 = OpPlzNerf;	//zasrany switch nie obsluguje stringow a chce aby argumenty jasno odzwierciedlaly wybor

	Character Warrior1 (arm1, wpn1), Warrior2 (arm2, wpn2);
	srand(time(NULL));
	Fight (Warrior1, Warrior2);
}

bool Fight (Character &Warrior1, Character &Warrior2)
{
	bool Winner = 0;
	Warrior1.Hp = Warrior1.BaseHp;
	Warrior2.Hp = Warrior2.BaseHp;
	Warrior1.Energy = Warrior1.BaseEnergy;
	Warrior2.Energy = Warrior2.BaseEnergy;
	while (Warrior1.Hp > 0 && Warrior2.Hp > 0)
	{
		if (Warrior1.Weapon1.AtkDelay() < Warrior2.Weapon1.AtkDelay())	//Warrior 1 atakuje pierwszy
		{
			if (!Warrior1.SkipRound)
			{
				WarriorXAtk (Warrior1, Warrior2);
			}
			if (Warrior2.Hp <= 0)
			{
				Winner = 0; break;
			}
			if (!Warrior2.SkipRound)
			{
				WarriorXAtk (Warrior2, Warrior1);
			}
			if (Warrior1.Hp <= 0)
			{
				Winner = 1; break;
			}
			Warrior1.Energy += 15;
			Warrior2.Energy += 15;
		}
		else if (Warrior2.Weapon1.AtkDelay() < Warrior1.Weapon1.AtkDelay())	//Warrior 2 atakuje pierwszy
		{
			if (!Warrior2.SkipRound)
			{
				WarriorXAtk (Warrior2, Warrior1);
			}
			if (Warrior1.Hp <= 0)
			{
				Winner = 0; break;
			}
			if (!Warrior1.SkipRound)
			{
				WarriorXAtk (Warrior1, Warrior2);
			}
			if (Warrior2.Hp <= 0)
			{
				Winner = 1; break;
			}
			Warrior1.Energy += 15;
			Warrior2.Energy += 15;
		}
	}
	return Winner;
}

void WarriorXAtk (Character &Warrior1, Character &Warrior2)
{
	Warrior1.SkipRound = false;		//na poczatku tury resetujemy SkipRound, poniewaz "decyzja", czy dana postac atakuje juz jest podjeta przez instrukcje warunkowa zawarta przed wykonaniem tej funkcji
	Warrior2.SkipRound = false;
	if (int randdodge = rand() % 100 >= Warrior2.BurdenPercent(Warrior2.Armor1, Warrior2.Weapon1) && Warrior2.Energy > 0)	//przypadek gdy Warrior 2 unika
	{
		Warrior1.Energy -= Warrior1.Weapon1.EnergyConsumption();
		Warrior2.Energy -= (Warrior2.BurdenPercent(Warrior2.Armor1, Warrior2.Weapon1) / 5);	//strata energii przy uniku zalezna od stopnia obciazenia
		if (Warrior1.Energy < 0) Warrior1.Energy = 0;
		if (Warrior2.Energy < 0) Warrior2.Energy = 0;
	}
	else if (Warrior2.Energy > 0)	//przypadek gdy Warrior 2 blokuje
	{
		if (int randblock = rand() % 100 < 80)	//blok sie udaje
		{
			Warrior1.Energy -= Warrior1.Weapon1.EnergyConsumption();
			Warrior2.Energy -= (10 + ((100 - Warrior2.Armor1.getPoise()) / 10));
			if (Warrior1.Energy < 0) Warrior1.Energy = 0;
			if (Warrior2.Energy < 0) Warrior2.Energy = 0;
		}
		else						//blok sie nie udaje, Warrior 2 zbiera baty
		{
			if (Warrior1.Weapon1.PoiseDmg() > Warrior2.Armor1.getPoise()) Warrior2.SkipRound = true;	//jesli Warrior 2 ma za mala stabilnosc, traci ture
			Warrior1.Energy -= Warrior1.Weapon1.EnergyConsumption();
			if (Warrior1.Energy < 0) Warrior1.Energy = 0;
			Warrior2.Hp -= Warrior1.DealDmg(Warrior2.Armor1, Warrior1.Weapon1);		//Warrior 2 zbiera dmg, ale nie traci energii, bo nie wykonal zadnej akcji
		}
	}
	else if (Warrior2.Energy <= 0)	//podobnie jak przy nieudanym bloku, ale tu Warrior 2 traci swoja kolejke
	{
		Warrior1.Energy -= Warrior1.Weapon1.EnergyConsumption();
		if (Warrior1.Energy < 0) Warrior1.Energy = 0;
		Warrior2.Hp -= Warrior1.DealDmg(Warrior2.Armor1, Warrior1.Weapon1);
		Warrior2.SkipRound = true;											//moge w zrezygnowac z mechaniki skipround zaleznie od tego jak to wyjdzie dalej ----------- dotad sie buduje kod jak na razie (29.05)
	}
}


/*void Fight (Character &Warrior1, Character &Warrior2)  ---stara wersja---
{
	Warrior1.Hp = Warrior1.BaseHp;
	Warrior2.Hp = Warrior2.BaseHp;
	Warrior1.Energy = Warrior1.BaseEnergy;
	Warrior2.Energy = Warrior2.BaseEnergy;
	while (Warrior1.Hp > 0 && Warrior2.Hp > 0)
	{
		if (Warrior1.Weapon1.AtkDelay() < Warrior2.Weapon1.AtkDelay())	//Warrior1 atakuje pierwszy
		{
			if (!Warrior1.SkipRound)
			{
				if (int randdodge = rand() % 100 >= Warrior2.BurdenPercent(Warrior2.Armor1, Warrior2.Weapon1) && Warrior2.Energy > 0)	//przypadek gdy Warrior 2 unika
				{
					Warrior1.Energy -= Warrior1.Weapon1.EnergyConsumption();
					Warrior2.Energy -= (Warrior2.BurdenPercent(Warrior2.Armor1, Warrior2.Weapon1) / 5);	//strata energii przy uniku zalezna od stopnia obciazenia
					if (Warrior1.Energy < 0) Warrior1.Energy = 0;
					if (Warrior2.Energy < 0) Warrior2.Energy = 0;
				}
				else if (Warrior2.Energy > 0)	//przypadek gdy Warrior 2 blokuje
				{
					if (int randblock = rand() % 100 < 80)	//blok sie udaje
					{
						Warrior1.Energy -= Warrior1.Weapon1.EnergyConsumption();
						Warrior2.Energy -= (10 + ((100 - Warrior2.Armor1.getPoise()) / 10));
						if (Warrior1.Energy < 0) Warrior1.Energy = 0;
						if (Warrior2.Energy < 0) Warrior2.Energy = 0;
					}
					else						//blok sie nie udaje, Warrior 2 zbiera baty
					{
						Warrior1.Energy -= Warrior1.Weapon1.EnergyConsumption();
						if (Warrior1.Energy < 0) Warrior1.Energy = 0;
						Warrior2.Hp -= Warrior1.DealDmg(Warrior2.Armor1, Warrior1.Weapon1);		//Warrior 2 zbiera dmg, ale nie traci energii, bo nie wykonal zadnej akcji
					}
				}
				else if (Warrior2.Energy <= 0)	//podobnie jak przy nieudanym bloku, ale tu Warrior 2 traci swoja kolejke
				{
					Warrior1.Energy -= Warrior1.Weapon1.EnergyConsumption();
					if (Warrior1.Energy < 0) Warrior1.Energy = 0;
					Warrior2.Hp -= Warrior1.DealDmg(Warrior2.Armor1, Warrior1.Weapon1);
					Warrior2.SkipRound = true;											//moge w zrezygnowac z mechaniki skipround zaleznie od tego jak to wyjdzie dalej ----------- dotad sie buduje kod jak na razie (29.05)
				}
				//-----teraz kolej na Wariora 2-----//

			}
		}
	}
}*/