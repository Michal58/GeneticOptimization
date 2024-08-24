#include "ParameterLessPopulationPyramid.h"


void ParameterLessPopulationPyramid::decideOnAddingIndividualToPyramid(P3Individual& potentiallyDistinctIndividual, int potentialPyramidLevelToUpdate)
{
    bool isIndividualDistinct = this->isIndividualDistinct(potentiallyDistinctIndividual);
    if (isIndividualDistinct)
    {
        P3Individual* actualIndividualToAdd = new P3Individual(potentiallyDistinctIndividual);
        populationPyramid->addIndividualAndOptionallyCreateLevelAtDepth(actualIndividualToAdd, potentialPyramidLevelToUpdate);
        allDistinctIndividualsSet->insert(actualIndividualToAdd);
    }
}

void ParameterLessPopulationPyramid::tryToImproveSolutionWithCluster(GeneIndexCluster& clusterOfChange, P3Individual& solution, PopulationLevel& population)
{
    bool wasSolutionChanged = false;
    std::unordered_set<int> usedIndicesOfPopulationIndividuals;
    int populationLevelSize = population.size();

    while (!wasSolutionChanged && usedIndicesOfPopulationIndividuals.size() < populationLevelSize)
    {
        int diceRoll;
        do
            diceRoll = Mt19937Randomizer::getSingletonInstance()->randInRange(populationLevelSize);
        while (isThereElementIn<std::unordered_set<int>, int>(usedIndicesOfPopulationIndividuals, diceRoll));
        usedIndicesOfPopulationIndividuals.insert(diceRoll);

        P3Individual& randomIndividualFromPopulation = population.getIndividualFromIndex(diceRoll);
        ClusterBaseCrossoverParameters parameters(clusterOfChange);

        double startingFitness = solution.evaluateFitness();
        unsigned int startingHash = solution.getHash();

        PreviousGenes* resultOfCrossoverMadeInPlace = (PreviousGenes*)solution.crossover(randomIndividualFromPopulation, parameters);

        double fitnessAfterChanges = solution.evaluateFitness();
        wasSolutionChanged = resultOfCrossoverMadeInPlace->didGenesChange;
        bool didSolutionDecreased = fitnessAfterChanges < startingFitness;
        if (wasSolutionChanged && didSolutionDecreased)
            solution.revertChanges(clusterOfChange, resultOfCrossoverMadeInPlace->previousGenes, startingFitness, startingHash);
        
        delete resultOfCrossoverMadeInPlace->previousGenes;
        delete resultOfCrossoverMadeInPlace;
    }
}

ParameterLessPopulationPyramid::ParameterLessPopulationPyramid(OptimazationCase& caseInstance):
    GeneticOptimizer(caseInstance),
    isInitialized(false)
{
    theBestIndividual = nullptr;
    populationPyramid = nullptr;
    commonGreedyOptimizer = nullptr;
    allDistinctIndividualsSet = nullptr;
}

ParameterLessPopulationPyramid::~ParameterLessPopulationPyramid()
{
    delete theBestIndividual;
    delete populationPyramid;
    delete commonGreedyOptimizer;
    delete allDistinctIndividualsSet;
}

bool ParameterLessPopulationPyramid::isIndividualDistinct(P3Individual& possibleDistinctIndividual)
{
    return allDistinctIndividualsSet->find(&possibleDistinctIndividual) == allDistinctIndividualsSet->end();
}

void ParameterLessPopulationPyramid::mixSolutionWithPopulation(P3Individual& solution, PopulationLevel& population)
{
    for (Cluster* clusterOfChange : population.shareClusters())
        tryToImproveSolutionWithCluster(*(GeneIndexCluster*)clusterOfChange, solution, population);
}

void ParameterLessPopulationPyramid::reset()
{
    theBestIndividual = nullptr;
    populationPyramid = new Pyramid(caseInstance);
    commonGreedyOptimizer = new GreedyHillClimber(caseInstance, true, GreedyHillClimber::TURN_OFF_CONFIRMATION);
    allDistinctIndividualsSet = new IndividualsHashSet;

    isInitialized = true;
}

bool ParameterLessPopulationPyramid::isReadyToSearch()
{
    return isInitialized;
}

void ParameterLessPopulationPyramid::runIteration()
{
    P3Individual currentSolutionIndividual(caseInstance);
    currentSolutionIndividual.fillAllGensRandomly();

    currentSolutionIndividual.greedilyOptimize(*commonGreedyOptimizer);
    decideOnAddingIndividualToPyramid(currentSolutionIndividual, 0);
    for (int iPyramidDepth = 0; populationPyramid->hasLevelAt(iPyramidDepth); iPyramidDepth++)
    {
        double startingFitness = currentSolutionIndividual.evaluateFitness();
        mixSolutionWithPopulation(currentSolutionIndividual, populationPyramid->getLevel(iPyramidDepth));
        bool hasFitnessImproved = currentSolutionIndividual.evaluateFitness() > startingFitness;
        if (hasFitnessImproved)
            decideOnAddingIndividualToPyramid(currentSolutionIndividual, iPyramidDepth + 1);
    }

    if (theBestIndividual == nullptr || currentSolutionIndividual.evaluateFitness() > theBestIndividual->evaluateFitness())
    {
        delete theBestIndividual;
        theBestIndividual = new P3Individual(currentSolutionIndividual);
    }
}

Individual* ParameterLessPopulationPyramid::peekTheBestIndividual()
{
    return theBestIndividual;
}

Individual* ParameterLessPopulationPyramid::copyTheBestIndividual()
{
    return theBestIndividual->clone();
}
