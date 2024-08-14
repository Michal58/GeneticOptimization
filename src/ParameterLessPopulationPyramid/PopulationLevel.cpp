#include "PopulationLevel.h"

void PopulationLevel::deleteIndividualsFromPopulation()
{
	clearVectorOfPointers(population);
}

PopulationLevel::~PopulationLevel()
{
	deleteIndividualsFromPopulation();
}

void PopulationLevel::addIndividual(P3Individual* newIndividual)
{
	population.push_back(newIndividual);
}
