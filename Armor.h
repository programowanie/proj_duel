#pragma once
class Armor
{
	double Weight;
	int Protection, Poise;
public:
	Armor(double Weight, int Protection, int Poise);
	Armor() {};
	~Armor();
	double ReduceDmgPercent ();
	double getWeight ();
	int getPoise ();
};