#include "PopulationLevel.h"

void PopulationLevel::deleteIndividualsFromPopulation()
{
	clearVectorOfPointers(population);
}

PopulationLevel::PopulationLevel():
	areClustersUpToDate(false) {}

PopulationLevel::~PopulationLevel()
{
	deleteIndividualsFromPopulation();
}

void PopulationLevel::addIndividual(P3Individual* newIndividual)
{
	populationGenesFrequenciesLookup.updateWithIndividual(*newIndividual);
	population.push_back(newIndividual);
}
