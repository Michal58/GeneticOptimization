#include "Mt19937Randomizer.h"

Mt19937Randomizer* const Mt19937Randomizer::RANDOMIZER_SINGLETON_INSTANCE = new Mt19937Randomizer();

Mt19937Randomizer::Mt19937Randomizer():randomizer(randomBase()) {}

Mt19937Randomizer* Mt19937Randomizer::getSingletonInstance()
{
	return RANDOMIZER_SINGLETON_INSTANCE;
}

void Mt19937Randomizer::reset()
{
	randomizer.seed(randomBase());
}

int Mt19937Randomizer::randInRange(int inclusiveLowerBound, int exclusiveRange)
{
	std::uniform_int_distribution<> uniformDistributionGenerator(inclusiveLowerBound, exclusiveRange - 1);
	return uniformDistributionGenerator(randomizer);
}

int Mt19937Randomizer::randInRange(int exclusiveRange)
{
	std::uniform_int_distribution<> uniformDistributionGenerator(0, exclusiveRange - 1);
	return uniformDistributionGenerator(randomizer);
}

double Mt19937Randomizer::chanceRand()
{
	std::uniform_real_distribution<> uniformDistributionGenerator(0, 1);
	return uniformDistributionGenerator(randomizer);
}
