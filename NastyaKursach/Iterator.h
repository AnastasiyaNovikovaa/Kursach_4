#pragma once
#include <cstddef>

template <class T>
class Iterator
{
public:
	virtual T next() = 0; // index of data and data
	virtual bool has_next() = 0;
};