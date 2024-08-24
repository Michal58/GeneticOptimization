#include "P3Individual.h"

unsigned int P3Individual::calculateHash() const
{
	return Hashable::calculateHashOfVectorOfElementaryTypes<int>(*genotype);
}

void P3Individual::registerChangesInGenotype()
{
	Individual::registerChangesInGenotype();
	signalizePossibleChangeInHash();
}

P3Individual::P3Individual(OptimizationCase& evaluator):
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
	greedilyOptimize(GreedyHillClimber(*this, true, GreedyHillClimber::TURN_OFF_CONFIRMATION));
}

void P3Individual::greedilyOptimize(GreedyHillClimber& hillClimberToUse)
{
	hillClimberToUse.setIndividualToOptimize(*this, false);
	hillClimberToUse.optimizeIndividual();
}

ResultOfCrossover* P3Individual::crossover(Individual& donorOfGens, ParametersOfCrossover& crossoverParameters)
{
	registerChangesInGenotype();

	ClusterBaseCrossoverParameters& actualParameters = (ClusterBaseCrossoverParameters&)crossoverParameters;
	GeneIndexCluster& crossoverCluster=actualParameters.crossoverCluster;

	std::vector<int>* previousGenesContainer = nullptr;
	previousGenesContainer = new std::vector<int>;
	previousGenesContainer->reserve(crossoverCluster.cardinality());

	bool isThereChangeInGenotype = false;
	for (int indexOfChange : crossoverCluster.shareIndicies())
	{
		previousGenesContainer->push_back(genotype->at(indexOfChange));
		int donatedGene = donorOfGens.getGeneAt(indexOfChange);
		int currentGene = genotype->at(indexOfChange);
		isThereChangeInGenotype = isThereChangeInGenotype || donatedGene != currentGene;
		genotype->at(indexOfChange) = donatedGene;
	}

	return (ResultOfCrossover*) new PreviousGenes(previousGenesContainer, isThereChangeInGenotype);
}

Individual* P3Individual::clone()
{
	return new P3Individual(*this);
}

Randomizer& P3Individual::getDefaultRandomizer()
{
	return *Mt19937Randomizer::getSingletonInstance();
}

void P3Individual::revertChanges(GeneIndexCluster& clusterOfChange, std::vector<int>* previousGenes, double previousFitness, unsigned int previousHash)
{
	registerChangesInGenotype();
	std::vector<int>::iterator iteratorOfPreviousGenes = previousGenes->begin();
	for (int indexOfChange : clusterOfChange.shareIndicies())
	{
		genotype->at(indexOfChange) = *iteratorOfPreviousGenes;
		iteratorOfPreviousGenes++;
	}
	forcelyMemoizeHash(previousHash);
	forcelyMemoizeFitness(previousFitness);
}

bool P3Individual::equals(const Hashable& other) const
{
	return isInstanceOf<P3Individual>(&other) && *this == *((P3Individual*)&other);
}

PreviousGenes::PreviousGenes(std::vector<int>* previousGenes, bool didGenesChange):
	didGenesChange(didGenesChange)
{
	this->previousGenes = previousGenes;
}

ClusterBaseCrossoverParameters::ClusterBaseCrossoverParameters(GeneIndexCluster& crossoverCluster):
	crossoverCluster(crossoverCluster) {}
