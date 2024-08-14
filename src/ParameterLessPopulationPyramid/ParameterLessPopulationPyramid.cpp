#include "ParameterLessPopulationPyramid.h"


void ParameterLessPopulationPyramid::ifIndividualIsDistinctAddItToPopulationAtDepthAndUpdateSetOfDistinctIndividuals(P3Individual& potentiallyDistinctIndividual, int depth)
{
    bool isIndividualDistinct = this->isIndividualDistinct(potentiallyDistinctIndividual);
    if (isIndividualDistinct)
    {
        P3Individual* actualIndividualToAdd = new P3Individual(potentiallyDistinctIndividual);
        populationPyramid->getOrCreateNextLevelAt(depth).addIndividual(actualIndividualToAdd);
        allDistinctIndividualsSet->insert(actualIndividualToAdd);
    }
}

void ParameterLessPopulationPyramid::addSolutionAfterCrossoverToPopulationIfItIsNotWorse(P3Individual* solutionAfterCrossover, double previousEvaluation, int crossoverLevel)
{
    bool isCrossoverIndividualNotWorse = solutionAfterCrossover->evaluateFitness() >= previousEvaluation;
    if (isCrossoverIndividualNotWorse)
        ifIndividualIsDistinctAddItToPopulationAtDepthAndUpdateSetOfDistinctIndividuals(*solutionAfterCrossover, crossoverLevel + 1);
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

void ParameterLessPopulationPyramid::runIteration()
{
    P3Individual currentSolutionIndividual(caseInstance);
    currentSolutionIndividual.greedilyOptimize(*commonGreedyOptimizer);
    ifIndividualIsDistinctAddItToPopulationAtDepthAndUpdateSetOfDistinctIndividuals(currentSolutionIndividual, 0);
    for (int i = 0; populationPyramid->hasLevelAt(i); i++)
    {
        double startingFitness = currentSolutionIndividual.evaluateFitness();
        performCrossoverInPopulation(currentSolutionIndividual, populationPyramid->getLevel(i));
        addSolutionAfterCrossoverToPopulationIfItIsNotWorse(&currentSolutionIndividual, startingFitness, i);
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
