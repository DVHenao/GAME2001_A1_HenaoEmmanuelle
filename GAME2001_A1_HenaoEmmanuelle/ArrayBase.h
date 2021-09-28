#pragma once

template <class T>
class ArrayBase
{
public:
	ArrayBase() :
		m_array(NULL), m_maxSize(0), m_growSize(2), m_numElements(0)
	{
	
	}


	//functions
	int GetSize()
	{
		return m_numElements;
	}
	int GetMaxSize()
	{
		return m_maxSize;
	}
	int GetGrowSize()
	{
		return m_growSize;
	}
	int SetGrowSize(int val)
	{
		assert(val >= 0);
		m_growSize = val;
	}



private:

	T* m_array;			// Pointer to the beginning of the array

	int m_maxSize;		// Maximum size of the array
	int m_growSize;		// Amount the array can grow through expansion
	int m_numElements;	// Number of items currently in my array



};