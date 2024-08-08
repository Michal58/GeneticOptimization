#include "GeneticAlgorithm.h"

IterationCtirterium::IterationCtirterium(int maxIterationsCount)
{
	this->maxIterationsCount = maxIterationsCount;
	countOfIterations = 0;
}

bool IterationCtirterium::isLimitReached()
{
	return countOfIterations >= maxIterationsCount;
}

void IterationCtirterium::updateStance()
{
	countOfIterations++;
}

void GeneticAlgorithm::swapGenerationsAddresses()
{
	ClassicalIndividual** aux = generation;
	generation = nextGeneration;
	nextGeneration = aux;
}

void GeneticAlgorithm::clearNextGeneration()
{
	for (int i = 0; i < populationSize; i++)
		delete nextGeneration[i];
}

void GeneticAlgorithm::initializeGeneration()
{
	for (int i = 0; i < populationSize; i++)
	{
		ClassicalIndividual* randomIndividual = new ClassicalIndividual(caseInstance);
		randomIndividual->fillAllGensRandomly();
		generation[i] = randomIndividual;
	}
}

void GeneticAlgorithm::conductCrossovers()
{
	bool isIndividualsCountOdd = (populationSize & 1);
	int maxEvenCountOfIndividuals = populationSize - (int)isIndividualsCountOdd;

	for (int i = 0; i < maxEvenCountOfIndividuals; i += GeneticAlgorithm::PAIR_SIZE)
	{
		PairOfIndividuals crossoverPair = pairFromCrossoverAttempt();

		nextGeneration[i] = crossoverPair.individual1;
		nextGeneration[i + 1] = crossoverPair.individual2;
	}
	if (isIndividualsCountOdd)
	{
		PairOfIndividuals crossoverPair = pairFromCrossoverAttempt();
		ClassicalIndividual* fitterIndividual = crossoverPair.getFitterIndividual();

		nextGeneration[populationSize - 1] = fitterIndividual;

		// we must delete one of the copies

		if (fitterIndividual == crossoverPair.individual1)
			delete crossoverPair.individual2;
		else
			delete crossoverPair.individual1;
	}
}

void GeneticAlgorithm::conductMutations()
{
	for (int i = 0; i < populationSize; i++)
	{
		nextGeneration[i]->tryToMutateAllGensRandomly(genMutationChance);

		if (nextGeneration[i]->evaluateFitness() > theBestSolution->evaluateFitness())
		{
			delete theBestSolution;
			theBestSolution = new ClassicalIndividual(*nextGeneration[i]);
		}
	}
}

void GeneticAlgorithm::ensureThatTheBestIndividualIsKept()
{
	int indexForTheBestIndividualIntroduction = Mt19937Randomizer::getSingletonInstance()->randInRange(populationSize);
	ClassicalIndividual* individualToRemoveForThePurposeOfMakingSpace = generation[indexForTheBestIndividualIntroduction];

	delete individualToRemoveForThePurposeOfMakingSpace;

	generation[indexForTheBestIndividualIntroduction] = new ClassicalIndividual(*theBestSolution);
}

void GeneticAlgorithm::fillNextGeneration()
{
	conductCrossovers();
	conductMutations();
	ensureThatTheBestIndividualIsKept();
}

PairOfIndividuals GeneticAlgorithm::matchPairRandomly()
{
	int indexOfFirstIndividual = Mt19937Randomizer::getSingletonInstance()->randInRange(populationSize);
	int indexOfSecondIndividual = Mt19937Randomizer::getSingletonInstance()->randInRange(populationSize);

	ClassicalIndividual* firstIndividual = generation[indexOfFirstIndividual];
	ClassicalIndividual* secondIndividual = generation[indexOfSecondIndividual];

	return PairOfIndividuals(firstIndividual, secondIndividual);
}

PairOfIndividuals GeneticAlgorithm::pairFromCrossoverAttempt()
{
	double diceRoll = Mt19937Randomizer::getSingletonInstance()->chanceRand();

	PairOfIndividuals pair1 = matchPairRandomly();
	PairOfIndividuals pair2 = matchPairRandomly();

	ClassicalIndividual* winner1 = pair1.getFitterIndividual();
	ClassicalIndividual* winner2 = pair2.getFitterIndividual();

	if (diceRoll <= crossoverChance)
		return createCrossoverChildren(winner1, winner2);
	else
		return PairOfIndividuals(new ClassicalIndividual(*winner1), new ClassicalIndividual(*winner2));
}

PairOfIndividuals GeneticAlgorithm::createCrossoverChildren(ClassicalIndividual* parent1, ClassicalIndividual* parent2)
{
	int exclusiveIndexOfCut = Mt19937Randomizer::getSingletonInstance()->randInRange(parent1->getSizeOfGenotype() - 1);
	exclusiveIndexOfCut++;

	return parent1->crossover(parent2, exclusiveIndexOfCut);
}

ClassicalIndividual* GeneticAlgorithm::copyTheBestSolutionInTheGeneration()
{
	ClassicalIndividual* theBestSolutionInGeneration = generation[0];

	for (int i = 0; i < populationSize; i++)
	{
		if (theBestSolutionInGeneration->evaluateFitness() < generation[i]->evaluateFitness())
			theBestSolutionInGeneration = generation[i];
	}

	return new ClassicalIndividual(*theBestSolutionInGeneration);
}


GeneticAlgorithm::GeneticAlgorithm(int populationSize, double crossoverChance, double genMutationChance, OptimazationCase& standardEvaluator):
	GeneticOptimizer(standardEvaluator),
	populationSize(populationSize),
	crossoverChance(crossoverChance),
	genMutationChance(genMutationChance),
	isInitialized(false)
{
	this->generation = nullptr;
	this->nextGeneration = nullptr;
	this->theBestSolution = nullptr;
}

GeneticAlgorithm::~GeneticAlgorithm()
{
	if (isInitialized)
	{
		for (int i = 0; i < populationSize; i++)
			delete generation[i];

		delete[] generation;
		delete[] nextGeneration;

		delete theBestSolution;
	}
}

void GeneticAlgorithm::reset()
{
	if (populationSize > 0)
	{
		this->generation = new ClassicalIndividual * [populationSize];
		this->nextGeneration = new ClassicalIndividual * [populationSize];
		initializeGeneration();
		theBestSolution = copyTheBestSolutionInTheGeneration();
	}
	else
		theBestSolution = nullptr;

	isInitialized = true;
}

void GeneticAlgorithm::runIteration()
{
	fillNextGeneration();
	swapGenerationsAddresses();				// I want to save memory space
	clearNextGeneration();					// I want to keep next generation as 'empty' array in each step
}


Individual* GeneticAlgorithm::peekTheBestIndividual()
{
	return (Individual*) theBestSolution;
}

Individual* GeneticAlgorithm::copyTheBestIndividual()
{
	if (theBestSolution == nullptr)
		return nullptr;

	ClassicalIndividual* result = theBestSolution;
	theBestSolution = new ClassicalIndividual(*theBestSolution);
	return (Individual*) result;
}

bool GeneticAlgorithm::isReadyToSearch()
{
	return !(populationSize <= 0 || !isInitialized);
}
