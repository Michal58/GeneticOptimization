#pragma once

#include <random>
#include <iostream>
#include "../OptimazationTemplates/Randomizer.h"

class Mt19937Randomizer:public Randomizer
{
	std::random_device randomBase;
	std::mt19937 randomizer;
	static Mt19937Randomizer* const RANDOMIZER_SINGLETON_INSTANCE;

public:

	Mt19937Randomizer();
	static Mt19937Randomizer* getSingletonInstance();
	void reset() override;
	int randInRange(int inclusiveLowerBound, int exclusiveRange) override;
	int randInRange(int exclusiveRange) override;
	double chanceRand() override;
};
