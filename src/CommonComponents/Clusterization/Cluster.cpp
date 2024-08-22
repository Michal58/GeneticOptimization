#include "Cluster.h"

Cluster::Cluster(int associatedIndexInDistances):
	Hashable(false),
	associatedDistinctNumber(associatedIndexInDistances) {}

Cluster::~Cluster() {}

int Cluster::getAssociatedDistincNumber() const
{
	return associatedDistinctNumber;
}

bool Cluster::operator==(const Cluster& other) const
{
	return this->associatedDistinctNumber==other.associatedDistinctNumber;
}

bool Cluster::isSingletonCluster()
{
	return cardinality() == 1;
}

unsigned int Cluster::calculateHash() const
{
	std::hash<int> hasher;
	return hasher(associatedDistinctNumber);
}

bool Cluster::equals(const Hashable& other) const
{
	return isInstanceOf<Cluster>(&other);
}
