#pragma once

class Hashable
{
public:

	virtual unsigned int getHash() = 0;
	virtual bool equals(const Hashable& other) const = 0;
};
