#include "ReciprocalNearestNeighborsSelector.h"

Cluster* ReciprocalNearestNeighborsSelector::getLastButOneSeriesElement()
{
	return *(seriesOfClustersWithDescendingDistances.end() - LAST_BUT_ONE_OFFSET);
}

Cluster* ReciprocalNearestNeighborsSelector::findClusterInSingleClustersWhichMakesTheClosestDistanceWithLastElementOfSeries()
{
	Cluster* lastElementOfSeries = seriesOfClustersWithDescendingDistances.back();

	double theBestDistance = DBL_MAX;
	Cluster* theBestFoundCluster = nullptr;

	for (Cluster* singleCurrentCluster : *singleClustersOutOfSeries)
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

void ReciprocalNearestNeighborsSelector::moveToSeriesClusterFromSingleClusters(Cluster* toExpandSeries)
{
	seriesOfClustersWithDescendingDistances.push_back(toExpandSeries);
	singleClustersOutOfSeries->erase(toExpandSeries);
}

bool ReciprocalNearestNeighborsSelector::findIfAddingClusterFromSingleClusterKeepsDescendingOrderOfSeries(Cluster* theBestClusterFoundInSingleClusters)
{
	Cluster* lastSeriesElement = seriesOfClustersWithDescendingDistances.back();
	Cluster* lastButOneSeriesElement = getLastButOneSeriesElement();

	double distanceOfTheBestFoundElementInSingleClusters = associatedLookup->getDistance(*lastSeriesElement, *theBestClusterFoundInSingleClusters);
	double distanceOfCurrentLastTwoElementsInSeries = associatedLookup->getDistance(*lastSeriesElement, *lastButOneSeriesElement);

	return distanceOfTheBestFoundElementInSingleClusters > distanceOfCurrentLastTwoElementsInSeries;
}

ReciprocalNearestNeighborsSelector::ReciprocalNearestNeighborsSelector()
{
	singleClustersOutOfSeries = nullptr;
}

ReciprocalNearestNeighborsSelector::~ReciprocalNearestNeighborsSelector()
{
	delete singleClustersOutOfSeries;
}

void ReciprocalNearestNeighborsSelector::setAssociatedLookup(DistancesLookup& associatedLookup)
{
	SelectorOfClustersMerging::setAssociatedLookup(associatedLookup);
	singleClustersOutOfSeries = new ClustersSet(associatedLookup.shareAllSingleClusters());
}

void ReciprocalNearestNeighborsSelector::selectClustersForMerging(Cluster*& firstSelectedClusterContainer, Cluster*& secondSelectedClusterContainer)
{
	if (seriesOfClustersWithDescendingDistances.empty())
	{
		Cluster* arbitrarilySelectedCluster = *singleClustersOutOfSeries->begin();
		moveToSeriesClusterFromSingleClusters(arbitrarilySelectedCluster);
	}

	bool isTheBestFoundSingleClusterImporvement = true;

	while (isTheBestFoundSingleClusterImporvement && !singleClustersOutOfSeries->empty());
	{
		Cluster* theBestClusterFoundInSingleClusters = findClusterInSingleClustersWhichMakesTheClosestDistanceWithLastElementOfSeries();

		if (seriesOfClustersWithDescendingDistances.size() > 1)
			isTheBestFoundSingleClusterImporvement = findIfAddingClusterFromSingleClusterKeepsDescendingOrderOfSeries(theBestClusterFoundInSingleClusters);
		
		if (isTheBestFoundSingleClusterImporvement)
			moveToSeriesClusterFromSingleClusters(theBestClusterFoundInSingleClusters);
	}

	firstSelectedClusterContainer = getLastButOneSeriesElement();
	secondSelectedClusterContainer = seriesOfClustersWithDescendingDistances.back();
	seriesOfClustersWithDescendingDistances.pop_back();
}

void ReciprocalNearestNeighborsSelector::updateWithNewCluster(Cluster* newCluster)
{
	seriesOfClustersWithDescendingDistances.back() = newCluster;
}
