#include "SelectorOfClustersMerging.h"

SelectorOfClustersMerging::SelectorOfClustersMerging()
{
	associatedLookup = nullptr;
}

SelectorOfClustersMerging::SelectorOfClustersMerging(DistancesLookup& associatedLookup)
{
	setAssociatedLookup(associatedLookup);
}

void SelectorOfClustersMerging::setAssociatedLookup(DistancesLookup& associatedLookup)
{
	this->associatedLookup = &associatedLookup;
}
