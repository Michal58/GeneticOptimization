#pragma once
#include <iostream>

class Cluster
{
	int associatedDistinctNumber;

public:

	Cluster(int associatedDistinctNumber);
	int getAssociatedDistincNumber() const;
	bool operator==(const Cluster& other) const;
	virtual bool isSingletonCluster() = 0;
};

