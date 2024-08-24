#pragma once
#include <random>
#include <numeric>
#include "../Randomizers/Mt19937Randomizer.h"
#include "../../OptimizationTemplates/Randomizer.h"
#include "../../OptimizationTemplates/Individual.h"
#include "../../OptimizationTemplates/GeneticOptimizer.h"

class GreedyHillClimber: public GeneticOptimizer
{
	static const int DEFULT_COUNT_OF_SAME_INDIVIDUAL_OPTIMAZATIONS = 1;

	Individual* theBestIndividual;
	int countOfTheSameIndividualOptimazations;

	Individual* individualToOptimize;		// not to delete
	bool shouldMixOrderOfOptimazation;
	std::vector<int> orderOfOptimazation;

	bool isInitialized;

	void setDefalutOrderOfOptimazation();
	void randomlyMixOptimazationOrder();
	void applyMutationAndUpdateTheBestGeneAndFitnessIfNewGeneIsImprovement(int geneIndex, int newGene, int& theBestGene, double& theBestFitness);
	void optimizeGeneAt(int index);
	void tryToUpdateTheBestIndividual();

public:

	static enum GeneticOptimizerTurnOff 
	{
		TURN_OFF_CONFIRMATION
	};

	GreedyHillClimber(OptimizationCase& caseToInitialize,bool shouldMixOrderOfOptimazation, GeneticOptimizerTurnOff turnOffConfirmation);
	GreedyHillClimber(Individual& individualToOptimize, bool shouldMixOrderOfOptimazation, GeneticOptimizerTurnOff turnOffConfirmation);
	GreedyHillClimber(Individual& individualToOptimize, bool shouldMixOrderOfOptimazation);
	GreedyHillClimber(Individual& initialIndividual, bool shouldMixOrderOfOptimazation, int countOfTheSameIndividualOptimazations);
	~GreedyHillClimber();

	void optimizeIndividual();
	void setIndividualToOptimize(Individual& individualToOptimize, bool shouldTryToUpdateTheBestIndividual);

	void reset() override;
	bool isReadyToSearch() override;
	void runIteration() override;
	Individual* peekTheBestIndividual() override;
	Individual* copyTheBestIndividual() override;
};

