#include "PopulationLevel.h"

void PopulationLevel::updateClusterizationAndFrequencies(P3Individual* newIndividual)
{
	clearVectorOfPointers(*estimatedGenesClusters);
	populationGenesFrequenciesLookup.updateWithIndividual(*newIndividual);
	EntropyBasedInitializer clustersAndDistancesInitializer(caseToOptimize, populationGenesFrequenciesLookup);
	DistancesLookup clustersDistancesLookup(clustersAndDistancesInitializer);
	MinHeapBasedSelector correctnessMergeSelector;
	ClusterizationPerformer clusterizationExecutor(correctnessMergeSelector);
	conductClusterization(clusterizationExecutor, clustersDistancesLookup);
}

void PopulationLevel::orderClustersWithSizeAscending()
{
	ClusterSizeComparator comparatorComponent;
	std::sort(estimatedGenesClusters->begin(), estimatedGenesClusters->end(), comparatorComponent);
}

void PopulationLevel::removeClusterWithCardinalityOfGenotype()
{
	if (estimatedGenesClusters->back()->cardinality() != getSomeIndividual()->getSizeOfGenotype())
		throw std::runtime_error(ERROR_IN_CLUSTERIZATION_PROCESS_ASSUMPTION);
	estimatedGenesClusters->pop_back();
}

void PopulationLevel::conductClusterization(ClusterizationPerformer& clusterizationExecutor, DistancesLookup& clustersDistancesLookup)
{
	estimatedGenesClusters = clusterizationExecutor.perfromClusterization(clustersDistancesLookup, true);
	orderClustersWithSizeAscending();
	removeClusterWithCardinalityOfGenotype();
}

PopulationLevel::PopulationLevel(OptimazationCase& caseToOptimize):
	caseToOptimize(caseToOptimize)
{
	estimatedGenesClusters = new std::vector<Cluster*>;
}

PopulationLevel::~PopulationLevel()
{
	clearVectorOfPointers(population);
	clearVectorOfPointers(*estimatedGenesClusters);
	delete estimatedGenesClusters;
}

void PopulationLevel::addIndividual(P3Individual* newIndividual)
{
	population.push_back(newIndividual);
	updateClusterizationAndFrequencies(newIndividual);
}

std::vector<Cluster*>& PopulationLevel::shareClusters()
{
	return *estimatedGenesClusters;
}

std::vector<int> PopulationLevel::getShuffledIndiciesOfIndividualsInPopulation()
{
	std::vector<int> indiciesToShuffle(population.size());
	std::iota(indiciesToShuffle.begin(), indiciesToShuffle.end(), 0);
	return indiciesToShuffle;
}

P3Individual* PopulationLevel::getSomeIndividual()
{
	return population[0];
}

P3Individual& PopulationLevel::getIndividualFromIndex(int index)
{
	return *(population[index]);
}

int PopulationLevel::size()
{
	return population.size();
}

bool ClusterSizeComparator::operator()(Cluster* first, Cluster* second) const
{
	return first->cardinality() < second->cardinality();
}
