#include "GreedyHillClimber.h"

void GreedyHillClimber::setDefaultOrderOfOptimization()
{
	std::iota(orderOfOptimization.begin(), orderOfOptimization.end(), 0);
}

void GreedyHillClimber::randomlyMixOptimizationOrder()
{
	std::shuffle(orderOfOptimization.begin(), orderOfOptimization.end(), *Mt19937Randomizer::getSingletonInstance());
}

void GreedyHillClimber::applyMutationAndUpdateTheBestGeneAndFitnessIfNewGeneIsImprovement(int genIndex, int newGen, int& theBestGen, double& theBestFitness)
{
	individualToOptimize->mutateGene(genIndex, newGen);
	double newFitness = individualToOptimize->evaluateFitness();

	bool isNewGenImprovement = newFitness > theBestFitness;
	if (isNewGenImprovement)
	{
		theBestGen = newGen;
		theBestFitness = newFitness;
	}
}

void GreedyHillClimber::optimizeGeneAt(int index)
{
	std::unique_ptr<DomainIterator> geneDomain = individualToOptimize->getDomain(index);

	int originalGene= individualToOptimize->getGeneAt(index);
	int theBestGen = originalGene;
	double theBestFitness = individualToOptimize->evaluateFitness();

	while (geneDomain->hasNext())
	{
		int possibleGeneImprovement = geneDomain->next();
		applyMutationAndUpdateTheBestGeneAndFitnessIfNewGeneIsImprovement(index, possibleGeneImprovement, theBestGen, theBestFitness);
	}

	individualToOptimize->mutateGene(index, theBestGen);
	individualToOptimize->forcefullyMemoizeFitness(theBestFitness);
}

void GreedyHillClimber::tryToUpdateTheBestIndividual()
{
	if (theBestIndividual == nullptr || individualToOptimize->evaluateFitness() > theBestIndividual->evaluateFitness())
	{
		delete theBestIndividual;
		theBestIndividual = individualToOptimize->clone();
	}
}

GreedyHillClimber::GreedyHillClimber(OptimizationCase& caseToInitialize,bool shouldMixOrderOfOptimization, GeneticOptimizerTurnOff turnOffConfirmation):
	GeneticOptimizer(caseToInitialize),
	individualToOptimize(nullptr),
	shouldMixOrderOfOptimization(shouldMixOrderOfOptimization),
	orderOfOptimization(caseToInitialize.getCountOfDimensions()),
	countOfTheSameIndividualOptimizations(DEFAULT_COUNT_OF_SAME_INDIVIDUAL_OPTIMIZATIONS)
{
	setDefaultOrderOfOptimization();
	theBestIndividual = nullptr;
}

GreedyHillClimber::GreedyHillClimber(Individual& individualToOptimize, bool shouldMixOrderOfOptimization, GeneticOptimizerTurnOff turnOffConfirmation):
	GeneticOptimizer(individualToOptimize.getOptimizationCase()),
	individualToOptimize(&individualToOptimize),
	shouldMixOrderOfOptimization(shouldMixOrderOfOptimization),
	orderOfOptimization(individualToOptimize.getSizeOfGenotype()),
	countOfTheSameIndividualOptimizations(DEFAULT_COUNT_OF_SAME_INDIVIDUAL_OPTIMIZATIONS)
{
	setDefaultOrderOfOptimization();
	theBestIndividual = nullptr;
}

GreedyHillClimber::GreedyHillClimber(Individual& individualToOptimize, bool shouldMixOrderOfOptimization) :
	GreedyHillClimber(individualToOptimize, shouldMixOrderOfOptimization, GeneticOptimizerTurnOff::TURN_OFF_CONFIRMATION)
{
	individualToOptimize.evaluateFitness();
	theBestIndividual = individualToOptimize.clone();
}

GreedyHillClimber::GreedyHillClimber(Individual& initialIndividual, bool shouldMixOrderOfOptimization, int countOfTheSameIndividualOptimizations):
	GreedyHillClimber(initialIndividual,shouldMixOrderOfOptimization) 
{
	this->countOfTheSameIndividualOptimizations = countOfTheSameIndividualOptimizations;
}

GreedyHillClimber::~GreedyHillClimber()
{
	delete theBestIndividual;
}

void GreedyHillClimber::optimizeIndividual()
{
	if (shouldMixOrderOfOptimization)
		randomlyMixOptimizationOrder();

	for (int indexAssociatedWithGenToOptimize : orderOfOptimization)
		optimizeGeneAt(indexAssociatedWithGenToOptimize);
}

void GreedyHillClimber::setIndividualToOptimize(Individual& individualToOptimize, bool shouldTryToUpdateTheBestIndividual)
{
	this->individualToOptimize = &individualToOptimize;
	if (orderOfOptimization.size() != individualToOptimize.getSizeOfGenotype())
		setDefaultOrderOfOptimization();
	if (shouldTryToUpdateTheBestIndividual)
		tryToUpdateTheBestIndividual();
}

void GreedyHillClimber::reset()
{
	individualToOptimize->fillAllGensRandomly(*Mt19937Randomizer::getSingletonInstance());
	theBestIndividual = individualToOptimize->clone();
	individualToOptimize->evaluateFitness();
}

bool GreedyHillClimber::isReadyToSearch()
{
	return true;
}

void GreedyHillClimber::runIteration()
{
	for (int i = 0; i < countOfTheSameIndividualOptimizations; i++)
		optimizeIndividual();
	
	tryToUpdateTheBestIndividual();
	individualToOptimize->fillAllGensRandomly(*Mt19937Randomizer::getSingletonInstance());
}

Individual* GreedyHillClimber::peekTheBestIndividual()
{
	return theBestIndividual;
}

Individual* GreedyHillClimber::copyTheBestIndividual()
{
	return theBestIndividual->clone();
}
