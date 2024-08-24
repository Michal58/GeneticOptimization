#pragma once
#include "Hashable.h"
#include "../Functionalities/Functionalities.h"

#define INVALID_HASHER_USAGE "Tried to use hasher with no hashable object"

template<typename T>
class PointerBaseHasher
{
public:

	PointerBaseHasher();

	unsigned int  operator()(T* const& hashableObj) const;
	bool operator()(T const* firstHashableObj, T const* secondHashableObj) const;
};

template <typename T>
using PointerBaseHashablesComparator = PointerBaseHasher<T>;


// methods implementation

template<typename T>
inline PointerBaseHasher<T>::PointerBaseHasher()
{
	static_assert(std::is_base_of<Hashable, T>::value, INVALID_HASHER_USAGE);
}

template<typename T>
inline unsigned int PointerBaseHasher<T>::operator()(T* const& hashableObj) const
{
	return hashableObj->getHash();
}

template<typename T>
inline bool PointerBaseHasher<T>::operator()(T const* firstHashableObj, T const* secondHashableObj) const
{
	return firstHashableObj->equals(*secondHashableObj);
}
