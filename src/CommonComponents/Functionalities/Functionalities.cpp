#include "Functionalities.h"

template<typename T>
inline void clearVectorOfPointers(std::vector<T*> vectorOfPointers)
{
	for (T* pointerToDelete : vectorOfPointers)
		delete pointerToDelete;
	vectorOfPointers.clear();
}