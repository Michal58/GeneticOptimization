#pragma once
#include <iostream>
#include <vector>

class Hashable
{
	static const unsigned int HASH_ADDITION_ELEMENT = 0x9e3779b9;
	static const unsigned int HASH_LEFT_SHIFT_DEGREE = 6;
	static const unsigned int HASH_RIGHT_SHIFT_DEGREE = 2;

	static const bool DEFUALT_MEMOIZATION_DECISION = true;

	bool shouldHashBeMemoized;

	unsigned int memoizedHash;
	bool wasHashEvaluated;

	void memoizeHash(int calculatedHash);

public:

	Hashable(bool shoudHashBeMemoized);
	Hashable();

	static unsigned int combineHashes(unsigned int accumulatedHash, unsigned int partialHash);

	template<typename T>
	static unsigned int calculateHashOfVectorOfElementaryTypes(const std::vector<T>& vectorOfValues);

	virtual unsigned int calculateHash() const = 0;

	unsigned int getHash();
	unsigned int getHashWithoutMemoizing() const;
	virtual bool equals(const Hashable& other) const = 0;

	void signalizePossibleChangeInHash();
	void forcelyMemoizeHash(unsigned int hashToSet);
	bool isHashMemoized();
};

// place for template methods implementations

template<typename T>
inline unsigned int Hashable::calculateHashOfVectorOfElementaryTypes(const std::vector<T>& vectorOfValues)
{
	std::hash<T> hashingFunction;
	unsigned int accumulatedHash = hashingFunction(vectorOfValues.at(0));
	for (int i = 1; i < vectorOfValues.size(); i++)
	{
		unsigned int partialHash = hashingFunction(vectorOfValues.at(i));
		accumulatedHash = combineHashes(accumulatedHash, partialHash);
	}

	return accumulatedHash;
}
