#include "MinHeapBasedSelector.h"

bool MinHeapBasedSelector::isClusterRemoved(Cluster& toCheckIfIsRemoved)
{
	return removedClusters.find(&toCheckIfIsRemoved) != removedClusters.end();
}

bool MinHeapBasedSelector::isAnyOfTheClustersRemoved(ClustersPair pair)
{
	return isClusterRemoved(pair.first()) || isClusterRemoved(pair.second());
}

void MinHeapBasedSelector::markClustersAsRemoved(ClustersPair pair)
{
	removedClusters.insert(&pair.first());
	removedClusters.insert(&pair.second());
}

DistancesLookup& MinHeapBasedSelector::getAssociatedLookup()
{
	return *associatedLookup;
}

void MinHeapBasedSelector::setAssociatedLookup(DistancesLookup& associatedLookup)
{
	SelectorOfClustersMerging::setAssociatedLookup(associatedLookup);
	std::vector<ClustersPair> pairsInLookup = associatedLookup.getKeysOfMap();
	for (ClustersPair pair : pairsInLookup)
		minHeapOfPairs.push(HeapNodeOfClusterPair(pair, *this));
}

void MinHeapBasedSelector::selectClustersForMerging(Cluster*& firstSelectedClusterContainer, Cluster*& secondSelectedClusterContainer)
{
	while (isAnyOfTheClustersRemoved(minHeapOfPairs.top().getPair()))
		minHeapOfPairs.pop();
	ClustersPair clustersWithTheSmallestDistanceToEachOther = minHeapOfPairs.top().getPair();
	markClustersAsRemoved(clustersWithTheSmallestDistanceToEachOther);
	firstSelectedClusterContainer = &clustersWithTheSmallestDistanceToEachOther.first();
	secondSelectedClusterContainer = &clustersWithTheSmallestDistanceToEachOther.second();
}

void MinHeapBasedSelector::updateWithMergedCluster(Cluster* mergedCluster)
{
	std::vector<ClustersPair> containerForAsscoaitedPairs;
	associatedLookup->putIntoContainerPairsAssociatedWithCluster(containerForAsscoaitedPairs, mergedCluster);
	for (ClustersPair newPair : containerForAsscoaitedPairs)
		minHeapOfPairs.push(HeapNodeOfClusterPair(newPair, *this));
}


HeapNodeOfClusterPair::HeapNodeOfClusterPair(ClustersPair associatedPair, MinHeapBasedSelector& associatedSelector):
	associatedPair(associatedPair),
	associatedSelector(&associatedSelector) {}

ClustersPair HeapNodeOfClusterPair::getPair() const
{
	return associatedPair;
}

double HeapNodeOfClusterPair::getPairDistance()
{
	return associatedSelector->getAssociatedLookup().getDistance(associatedPair);
}

bool HeapNodeOfClusterPair::operator==(const HeapNodeOfClusterPair& other) const
{
	return associatedPair.equals(other.associatedPair);
}

bool ComparatorOfClustersPair::operator()(HeapNodeOfClusterPair firstNode, HeapNodeOfClusterPair secondNode)
{
	return firstNode.getPairDistance() > secondNode.getPairDistance();
}
