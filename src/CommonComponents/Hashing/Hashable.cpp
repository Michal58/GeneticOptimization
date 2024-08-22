#include "Hashable.h"

void Hashable::memoizeHash(int calculatedHash)
{
	memoizedHash = calculatedHash;
	wasHashEvaluated = true;
}

// combineHashes was sourced from Boost library
// https://www.boost.org/LICENSE_1_0.txt

Hashable::Hashable(bool shoudHashBeMemoized):
	shouldHashBeMemoized(shoudHashBeMemoized),
	wasHashEvaluated(false) {}

Hashable::Hashable():
	Hashable(DEFUALT_MEMOIZATION_DECISION) {}

unsigned int Hashable::combineHashes(unsigned int accumulatedHash, unsigned int partialHash)
{
	return accumulatedHash
		^ (partialHash
		+ HASH_ADDITION_ELEMENT
		+ (accumulatedHash << HASH_LEFT_SHIFT_DEGREE)
		+ (accumulatedHash >> HASH_RIGHT_SHIFT_DEGREE));
}

unsigned int Hashable::getHash()
{
	if (!shouldHashBeMemoized)
		return calculateHash();

	if (!wasHashEvaluated)
		memoizeHash(calculateHash());

	return memoizedHash;
}

unsigned int Hashable::getHashWithoutMemoizing() const
{
	return calculateHash();
}

void Hashable::signalizePossibleChangeInHash()
{
	wasHashEvaluated = false;
}

void Hashable::forcelyMemoizeHash(unsigned int hashToSet)
{
	memoizedHash = true;
	memoizedHash = hashToSet;
}
