#pragma once
#include <iostream>
#include <unordered_set>
#include <vector>

template <typename IterablePointers, typename PointerType>
void clearIterablePointers(IterablePointers pointersContainer);

template<typename T>
void clearVectorOfPointers(std::vector<T*> vectorOfPointers);

template<typename T>
void clearUnorderedSetOfPointers(std::unordered_set<T*> setOfPointers);

template<typename T, typename U>
bool isInstanceOf(U* const supposedDerivedClass);

template <typename T, typename U>
bool isInstanceOf(const U& supposedDerivedClass);


// defininitons of template functions - I dedcided it is a better solution than defining it in cpp file


template<typename IterablePointers, typename PointerType>
inline void clearIterablePointers(IterablePointers pointersContainer)
{
	for (PointerType* pointerToDelete : pointersContainer)
		delete pointerToDelete;
	pointersContainer.clear();
}

template<typename T>
inline void clearVectorOfPointers(std::vector<T*> vectorOfPointers)
{
	clearIterablePointers<std::vector<T*>, T>(vectorOfPointers);
}

template<typename T>
inline void clearUnorderedSetOfPointers(std::unordered_set<T*> setOfPointers)
{
	clearIterablePointers<std::unordered_set<T*>, T>(setOfPointers);
}

template<typename T, typename U>
inline bool isInstanceOf(const U* const supposedDerivedClass)
{
	return dynamic_cast<const T*>(supposedDerivedClass) != nullptr;
}

template<typename T, typename U>
inline bool isInstanceOf(const U& supposedDerivedClass)
{
	return isInstanceOf<const T>(&supposedDerivedClass);
}
