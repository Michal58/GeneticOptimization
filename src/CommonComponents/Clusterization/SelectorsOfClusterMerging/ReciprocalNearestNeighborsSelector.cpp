#include "ReciprocalNearestNeighborsSelector.h"

Cluster* ReciprocalNearestNeighborsSelector::findClusterInSingleClustersWhichMakesTheClosestDistanceWithLastElementOfSeries()
{
	Cluster* lastElementOfSeries = seriesOfClustersWithDescendingDistances.back();

	double theBestDistance = DBL_MAX;
	Cluster* theBestFoundCluster = nullptr;

	for (Cluster* singleCurrentCluster : *singleClusters)
	{
		double currentDistance = associatedLookup->getDistance(ClustersPair(*lastElementOfSeries, *singleCurrentCluster));
		if (currentDistance > theBestDistance)
		{
			theBestDistance = currentDistance;
			theBestFoundCluster = singleCurrentCluster;
		}
	}

	return theBestFoundCluster;
}

ReciprocalNearestNeighborsSelector::ReciprocalNearestNeighborsSelector()
{
	singleClusters = nullptr;
}

ReciprocalNearestNeighborsSelector::~ReciprocalNearestNeighborsSelector()
{
	delete singleClusters;
}

void ReciprocalNearestNeighborsSelector::setAssociatedLookup(DistancesLookup& associatedLookup)
{
	SelectorOfClustersMerging::setAssociatedLookup(associatedLookup);
	singleClusters = new ClustersSet(associatedLookup.shareAllSingleClusters());
}

void ReciprocalNearestNeighborsSelector::selectClustersForMerging(Cluster*& fitsSelectedClusterContainer, Cluster*& secondSelectedClusterContainer)
{
	fitsSelectedClusterContainer = seriesOfClustersWithDescendingDistances.back();

	Cluster* arbitrarilySelectedCluster = *singleClusters->begin();
	seriesOfClustersWithDescendingDistances.push_back(arbitrarilySelectedCluster);
	Cluster* theBestClusterFoundInSingleClusters = findClusterInSingleClustersWhichMakesTheClosestDistanceWithLastElementOfSeries();

	Cluster* lastSeriesElement = seriesOfClustersWithDescendingDistances.back();
	Cluster* lastButOneSeriesElement = *(seriesOfClustersWithDescendingDistances.end() - LAST_BUT_ONE_OFFSET);

	double distanceOfTheBestFoundElementInSingleClusters = associatedLookup->getDistance(*lastSeriesElement, *theBestClusterFoundInSingleClusters);
	double distanceOfCurrentLastTwoElementsInSeries = associatedLookup->getDistance(*lastSeriesElement, *lastButOneSeriesElement);

	if (distanceOfTheBestFoundElementInSingleClusters > distanceOfCurrentLastTwoElementsInSeries)
	{
		secondSelectedClusterContainer = theBestClusterFoundInSingleClusters;
		singleClusters->erase(theBestClusterFoundInSingleClusters);
	}
	else
	{
		secondSelectedClusterContainer = lastButOneSeriesElement;
		seriesOfClustersWithDescendingDistances.pop_back();
	}
}

void ReciprocalNearestNeighborsSelector::updateWithNewCluster(Cluster* newCluster)
{
	seriesOfClustersWithDescendingDistances.back() = newCluster;
}
