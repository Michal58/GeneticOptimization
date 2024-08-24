#pragma once
#include <iostream>
#include <vector>
#include "../OptimizationTemplates/OptimizationCase.h"
#include "../OptimizationTemplates/GeneticOptimizer.h"
#include "ClassicalIndividual.h"

#define GEN_OPTIMAZATION_CHANCE 0.001


class IterationCtirterium :public StopCriterium
{
	int maxIterationsCount;
	int countOfIterations;

public:

	IterationCtirterium(int maxIterationsCount);
	bool isLimitReached();
	void updateStance();
};

class GeneticAlgorithm: public GeneticOptimizer
{

public:

	static const int PAIR_SIZE = 2;

private:

	int populationSize;
	double crossoverChance;
	double genMutationChance;
	bool isInitialized;

	ClassicalIndividual** generation;

	ClassicalIndividual** nextGeneration;

	ClassicalIndividual* theBestSolution;				

	void swapGenerationsAddresses();
	void clearNextGeneration();

	void initializeGeneration();
	void conductCrossovers();
	void conductMutations();
	void ensureThatTheBestIndividualIsKept();
	void fillNextGeneration();
	PairOfIndividuals matchPairRandomly();

	PairOfIndividuals pairFromCrossoverAttempt();
	PairOfIndividuals createCrossoverChildren(ClassicalIndividual* parent1, ClassicalIndividual* parent2);


	ClassicalIndividual* copyTheBestSolutionInTheGeneration();

public:

	GeneticAlgorithm(int populationSize, double crossoverChance, double genMutationChance, OptimizationCase& standardEvaluator);
	~GeneticAlgorithm();

	void reset() override;

	bool isReadyToSearch() override;
	void runIteration() override;
	Individual* peekTheBestIndividual() override;
	Individual* copyTheBestIndividual() override;
};

