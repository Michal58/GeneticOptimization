#pragma once
#include <iostream>
#include <vector>

template<typename T>
void clearVectorOfPointers(std::vector<T*> vectorOfPointers);

template<typename T, typename U>
bool isInstanceOf(U* const supposedDerivedClass);

template <typename T, typename U>
bool isInstanceOf(const U& supposedDerivedClass);


// defininitons of template functions - I dedcided it is a better solution than defining it in cpp file

template<typename T>
inline void clearVectorOfPointers(std::vector<T*> vectorOfPointers)
{
	for (T* pointerToDelete : vectorOfPointers)
		delete pointerToDelete;
	vectorOfPointers.clear();
}

template<typename T, typename U>
inline bool isInstanceOf(U* const supposedDerivedClass)
{
	return dynamic_cast<T*>(supposedDerivedClass) != nullptr;
}

template<typename T, typename U>
inline bool isInstanceOf(const U& supposedDerivedClass)
{
	return isInstanceOf<T>(&supposedDerivedClass);
}
