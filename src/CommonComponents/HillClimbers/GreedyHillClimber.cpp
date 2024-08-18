#include "GreedyHillClimber.h"

void GreedyHillClimber::setDefalutOrderOfOptimazation()
{
	std::iota(orderOfOptimazation.begin(), orderOfOptimazation.end(), 0);
}

void GreedyHillClimber::randomlyMixOptimazationOrder()
{
	std::shuffle(orderOfOptimazation.begin(), orderOfOptimazation.end(), *Mt19937Randomizer::getSingletonInstance());
}

void GreedyHillClimber::updateTheBestGenAndFitnessIfNewGenIsImprovement(int genIndex, int newGen, int& theBestGen, double& theBestFitness)
{
	individualToOptimize->mutateGen(genIndex, newGen);
	double newFitness = individualToOptimize->evaluateFitness();

	bool isNewGenImprovement = newFitness > theBestFitness;
	if (isNewGenImprovement)
	{
		theBestGen = newGen;
		theBestFitness = newFitness;
	}
}

void GreedyHillClimber::optimizeGenAt(int index)
{
	std::unique_ptr<DomainIterator> genDomain = individualToOptimize->getDomain(index);

	int originalGen= individualToOptimize->getGenAt(index);
	int theBestGen = originalGen;
	double theBestFitness = individualToOptimize->evaluateFitness();

	while (genDomain->hasNext())
	{
		int possibleGenImporvement = genDomain->next();
		updateTheBestGenAndFitnessIfNewGenIsImprovement(index, possibleGenImporvement, theBestGen, theBestFitness);
	}

	individualToOptimize->mutateGen(index, theBestGen);
	individualToOptimize->forcelyMemoizeFitness(theBestFitness);
}

void GreedyHillClimber::updateTheBestIndividualIfNeeded()
{
	if (individualToOptimize->evaluateFitness() > theBestIndividual->evaluateFitness())
	{
		delete theBestIndividual;
		theBestIndividual = individualToOptimize->clone();
	}
}

GreedyHillClimber::GreedyHillClimber(OptimazationCase& caseToInitialize,bool shouldMixOrderOfOptimazation, GeneralOptimizerTurnOff turnOffConfirmation):
	GeneticOptimizer(caseToInitialize),
	individualToOptimize(nullptr),
	shouldMixOrderOfOptimazation(shouldMixOrderOfOptimazation),
	orderOfOptimazation(caseToInitialize.getCountOfDimensions()),
	countOfSameIndividualOptimazations(DEFULT_COUNT_OF_SAME_INDIVIDUAL_OPTIMAZATIONS)
{
	setDefalutOrderOfOptimazation();
	theBestIndividual = nullptr;
}

GreedyHillClimber::GreedyHillClimber(Individual& individualToOptimize, bool shouldMixOrderOfOptimazation, GeneralOptimizerTurnOff turnOffConfirmation):
	GeneticOptimizer(individualToOptimize.getOptimazationCase()),
	individualToOptimize(&individualToOptimize),
	shouldMixOrderOfOptimazation(shouldMixOrderOfOptimazation),
	orderOfOptimazation(individualToOptimize.getSizeOfGenotype()),
	countOfSameIndividualOptimazations(DEFULT_COUNT_OF_SAME_INDIVIDUAL_OPTIMAZATIONS)
{
	setDefalutOrderOfOptimazation();
	theBestIndividual = nullptr;
}

GreedyHillClimber::GreedyHillClimber(Individual& individualToOptimize, bool shouldMixOrderOfOptimazation) :
	GreedyHillClimber(individualToOptimize, shouldMixOrderOfOptimazation, GeneralOptimizerTurnOff::CONFIRMATION)
{
	individualToOptimize.evaluateFitness();
	theBestIndividual = individualToOptimize.clone();
}

GreedyHillClimber::GreedyHillClimber(Individual& initialIndividual, bool shouldMixOrderOfOptimazation, int countOfSameIndividualOptimazations):
	GreedyHillClimber(initialIndividual,shouldMixOrderOfOptimazation) 
{
	this->countOfSameIndividualOptimazations = countOfSameIndividualOptimazations;
}

GreedyHillClimber::~GreedyHillClimber()
{
	delete theBestIndividual;
}

void GreedyHillClimber::optimizeIndividual()
{
	if (shouldMixOrderOfOptimazation)
		randomlyMixOptimazationOrder();

	for (int indexAssociatedWithGenToOptimize : orderOfOptimazation)
		optimizeGenAt(indexAssociatedWithGenToOptimize);
}

void GreedyHillClimber::setIndividualToOptimize(Individual& individualToOptimize, bool shouldUpdateTheBestIndividualInWholeOptimazationProcess)
{
	this->individualToOptimize = &individualToOptimize;
	if (orderOfOptimazation.size() != individualToOptimize.getSizeOfGenotype())
		setDefalutOrderOfOptimazation();
	if (shouldUpdateTheBestIndividualInWholeOptimazationProcess)
		updateTheBestIndividualIfNeeded();
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
	for (int i = 0; i < countOfSameIndividualOptimazations; i++)
		optimizeIndividual();
	
	updateTheBestIndividualIfNeeded();
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
