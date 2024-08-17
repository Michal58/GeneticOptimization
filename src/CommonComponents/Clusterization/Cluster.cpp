#include "Cluster.h"

Cluster::Cluster(int associatedIndexInDistances):
	Hashable(false),
	associatedDistinctNumber(associatedIndexInDistances) {}

int Cluster::getAssociatedDistincNumber() const
{
	return associatedDistinctNumber;
}

bool Cluster::operator==(const Cluster& other) const
{
	return this->associatedDistinctNumber==other.associatedDistinctNumber;
}

unsigned int Cluster::calculateHash()
{
	std::hash<int> hasher;
	return hasher(associatedDistinctNumber);
}

bool Cluster::equals(const Hashable& other) const
{
	return isInstanceOf<Cluster>(&other);
}
