#include "MinHeapBasedSelector.h"

bool MinHeapBasedSelector::isClusterRemoved(Cluster& toCheckIfIsRemoved)
{
	return removedClusters.find(&toCheckIfIsRemoved) != removedClusters.end();
}

bool MinHeapBasedSelector::isAnyOfTheClustersRemoved(ClustersPair pair)
{
	return isClusterRemoved(pair.firstCluster) || isClusterRemoved(pair.secondCluser);
}

void MinHeapBasedSelector::markClustersAsRemoved(ClustersPair pair)
{
	removedClusters.insert(&pair.firstCluster);
	removedClusters.insert(&pair.secondCluser);
}

DistancesLookup& MinHeapBasedSelector::getAssociatedLookup()
{
	return *associatedLookup;
}

void MinHeapBasedSelector::setAssociatedLookup(DistancesLookup& associatedLookup)
{
	SelectorOfClustersMerging::setAssociatedLookup(associatedLookup);
	for (ClustersPair pair : associatedLookup.getKeysOfMap())
		minHeapOfPairs.push(HeapNodeOfClusterPair(pair, *this));
}

void MinHeapBasedSelector::selectClustersForMerging(Cluster*& firstSelectedClusterContainer, Cluster*& secondSelectedClusterContainer)
{
	while (isAnyOfTheClustersRemoved(minHeapOfPairs.top().getPair()))
		minHeapOfPairs.pop();
	ClustersPair clustersWithTheSmallestDistanceToEachOther = minHeapOfPairs.top().getPair();
	markClustersAsRemoved(clustersWithTheSmallestDistanceToEachOther);
	firstSelectedClusterContainer = &clustersWithTheSmallestDistanceToEachOther.firstCluster;
	secondSelectedClusterContainer = &clustersWithTheSmallestDistanceToEachOther.secondCluser;
}

void MinHeapBasedSelector::updateWithNewCluster(Cluster* newCluster)
{
	std::vector<ClustersPair> containerForAsscoaitedPairs;
	associatedLookup->putIntoContainerPairsAssociatedWithCluster(containerForAsscoaitedPairs, newCluster);
	for (ClustersPair newPair : containerForAsscoaitedPairs)
		minHeapOfPairs.push(HeapNodeOfClusterPair(newPair, *this));
}


HeapNodeOfClusterPair::HeapNodeOfClusterPair(ClustersPair associatedPair, MinHeapBasedSelector& associatedSelector):
	associatedPair(associatedPair),
	associatedSelector(associatedSelector) {}

ClustersPair HeapNodeOfClusterPair::getPair() const
{
	return associatedPair;
}

double HeapNodeOfClusterPair::getPairDistance()
{
	return associatedSelector.getAssociatedLookup().getDistance(associatedPair);
}

bool ComparatorOfClustersPair::operator()(HeapNodeOfClusterPair firstNode, HeapNodeOfClusterPair secondNode)
{
	return firstNode.getPairDistance() > secondNode.getPairDistance();
}
