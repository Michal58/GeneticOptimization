#pragma once
#include "../OptimazationTemplates/Individual.h"
#include "../CommonComponents/Functionalities/Functionalities.h"

class PopulationLevel
{
	const static int DEFAULT_POPULATION_SIZE = 1;
	std::vector<P3Individual*> population;

	void deleteIndividualsFromPopulation();

public:

	~PopulationLevel();
	void addIndividual(P3Individual* newIndividual);
};

