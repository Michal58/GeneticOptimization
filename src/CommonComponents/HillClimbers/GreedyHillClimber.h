#pragma once
#include <random>
#include <numeric>
#include "../Randomizers/Mt19937Randomizer.h"
#include "../../OptimizationTemplates/Randomizer.h"
#include "../../OptimizationTemplates/Individual.h"
#include "../../OptimizationTemplates/GeneticOptimizer.h"

class GreedyHillClimber: public GeneticOptimizer
{
	static const int DEFAULT_COUNT_OF_SAME_INDIVIDUAL_OPTIMIZATIONS = 1;

	Individual* theBestIndividual;
	int countOfTheSameIndividualOptimizations;

	Individual* individualToOptimize;		// not to delete
	bool shouldMixOrderOfOptimization;
	std::vector<int> orderOfOptimization;

	bool isInitialized;

	void setDefaultOrderOfOptimization();
	void randomlyMixOptimizationOrder();
	void applyMutationAndUpdateTheBestGeneAndFitnessIfNewGeneIsImprovement(int geneIndex, int newGene, int& theBestGene, double& theBestFitness);
	void optimizeGeneAt(int index);
	void tryToUpdateTheBestIndividual();

public:

	static enum GeneticOptimizerTurnOff 
	{
		TURN_OFF_CONFIRMATION
	};

	GreedyHillClimber(OptimizationCase& caseToInitialize,bool shouldMixOrderOfOptimization, GeneticOptimizerTurnOff turnOffConfirmation);
	GreedyHillClimber(Individual& individualToOptimize, bool shouldMixOrderOfOptimization, GeneticOptimizerTurnOff turnOffConfirmation);
	GreedyHillClimber(Individual& individualToOptimize, bool shouldMixOrderOfOptimization);
	GreedyHillClimber(Individual& initialIndividual, bool shouldMixOrderOfOptimization, int countOfTheSameIndividualOptimizations);
	~GreedyHillClimber();

	void optimizeIndividual();
	void setIndividualToOptimize(Individual& individualToOptimize, bool shouldTryToUpdateTheBestIndividual);

	void reset() override;
	bool isReadyToSearch() override;
	void runIteration() override;
	Individual* peekTheBestIndividual() override;
	Individual* copyTheBestIndividual() override;
};

