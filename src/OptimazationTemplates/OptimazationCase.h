#pragma once
#include <iostream>
#include <vector>

class DomainIterationPerformer;

class DomainIterator {

	static DomainIterator* const FINISHED_ITERATOR_SINGLETON;
	
	const static int CURRENT_ELEMENT_DEFAULT_VALUE = 0;
	int currentElement;
	bool isIterationProtocolInitialized;
	bool isCurrentValueEndInvalidValue;

protected:

	void initializeStandardIterationProtocolIfNeeded();
	void throwExceptionIfTriedToDoAnActionOnFinishedIterator();
	void prepeareNonConstMethodOfStandardIteratorProtocolToRun();

public:

	static const std::string OUT_OF_RANGE_MESSAGE;
	static DomainIterator& getFinishedIteratorInstance();

	DomainIterator();
	virtual ~DomainIterator();

	virtual bool hasNext() const = 0;
	virtual bool hasNext(int iOffset) const = 0;

	virtual int next() = 0;
	virtual int next(int iOffset) = 0;

	using iterator_category = std::input_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = int;
	using pointer = int*;
	using reference = int&;

	reference operator*();
	pointer operator->();
	DomainIterator& operator++();
	bool operator==(const DomainIterator& other) const;			// Only iterators which haven't next elements are equal
	bool operator!=(const DomainIterator& other) const;

	DomainIterationPerformer begin();
	DomainIterationPerformer end();
};

class DomainIterationPerformer :public DomainIterator
{

	DomainIterator& actualIterator;

public:

	DomainIterationPerformer(DomainIterator& actualIterator);

	bool hasNext() const override;
	bool hasNext(int iOffset) const override;
	int next() override;
	int next(int iOffset) override;

};

class FinishedIterator: public DomainIterator {

	void causeInitializationAsStarndardIterator();

public:

	FinishedIterator();
	bool hasNext() const override;
	bool hasNext(int iOffset) const override;
	int next() override;
	int next(int iOffset) override;
};

class OptimazationCase
{
public:

	virtual double evaluateFitness(std::vector<int>& solution) = 0;
	virtual int getCountOfDimensions() = 0;
	virtual int getCountOfDomainValues(int indexOfDimension) = 0;

	virtual std::unique_ptr<DomainIterator> getDomain(int indexOfDimension) = 0;
	virtual int getValueOutOfAllDomains() = 0;
};

