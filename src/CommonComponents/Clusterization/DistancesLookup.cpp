#include "DistancesLookup.h"

ClustersPair::ClustersPair():
	firstCluster(nullptr),
	secondCluster(nullptr) {}

ClustersPair::ClustersPair(Cluster& firstCluster, Cluster& secondCluster):
	Hashable(false),
	firstCluster(&firstCluster),
	secondCluster(&secondCluster) {}

Cluster& ClustersPair::first()
{
	return *firstCluster;
}

Cluster& ClustersPair::second()
{
	return *secondCluster;
}

unsigned int ClustersPair::calculateHash() const
{
	std::vector<int> clustersDistinctNumbers =
	{
		firstCluster->getAssociatedDistincNumber(),
		secondCluster->getAssociatedDistincNumber()
	};
	std::sort(clustersDistinctNumbers.begin(), clustersDistinctNumbers.end());

	return Hashable::calculateHashOfVectorOfElementaryTypes<int>(clustersDistinctNumbers);
}

bool ClustersPair::equals(const Hashable& other) const
{
	if (!isInstanceOf<ClustersPair>(other))
		return false;

	ClustersPair& otherClusterPair = (ClustersPair&)other;

	return (*this->firstCluster == *otherClusterPair.firstCluster && *this->secondCluster == *otherClusterPair.secondCluster)
		|| (*this->firstCluster == *otherClusterPair.secondCluster && *this->secondCluster == *otherClusterPair.firstCluster);
}

bool DistancesLookup::isThereClusterPair(ClustersPair pairToCheck)
{
	return distancesMap.find(pairToCheck) != distancesMap.end();
}

Cluster* DistancesLookup::mergeClusters(const Cluster& firstToMerge, const Cluster& secondToMerge)
{
	return firstToMerge.getMergedCluster(secondToMerge, firstToMerge.proposeDistinctNumber());
}

double DistancesLookup::calculateCkDistanceToCiCjUnion(Cluster& Ck, Cluster& Ci, Cluster& Cj)
{
	ClustersPair CkCi(Ck, Ci);
	ClustersPair CkCj(Ck, Cj);
	

	return (Ci.cardinality() * distancesMap[CkCi] + Cj.cardinality() * distancesMap[CkCj])
		/ (Ci.cardinality() + Cj.cardinality());
}

void DistancesLookup::mapDistanceToMergedCluster(Cluster* distanceCalculationParticipant, Cluster* mergedCluster, Cluster& firstMergeMember, Cluster& secondMergeMember)
{
	ClustersPair newPair(*mergedCluster, *distanceCalculationParticipant);
	double newDistance = calculateCkDistanceToCiCjUnion(*distanceCalculationParticipant, firstMergeMember, secondMergeMember);
	distancesMap.insert({ newPair,newDistance });
}

void DistancesLookup::removePairsWithClusterFromDistances(Cluster& toRemove)
{
	for (Cluster* kCluster : allSingleClusters)
	{
		ClustersPair distanceToRemove(toRemove, *kCluster);
		distancesMap.erase(distanceToRemove);
	}
}

void DistancesLookup::updateDistancesToMergedCluster(Cluster* mergedCluster, Cluster& firstMergeMember, Cluster& secondMergeMember)
{
	for (Cluster* kCluster : allSingleClusters)
		mapDistanceToMergedCluster(kCluster, mergedCluster, firstMergeMember, secondMergeMember);

	distancesMap.erase({ firstMergeMember,secondMergeMember });
	removePairsWithClusterFromDistances(firstMergeMember);
	removePairsWithClusterFromDistances(secondMergeMember);
}

DistancesLookup::DistancesLookup(InitializerOfDistancesLookup& initializer)
{
	initializer.initializeDistancesLookup(*this);
}

double DistancesLookup::getDistance(Cluster& first, Cluster& second)
{
	ClustersPair pairOfGivenClusters(first, second);
	if (!isThereClusterPair(pairOfGivenClusters))
		std::runtime_error(DISTANCE_DOESNT_EXIST_ERROR_MESSAGE);
	return distancesMap[pairOfGivenClusters];
}

double DistancesLookup::getDistance(ClustersPair pair)
{
	return getDistance(pair.first(), pair.second());
}

Cluster* DistancesLookup::replaceClustersByMergedClusterAndReturnIt(Cluster& firstMerge, Cluster& secondMerge)
{
	Cluster* mergedCluster = mergeClusters(firstMerge, secondMerge);
	allSingleClusters.erase(&firstMerge);
	allSingleClusters.erase(&secondMerge);
	updateDistancesToMergedCluster(mergedCluster, firstMerge, secondMerge);
	allSingleClusters.insert(mergedCluster);

	return mergedCluster;
}

ClustersSet& DistancesLookup::shareAllSingleClusters()
{
	return allSingleClusters;
}

void DistancesLookup::putIntoContainerPairsAssociatedWithCluster(std::vector<ClustersPair>& container, Cluster* clusterToAssociate)
{
	for (Cluster* kCluster : allSingleClusters)
	{
		ClustersPair currentPairing = ClustersPair(*clusterToAssociate, *kCluster);
		if (isThereClusterPair(currentPairing))
			container.push_back(currentPairing);
	}
}


std::vector<ClustersPair> DistancesLookup::getKeysOfMap()
{
	std::vector<ClustersPair> keys;
	keys.reserve(distancesMap.size());
	for (std::pair<const ClustersPair,double> distancesPair : distancesMap)
		keys.push_back(distancesPair.first);
	
	return keys;
}

int DistancesLookup::allClustersCardinality()
{
	return allSingleClusters.size();
}

ClustersSet& InitializerOfDistancesLookup::accessSingleClusters(DistancesLookup& lookupToAccess)
{
	return lookupToAccess.allSingleClusters;
}

ClusterPairsToDistances& InitializerOfDistancesLookup::accessDistancesMap(DistancesLookup& lookupToAccess)
{
	return lookupToAccess.distancesMap;
}
