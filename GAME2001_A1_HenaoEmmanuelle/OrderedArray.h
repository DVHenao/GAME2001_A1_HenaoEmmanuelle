#pragma once
#include <cassert>
#include "ArrayBase.h"
#include <iostream>

template<class T>
class OrderedArray: public ArrayBase<T>
{
public:
	// Constructor
	OrderedArray(int size, int growBy = 2)
	{
		if (size)	// Is this a legal size for an array?
		{
			OrderedArray::SetMaxSize(size);
			m_array = new T[OrderedArray::GetMaxSize()];		// Dynamically allocating an array to m_maxSize
			memset(m_array, 0, sizeof(T) * OrderedArray::GetMaxSize());	// Explicitly set 0 to all elements in the array

			//m_growSize = ((growBy > 0) ? growBy : 0);
			OrderedArray::SetGrowSize(growBy);
		}
	}
	// Destructor
	~OrderedArray()
	{
		if (m_array != nullptr)
		{
			delete[] m_array;
			m_array = nullptr;
		}
	}
	// Insertion -- Big-O = O(N)
	void push(T val)
	{

		assert(m_array != nullptr);

		if (OrderedArray::GetSize() >= OrderedArray::GetMaxSize())
		{
			Expand();
		}


		// CHECK FOR DUPLICATE
		bool duplicate = 0;
		if (OrderedArray::GetDuplicate() == 0)
		for (int i = 0; i <= OrderedArray::GetSize(); i++)
		{
			if (m_array[i] == val)
			{
				duplicate = 1;
				std::cout << " DUPLICATE DETECTED: " << m_array[i] << std::endl;
			}
		}
		
		if (duplicate == 0)
		{
			int i, k;	// i - Index to be inserted. k - Used for shifting purposes
			// Step 1: Find the index to insert val
			for (i = 0; i < OrderedArray::GetSize(); i++)
			{
				if (m_array[i] > val)
				{
					break;
				}
			}

			// Step 2: Shift everything to the right of the index(i) forward by one. Work backwards
			for (k = OrderedArray::GetSize(); k > i; k--)
			{
				m_array[k] = m_array[k - 1];
			}

			// Step 3: Insert val into the array at index
			m_array[i] = val;

			OrderedArray::SetSize(OrderedArray::GetSize()+1);
		}
		// return i;
	}
	
	void remove(int index)
	{
		assert(m_array != nullptr);

		if (index >= OrderedArray::GetSize())
		{
			// I am trying to remove something outside of the bounds of the array
			return;	// <-- Maybe could do some form of exception handling
		}

		for (int i = index; i < OrderedArray::GetSize(); i++)
		{
			// Start at the index we want to remove.
			// Shift everything after index back by one.
			if (i + 1 < OrderedArray::GetSize())	// Confines the loop into the array
			{
				m_array[i] = m_array[i + 1];
			}
		}
		OrderedArray::SetSize(OrderedArray::GetSize()-1);
	}
	// Searching
	// Binary Search
	int search(T searchKey)
	{
		assert(m_array != nullptr);

		// Helper variables.
		int lowerBound = 0;
		int upperBound = OrderedArray::GetSize() - 1;
		int current = 0;

		while (1)	// <-- Replaced with recursion
		{
			current = (lowerBound + upperBound) >> 1;	// Preview of bitwise operatrions. Divides by 2

			// Binary search steps:
			// Step 1: Check if the middle is the value we are looking for.
			if (m_array[current] == searchKey)
			{
				// Found the item in the middle of the array. Return the index
				return current;
			}
			// Step 2: Check that we've exhausted all options. Can't find the item
			else if (lowerBound > upperBound)
			{
				return -1;
			}
			// Step 3: Check which half of the array the value is in.
			else
			{
				if (m_array[current] < searchKey)
				{
					lowerBound = current + 1;	// Value may be in the upper half
				}
				else
				{
					upperBound = current - 1;	// Value may be in the lower half
				}
			}
		}

		return -1;	// Catch all return from danger.
	}
	// Overloaded [] operator
	T& operator[](int index)
	{
		assert(m_array != nullptr && index < OrderedArray::GetSize());
		return m_array[index];
	}
	
	
private:
	// Private functions
		// Expansion
	bool Expand()
	{
		if (OrderedArray::GetGrowSize() <= 0)
		{
			// LEAVE!
			return false;
		}

		// Create the new array
		T* temp = new T[OrderedArray::GetMaxSize() + OrderedArray::GetGrowSize()];
		assert(temp != nullptr);

		// Copy the contents of the original array into the new array
		memcpy(temp, m_array, sizeof(T) * OrderedArray::GetMaxSize());

		// Delete the old array
		delete[] m_array;

		// Clean up variable assignments
		m_array = temp;
		temp = nullptr;

		//m_maxSize += OrderedArray::GetGrowSize();
		OrderedArray::SetMaxSize(OrderedArray::GetMaxSize() + OrderedArray::GetMaxSize());
		OrderedArray::SetGrowSize(2);

		std::cout << "Size of m_array is " << OrderedArray::GetMaxSize() << std::endl;
		return true;
	}
private:
	// Private Variables
	T* m_array;			// Pointer to the beginning of the array

	
};