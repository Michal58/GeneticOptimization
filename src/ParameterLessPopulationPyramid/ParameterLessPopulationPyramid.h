#pragma once
#include <unordered_set>
#include "../CommonComponents/Hashing/PointerBaseHasher.h"
#include "../OptimazationTemplates/GeneticOptimizer.h"
#include "P3Individual.h"
#include "Pyramid.h"

class ParameterLessPopulationPyramid;
using P3 = ParameterLessPopulationPyramid;

using IndividualsHashSet = std::unordered_set<P3Individual*, PointerBaseHasher<P3Individual>, PointerBaseHashablesComparator<P3Individual>>;

class ParameterLessPopulationPyramid: public GeneticOptimizer
{
	GreedyHillClimber* commonGreedyOptimizer;
	Individual* theBestIndividual;
	Pyramid* populationPyramid;
	IndividualsHashSet* allDistinctIndividualsSet;

	bool isInitialized;

	void decideAboutUpadingPyramidWithIndividual(P3Individual& potentiallyDistinctIndividual, int potentialPyramidLevelToUpdate);

public:

	ParameterLessPopulationPyramid(OptimazationCase& caseInstance);
	~ParameterLessPopulationPyramid();

	bool isIndividualDistinct(P3Individual& possibleDistinctIndividual);
	void mixSolutionWithPopulation(P3Individual& solution, PopulationLevel& population);

	void reset() override;
	bool isReadyToSearch() override;
	void runIteration() override;
	Individual* peekTheBestIndividual() override;
	Individual* copyTheBestIndividual() override;
};