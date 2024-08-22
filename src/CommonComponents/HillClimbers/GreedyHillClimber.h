#pragma once
#include <random>
#include <numeric>
#include "../Randomizers/Mt19937Randomizer.h"
#include "../../OptimazationTemplates/Randomizer.h"
#include "../../OptimazationTemplates/Individual.h"
#include "../../OptimazationTemplates/GeneticOptimizer.h"

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
	void updateTheBestGenAndFitnessIfNewGenIsImprovement(int genIndex, int newGen, int& theBestGen, double& theBestFitness);
	void optimizeGenAt(int index);
	void tryToUpdateTheBestIndividual();

public:

	static enum GeneticOptimizerTurnOff 
	{
		TURN_OFF_CONFIRMATION
	};

	GreedyHillClimber(OptimazationCase& caseToInitialize,bool shouldMixOrderOfOptimazation, GeneticOptimizerTurnOff turnOffConfirmation);
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

