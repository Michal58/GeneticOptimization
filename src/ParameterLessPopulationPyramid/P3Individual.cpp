#include "P3Individual.h"

unsigned int P3Individual::calculateHash()
{
	return Hashable::calculateHashOfVectorOfElementaryTypes<int>(*genotype);
}

void P3Individual::registerChangesInGenotype()
{
	Individual::registerChangesInGenotype();
	signalizePossibleChangeInHash();
}

P3Individual::P3Individual(OptimazationCase& evaluator):
	Individual(evaluator),
	Hashable() {}

P3Individual::P3Individual(const P3Individual& other):
	Individual(other),
	Hashable(other) {}

bool P3Individual::operator==(const P3Individual& other) const
{
	return *genotype==*other.genotype;
}

void P3Individual::greedilyOptimize()
{
	greedilyOptimize(GreedyHillClimber(*this, true, GreedyHillClimber::CONFIRMATION));
}

void P3Individual::greedilyOptimize(GreedyHillClimber& hillClimberToUse)
{
	hillClimberToUse.setIndividualToOptimize(*this, false);
	hillClimberToUse.optimizeIndividual();
}

ResultOfCrossover* P3Individual::crossover(Individual& donorOfGens, ParametersOfCrossover& crossoverParameters)
{
	ClusterBaseCrossoverParameters& actualParameters = (ClusterBaseCrossoverParameters&)crossoverParameters;
	GeneIndexCluster& crossoverCluster=actualParameters.crossoverCluster;

	std::vector<int>* previousGenesContainer = nullptr;
	previousGenesContainer = new std::vector<int>;

	for (int indexOfChange : crossoverCluster.shareIndicies())
	{
		previousGenesContainer->push_back((*genotype)[indexOfChange]);
		genotype->at(indexOfChange) = donorOfGens.getGenAt(indexOfChange);
	}

	return (ResultOfCrossover*) new PreviousGenes(previousGenesContainer);
}

Individual* P3Individual::clone()
{
	return new P3Individual(*this);
}

Randomizer& P3Individual::getDefaultRandomizer()
{
	return *Mt19937Randomizer::getSingletonInstance();
}

void P3Individual::revertChanges(GeneIndexCluster& clusterOfChange, std::vector<int>* previousGenes, double previousFitness)
{
	std::vector<int>::iterator iteratorOfPreviousGenes = previousGenes->begin();
	for (int indexOfChange : clusterOfChange.shareIndicies())
	{
		genotype->at(indexOfChange) = *iteratorOfPreviousGenes;
		iteratorOfPreviousGenes++;
	}
	forcelyMemoizeFitness(previousFitness);
}

bool P3Individual::equals(const Hashable& other) const
{
	return isInstanceOf<P3Individual>(&other) && *this == *((P3Individual*)&other);
}

PreviousGenes::PreviousGenes(std::vector<int>* previousGenes)
{
	this->previousGenes = previousGenes;
}

ClusterBaseCrossoverParameters::ClusterBaseCrossoverParameters(GeneIndexCluster& crossoverCluster):
	crossoverCluster(crossoverCluster) {}
