#include "ParameterLessPopulationPyramid.h"


void ParameterLessPopulationPyramid::decideAboutUpadingPyramidWithIndividual(P3Individual& potentiallyDistinctIndividual, int potentialPyramidLevelToUpdate)
{
    bool isIndividualDistinct = this->isIndividualDistinct(potentiallyDistinctIndividual);
    if (isIndividualDistinct)
    {
        P3Individual* actualIndividualToAdd = new P3Individual(potentiallyDistinctIndividual);
        populationPyramid->getOrCreateNextLevelAt(potentialPyramidLevelToUpdate).addIndividual(actualIndividualToAdd);
        allDistinctIndividualsSet->insert(actualIndividualToAdd);
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

void ParameterLessPopulationPyramid::runIteration()
{
    P3Individual currentSolutionIndividual(caseInstance);
    currentSolutionIndividual.greedilyOptimize(*commonGreedyOptimizer);
    decideAboutUpadingPyramidWithIndividual(currentSolutionIndividual, 0);
    for (int iPyramidDepth = 0; populationPyramid->hasLevelAt(iPyramidDepth); iPyramidDepth++)
    {
        double startingFitness = currentSolutionIndividual.evaluateFitness();
        mixSolutionWithPopulation(currentSolutionIndividual, populationPyramid->getLevel(iPyramidDepth));
        bool hasFitnessImproved = currentSolutionIndividual.evaluateFitness() > startingFitness;
        if (hasFitnessImproved)
            decideAboutUpadingPyramidWithIndividual(currentSolutionIndividual, iPyramidDepth + 1);
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
