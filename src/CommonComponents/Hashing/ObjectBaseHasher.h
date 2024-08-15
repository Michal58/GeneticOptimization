#pragma once
#include "PointerBaseHasher.h"

template<typename T>
class ObjectBaseHasher
{
public:

	ObjectBaseHasher();

	unsigned int  operator()(const T& hashableObj) const;
	bool operator()(const T& firstHashableObj, const T& secondHashableObj) const;
};

template<typename T>
using ObjectBaseHashablesComparator = ObjectBaseHasher<T>;

//methods implementation

template<typename T>
inline ObjectBaseHasher<T>::ObjectBaseHasher()
{
	static_assert(std::is_base_of<Hashable, T>::value, INVALID_HASHER_USAGE);
}

template<typename T>
inline unsigned int ObjectBaseHasher<T>::operator()(const T& hashableObj) const
{
	return hashableObj.getHash();
}

template<typename T>
inline bool ObjectBaseHasher<T>::operator()(const T& firstHashableObj, const T& secondHashableObj) const
{
	return firstHashableObj.equals(secondHashableObj);
}
