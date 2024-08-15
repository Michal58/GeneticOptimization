#include "Cluster.h"

Cluster::Cluster(int associatedIndexInDistances):
	associatedDistinctNumber(associatedIndexInDistances) {}

int Cluster::getAssociatedDistincNumber() const
{
	return associatedDistinctNumber;
}

bool Cluster::operator==(const Cluster& other) const
{
	return this->associatedDistinctNumber==other.associatedDistinctNumber;
}
