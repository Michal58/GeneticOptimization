#include "DistancesLookup.h"

ClustersPair::ClustersPair(const Cluster& firstCluster, const Cluster& secondCluster):
	Hashable(false),
	firstCluster(firstCluster),
	secondCluser(secondCluser) {}

unsigned int ClustersPair::calculateHash()
{
	std::vector<int> clustersDistinctNumbers =
	{
		firstCluster.getAssociatedDistincNumber(),
		secondCluser.getAssociatedDistincNumber()
	};

	return Hashable::calculateHashOfVectorOfElementaryTypes<int>(clustersDistinctNumbers);
}

bool ClustersPair::equals(const Hashable& other) const
{
	if (!isInstanceOf<ClustersPair>(other))
		return false;

	ClustersPair& otherClusterPair = (ClustersPair&)other;

	return (this->firstCluster == otherClusterPair.firstCluster && this->secondCluser == otherClusterPair.secondCluser)
		|| (this->firstCluster == otherClusterPair.secondCluser && this->secondCluser == otherClusterPair.firstCluster);
}

bool DistancesLookup::isThereClusterPair(ClustersPair pairToCheck)
{
	return distancesMap.find(pairToCheck) != distancesMap.end();
}

DistancesLookup::DistancesLookup(InitializerOfDistancesLookup& initializator)
{
	initializator.initializeDistancesLookup(*this);
}

double DistancesLookup::getDistance(const Cluster& first, const Cluster& second)
{
	ClustersPair pairOfGivenClusters(first, second);
	if (!isThereClusterPair(pairOfGivenClusters))
		std::runtime_error(DISTANCE_DOESNT_EXIST_ERROR_MESSAGE);
	return distancesMap[pairOfGivenClusters];
}
