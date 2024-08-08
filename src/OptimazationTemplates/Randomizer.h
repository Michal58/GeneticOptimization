#pragma once

class Randomizer
{
public:

	virtual void reset() = 0;
	virtual int randInRange(int inclusiveLowerBound, int exclusiveRange) = 0;
	virtual int randInRange(int exclusiveRange) = 0;
	virtual double chanceRand() = 0;

};

