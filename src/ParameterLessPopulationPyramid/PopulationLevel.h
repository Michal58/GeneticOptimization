#pragma once
#include "../OptimazationTemplates/Individual.h"
#include "../CommonComponents/Functionalities/Functionalities.h"
#include "P3Individual.h"
#include "GenesFrequenciesLookup.h"

class PopulationLevel
{
	const static int DEFAULT_POPULATION_SIZE = 1;

	std::vector<P3Individual*> population;
	GenesFrequenciesLookup populationGenesFrequenciesLookup;

	bool areClustersUpToDate;

	void deleteIndividualsFromPopulation();

public:

	PopulationLevel();
	~PopulationLevel();
	void addIndividual(P3Individual* newIndividual);
};

