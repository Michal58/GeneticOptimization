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

	void ifIndividualIsDistinctAddItToPopulationAtDepthAndUpdateSetOfDistinctIndividuals(P3Individual& potentiallyDistinctIndividual, int depth);
	void addSolutionAfterCrossoverToPopulationIfItIsNotWorse(P3Individual* solutionAfterCrossover, double previousEvaluation, int crossoverLevel);

public:

	ParameterLessPopulationPyramid(OptimazationCase& caseInstance);
	~ParameterLessPopulationPyramid();

	bool isIndividualDistinct(P3Individual& possibleDistinctIndividual);
	void performCrossoverInPopulation(P3Individual& individualForCrossover, PopulationLevel& populationForCrossover);

	void reset() override;
	bool isReadyToSearch() override;
	void runIteration() override;
	Individual* peekTheBestIndividual() override;
	Individual* copyTheBestIndividual() override;
};