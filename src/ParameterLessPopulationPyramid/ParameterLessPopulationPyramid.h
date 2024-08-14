#pragma once
#include <unordered_set>
#include "../OptimazationTemplates/GeneticOptimizer.h"
#include "P3Individual.h"
#include "Pyramid.h"

class ParameterLessPopulationPyramid;
using P3 = ParameterLessPopulationPyramid;

class ParameterLessPopulationPyramid: public GeneticOptimizer
{
	GreedyHillClimber* commonGreedyOptimizer;
	Individual* theBestIndividual;
	Pyramid* populationPyramid;
	std::unordered_set<P3Individual*, HashGetterOfP3Individual, EqualityCheckerOfP3Individual>* allDistinctIndividualsSet;

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