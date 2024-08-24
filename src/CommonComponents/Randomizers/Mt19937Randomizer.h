#pragma once

#include <random>
#include <iostream>
#include "../../OptimizationTemplates/Randomizer.h"
#undef min
#undef max

class Mt19937Randomizer:public Randomizer
{
	std::random_device randomBase;
	std::mt19937 randomizer;
	static Mt19937Randomizer* const RANDOMIZER_SINGLETON_INSTANCE;

public:

	typedef std::mt19937::result_type result_type;

	Mt19937Randomizer();
	static Mt19937Randomizer* getSingletonInstance();
	static result_type min();
	static result_type max();
	result_type operator()();
	void reset() override;
	int randInRange(int inclusiveLowerBound, int exclusiveRange) override;
	int randInRange(int exclusiveRange) override;
	double chanceRand() override;
};
