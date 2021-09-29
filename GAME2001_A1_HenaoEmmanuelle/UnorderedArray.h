#pragma once
#include <cassert>
#include "ArrayBase.h"
#include <iostream>

template<class T>
class UnorderedArray: public ArrayBase<T>
{
public:
	// Constructor
	UnorderedArray(int size, int growBy = 2)
	{
		if (size)	// Is this a legal size for an array?
		{
			UnorderedArray::SetMaxSize(size);
			m_array = new T[UnorderedArray::GetMaxSize()];		// Dynamically allocating an array to m_maxSize
			memset(m_array, 0, sizeof(T) * UnorderedArray::GetMaxSize());	// Explicitly set 0 to all elements in the array

			//m_growSize = ((growBy > 0) ? growBy : 0);
			UnorderedArray::SetGrowSize(growBy);
		}
	}
	// Destructor
	~UnorderedArray()
	{
		if (m_array != nullptr)
		{
			delete[] m_array;
			m_array = nullptr;
		}
	}
	// Insertion
	// Fast insertion for UnorderedArray -- Big-O is O(1)
	void push(T val)
	{

		assert(m_array != nullptr); // Debugging purposes

		if (UnorderedArray::GetSize() >= UnorderedArray::GetMaxSize())	// Check if the array has to expand to accommodate the new data.
		{
			Expand();
		}

		// My array has space for a new value. Let's add it!
		bool duplicate = 0;
		for (int i = 0; i < UnorderedArray::GetSize(); i++)
		{
			if (m_array[i] == val)
			{
				duplicate = 1;
				std::cout << " DUPLICATE DETECTED: " << m_array[i] << std::endl;
			}
		}
		if (duplicate == 0)
		{
			m_array[UnorderedArray::GetSize()] = val;
			UnorderedArray::SetSize(UnorderedArray::GetSize() + 1);
		}
	}
	
	
	void remove(int index)
	{
		assert(m_array != nullptr);

		if (index >= UnorderedArray::GetSize())
		{
			// I am trying to remove something outside of the bounds of the array
			return;	// <-- Maybe could do some form of exception handling
		}

		for (int i = index; i < UnorderedArray::GetSize(); i++)
		{
			// Start at the index we want to remove.
			// Shift everything after index back by one.
			if (i + 1 < UnorderedArray::GetSize())
			{
				m_array[i] = m_array[i + 1];
			}
		}
		UnorderedArray::SetSize(UnorderedArray::GetSize() - 1);
	}
	// Searching
	// Linear Search
	int search(T val)
	{
		assert(m_array != nullptr);

		// Brute-force Search
		for (int i = 0; i < UnorderedArray::GetSize(); i++)
		{
			if (m_array[i] == val)
			{
				return i;	// Return the index of where the item is located in the array
			}
		}

		return -1;
	}
	// Overloaded [] operator
	T& operator[](int index)
	{
		assert(m_array != nullptr && index < UnorderedArray::GetSize());
		return m_array[index];
	}
	
private:
	// Private functions
		// Expansion
	bool Expand()
	{
		if (UnorderedArray::GetGrowSize() <= 0)
		{
			// LEAVE!
			return false;
		}

		// Create the new array
		T* temp = new T[UnorderedArray::GetMaxSize() + UnorderedArray::GetGrowSize()];
		assert(temp != nullptr);

		// Copy the contents of the original array into the new array
		memcpy(temp, m_array, sizeof(T) * UnorderedArray::GetMaxSize());

		// Delete the old array
		delete[] m_array;

		// Clean up variable assignments
		m_array = temp;
		temp = nullptr;

		UnorderedArray::SetMaxSize(UnorderedArray::GetMaxSize() + UnorderedArray::GetMaxSize());
		UnorderedArray::SetGrowSize(2);

		std::cout << "Size of m_array is " << UnorderedArray::GetMaxSize() << std::endl;
		return true;
		
	}
private:
	// Private Variables
	T* m_array;			// Pointer to the beginning of the array
};