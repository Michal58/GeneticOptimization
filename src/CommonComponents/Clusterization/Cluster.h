#pragma once
#include <iostream>
#include "../Hashing/Hashable.h"
#include "../Functionalities//Functionalities.h"

class Cluster: public Hashable
{
	int associatedDistinctNumber;

public:

	Cluster(int associatedDistinctNumber);
	int getAssociatedDistincNumber() const;
	bool operator==(const Cluster& other) const;
	virtual bool isSingletonCluster() = 0;
	virtual void mergeWithOther(const Cluster& other) = 0;
	virtual Cluster* getCopy(const Cluster& other) const = 0;
	virtual int cardinality() = 0;

	unsigned int calculateHash() override;
	bool equals(const Hashable& other) const override;
};

