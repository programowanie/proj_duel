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
	int *arg = new int[argc - 1];
	for (int i = 0; i < argc - 1; i++)
	{
		arg[i] = atoi(argv[i + 1]);
	}
	if (argc < 5)
	{
		cout << "Wprowadz ponizsze argumenty programu i uruchom ponownie:\n"
			<< "- argument 1 - bron pierwszego wojownika\n"
			<< "- argument 2 - pancerz pierwszego wojownika\n"
			<< "- argument 3 - bron drugiego wojownika\n"
			<< "- argument 4 - pancerz drugiego wojownika\n";
		exit (0);
	}
	if (arg[0] == 1) wpn1 = &StraightSword;
	else if (arg[0] == 2) wpn1 = &GreatSword;
	else if (arg[0] == 3) wpn1 = &Halberd;
	else if (arg[0] == 4) wpn1 = &Ulumulu;
	if (arg[1] == 1) arm1 = &KnightSet;
	else if (arg[1] == 2) arm1 = &ArtoriasSet;
	else if (arg[1] == 3) arm1 = &HavelSet;
	else if (arg[1] == 4) arm1 = &ThiefSet;
	else if (arg[1] == 5) arm1 = &OpPlzNerf;
	if (arg[2] == 1) wpn2 = &StraightSword;
	else if (arg[2] == 2) wpn2 = &GreatSword;
	else if (arg[2] == 3) wpn2 = &Halberd;
	else if (arg[2] == 4) wpn2 = &Ulumulu;
	if (arg[3] == 1) arm2 = &KnightSet;
	else if (arg[3] == 2) arm2 = &ArtoriasSet;
	else if (arg[3] == 3) arm2 = &HavelSet;
	else if (arg[3] == 4) arm2 = &ThiefSet;
	else if (arg[3] == 5) arm2 = &OpPlzNerf;

	Character Warrior1 (arm1, wpn1), Warrior2 (arm2, wpn2);
	srand(time(NULL));
	(Fight (Warrior1, Warrior2) == 0) ? (cout<<"Warrior 1 wygrywa pojedynek!\n------------------------------\n"): (cout<<"Warrior 2 wygrywa pojedynek!\n------------------------------");
	delete[] arg;
}

bool Fight (Character &Warrior1, Character &Warrior2)
{
	Warrior1 = Warrior1; //---
	Warrior2 = Warrior2; //---
	bool Winner = 0;
	Warrior1.Hp = Warrior1.BaseHp;
	Warrior2.Hp = Warrior2.BaseHp;
	Warrior1.Energy = Warrior1.BaseEnergy;
	Warrior2.Energy = Warrior2.BaseEnergy;
	while (Warrior1.Hp > 0 && Warrior2.Hp > 0)
	{
		if (Warrior1.Weapon1.AtkDelay() <= Warrior2.Weapon1.AtkDelay())	//Warrior 1 atakuje pierwszy
		{
			if (!Warrior1.SkipRound)
			{
				cout << "Warrior 1 atakuje.\n";
				Warrior2.SkipRound = 0;
				WarriorXAtk (Warrior1, Warrior2);
			}
			if (Warrior2.Hp <= 0)
			{
				cout << "Warrior 2 ginie\n";
				Winner = 0; break;
			}
			if (!Warrior2.SkipRound)
			{
				cout << "Warrior 2 atakuje.\n";
				Warrior1.SkipRound = 0;
				WarriorXAtk (Warrior2, Warrior1);
			}
			if (Warrior1.Hp <= 0)
			{
				cout << "Warrior 1 ginie\n";
				Winner = 1; break;
			}
			Warrior1.Energy += 15;
			Warrior2.Energy += 15;
		}
		else if (Warrior2.Weapon1.AtkDelay() < Warrior1.Weapon1.AtkDelay())	//Warrior 2 atakuje pierwszy
		{
			if (!Warrior2.SkipRound)
			{
				cout << "Warrior 2 atakuje.\n";
				Warrior1.SkipRound = 0;
				WarriorXAtk (Warrior2, Warrior1);
			}
			if (Warrior1.Hp <= 0)
			{
				cout << "Warrior 1 ginie\n";
				Winner = 1; break;
			}
			if (!Warrior1.SkipRound)
			{
				cout << "Warrior 1 atakuje.\n";
				Warrior2.SkipRound = 0;
				WarriorXAtk (Warrior1, Warrior2);
			}
			if (Warrior2.Hp <= 0)
			{
				cout << "Warrior 2 ginie\n";
				Winner = 0; break;
			}
			Warrior1.Energy += 15;
			Warrior2.Energy += 15;
			if (Warrior1.Energy > Warrior1.BaseEnergy) Warrior1.Energy = Warrior1.BaseEnergy;
			if (Warrior2.Energy > Warrior2.BaseEnergy) Warrior2.Energy = Warrior2.BaseEnergy;
		}
	}
	if (Warrior1.Hp <= 0) Winner = 1;
	else if (Warrior2.Hp <= 0) Winner = 0;
	return Winner;
}

void WarriorXAtk (Character &Warrior1, Character &Warrior2)
{
	Warrior1 = Warrior1; //---
	Warrior2 = Warrior2; //---

	if (int randdodge = rand() % 100 >= Warrior2.BurdenPercent(Warrior2.Armor1, Warrior2.Weapon1) && Warrior2.Energy > 0)	//przypadek gdy Warrior 2 unika
	{
		Warrior1.Energy -= Warrior1.Weapon1.EnergyConsumption();
		Warrior2.Energy -= (Warrior2.BurdenPercent(Warrior2.Armor1, Warrior2.Weapon1) / 5);	//strata energii przy uniku zalezna od stopnia obciazenia
		if (Warrior1.Energy < 0) Warrior1.Energy = 0;
		if (Warrior2.Energy < 0) Warrior2.Energy = 0;
		cout << "Unik.\n" << "Energia atakujacego: " << Warrior1.Energy << "\nEnergia broniacego sie: " << Warrior2.Energy << "\n\n";
	}
	else if (Warrior2.Energy > 0)	//przypadek gdy Warrior 2 blokuje
	{
		if (int randblock = rand() % 100 < 70)	//blok sie udaje
		{
			Warrior1.Energy -= Warrior1.Weapon1.EnergyConsumption();
			Warrior2.Energy -= (10 + ((100 - Warrior2.Armor1.getPoise()) / 10));
			if (Warrior1.Energy < 0) Warrior1.Energy = 0;
			if (Warrior2.Energy < 0) Warrior2.Energy = 0;
			cout << "Blok.\n" << "Energia atakujacego: " << Warrior1.Energy << "\nEnergia broniacego sie: " << Warrior2.Energy << "\n\n";
		}
		else						//blok sie nie udaje, Warrior 2 zbiera baty
		{
			if (Warrior1.Weapon1.PoiseDmg() > Warrior2.Armor1.getPoise()) 
			{ 
				Warrior2.SkipRound = true; 
				cout << "Broniacy sie traci  kolejke.\n";
			}	//jesli Warrior 2 ma za mala stabilnosc, traci ture
			Warrior1.Energy -= Warrior1.Weapon1.EnergyConsumption();
			if (Warrior1.Energy < 0) Warrior1.Energy = 0;
			Warrior2.Hp -= Warrior1.DealDmg(Warrior2.Armor1, Warrior1.Weapon1);		//Warrior 2 zbiera dmg, ale nie traci energii, bo nie wykonal zadnej akcji
			cout << "Udany atak.\n" << "Energia atakujacego: " << Warrior1.Energy << "\nEnergia broniacego sie: " << Warrior2.Energy << "\nHP broniacego sie: " << Warrior2.Hp << "\n\n";
		}
	}
	else if (Warrior2.Energy <= 0)	//podobnie jak przy nieudanym bloku, ale tu Warrior 2 traci swoja kolejke
	{
		Warrior1.Energy -= Warrior1.Weapon1.EnergyConsumption();
		if (Warrior1.Energy < 0) Warrior1.Energy = 0;
		Warrior2.Hp -= Warrior1.DealDmg(Warrior2.Armor1, Warrior1.Weapon1);
		Warrior2.SkipRound = true;
		cout << "Broniacy sie traci  kolejke.\n";
		cout << "Udany atak.\n" << "Energia atakujacego: " << Warrior1.Energy << "\nEnergia broniacego sie: " << Warrior2.Energy << "\nHP broniacego sie: " << Warrior2.Hp << "\n\n";
	}
}