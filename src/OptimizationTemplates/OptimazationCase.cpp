#include "OptimizationCase.h"

DomainIterator* const DomainIterator::FINISHED_ITERATOR_SINGLETON = new FinishedIterator;

void DomainIterator::initializeStandardIterationProtocolIfNeeded()
{
	if (!isIterationProtocolInitialized)
	{
		isIterationProtocolInitialized = true;
		isCurrentValueEndInvalidValue = !hasNext();
		if (isCurrentValueEndInvalidValue)
			return;
		++(*this);
	}
}

void DomainIterator::throwExceptionIfTriedToDoAnActionOnFinishedIterator()
{
	if (isCurrentValueEndInvalidValue)
		next();
}

void DomainIterator::prepeareNonConstMethodOfStandardIteratorProtocolToRun()
{
	initializeStandardIterationProtocolIfNeeded();
	throwExceptionIfTriedToDoAnActionOnFinishedIterator();
}

DomainIterator& DomainIterator::getFinishedIteratorInstance()
{
	return *FINISHED_ITERATOR_SINGLETON;
}

DomainIterator::DomainIterator() :
	currentElement(CURRENT_ELEMENT_DEFAULT_VALUE),
	isIterationProtocolInitialized(false),
	isCurrentValueEndInvalidValue(false) {}

DomainIterator::~DomainIterator() = default;

DomainIterator::reference DomainIterator::operator*()
{
	prepeareNonConstMethodOfStandardIteratorProtocolToRun();

	return currentElement;
}

DomainIterator::pointer DomainIterator::operator->()
{
	prepeareNonConstMethodOfStandardIteratorProtocolToRun();

	return &currentElement;
}

DomainIterator& DomainIterator::operator++()
{
	prepeareNonConstMethodOfStandardIteratorProtocolToRun();

	DomainIterator& iteratorToReturn = *this;

	if (!this->hasNext())
		iteratorToReturn.isCurrentValueEndInvalidValue = true;
	else
		iteratorToReturn.currentElement = this->next();

	return iteratorToReturn;
}

bool DomainIterator::operator==(const DomainIterator& other) const
{
	return this->isCurrentValueEndInvalidValue 
		&& other.isCurrentValueEndInvalidValue;
}

bool DomainIterator::operator!=(const DomainIterator& other) const
{
	return !(*this == other);
}

DomainIterationPerformer DomainIterator::begin()
{
	return DomainIterationPerformer(*this);
}

const std::string DomainIterator::OUT_OF_RANGE_MESSAGE = "Next value was out of range";

DomainIterationPerformer DomainIterator::end()
{
	return DomainIterationPerformer(DomainIterator::getFinishedIteratorInstance());
}

void FinishedIterator::causeInitializationAsStarndardIterator()
{
	initializeStandardIterationProtocolIfNeeded();
}

FinishedIterator::FinishedIterator():
	DomainIterator()
{
	causeInitializationAsStarndardIterator();
}

bool FinishedIterator::hasNext() const
{
	return false;
}

bool FinishedIterator::hasNext(int iOffset) const
{
	return false;
}

int FinishedIterator::next()
{
	throw std::out_of_range(OUT_OF_RANGE_MESSAGE);
}

int FinishedIterator::next(int iOffset)
{
	throw std::out_of_range(OUT_OF_RANGE_MESSAGE);
}

DomainIterationPerformer::DomainIterationPerformer(DomainIterator& actualIterator):
	DomainIterator(actualIterator),
	actualIterator(actualIterator) {}

bool DomainIterationPerformer::hasNext() const
{
	return actualIterator.hasNext();
}

bool DomainIterationPerformer::hasNext(int iOffset) const
{
	return actualIterator.hasNext(iOffset);
}

int DomainIterationPerformer::next()
{
	return actualIterator.next();
}

int DomainIterationPerformer::next(int iOffset)
{
	return actualIterator.next(iOffset);
}
