#include "Armor.h"

Armor::Armor(double Weight, int Protection, int Poise)
{
	this->Weight = Weight;
	this->Protection = Protection;
	this->Poise = Poise;
}

Armor::~Armor()
{
}

double Armor::ReduceDmgPercent ()	//max protection to 600, przy wiekszej wartosci zbroja zaczyna leczyc wlasciciela, nawet ponad max hp
{
	return (double)Protection / 6 / 100;	//np przy 60 protection pancerz bedzie zbijal 60/6 -> 10% obrazen
}

double Armor::getWeight ()
{
	return Weight;
}

int Armor::getPoise ()
{
	return Poise;
}
