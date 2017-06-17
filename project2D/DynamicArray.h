#pragma once
#include <cstring>


template <class T>
class DynamicArray
{
public:

	typedef T* iterator;
	typedef const T* const_iterator;

	DynamicArray(int capacity = 10)
	{
		//m_capacity = default
		m_capicity = capacity;
		//data = new templated array of Capacity number of empty cells
		m_data = new T[capacity];
		//number of elements in array set to 0
		m_size = 0;
	}

	~DynamicArray()
	{
		//delete cells in m_data
		delete[] m_data;
	}

	//Add "element" to end of array
	void push_back(T element)
	{
		//number of elements in array == the number of arrays cells
		if (m_size == m_capicity)
		{
			//then call expand
			Expand();
		}
		//else pointer to array data[number of elements in array] = the new element
		m_data[m_size] = element;
		//imcrement m_size by 1
		m_size++;
	}

	int find(T element)
	{
		for (int i = 0; i < size(); i++)
		{
			if (m_data[i] == element)
			{
				return i;
			}
		}
		return -1;
	}
	
	iterator erase(iterator element)
	{
		iterator newElement = nullptr;

		for(int i = 0; i < size(); i++)
		{
			if (&m_data[i] == element)
				newElement = m_data + i;
		}

		if (newElement != nullptr)
		{
			removeByIndex((newElement - m_data) / sizeof(T));
		}

		return element;
	}

	bool empty()
	{
		if (m_size == 0)
			return true;
	}

	//begin itarator
	T* begin()
	{
		return &m_data[0];
	}

	//end iterator
	T* end()
	{
		return &m_data[m_size];
	}

	T pop_back()
	{
		return m_data[--m_size];
	}

	bool removeByValue(T element)
	{
		for (int i = 0; i < m_size; i++)
		{
			if (m_data[i] == element)
			{
				removeByIndex(i);
				return true;
			}
		}
		return false;
	}

	void sort() 
	{
		int i, j;
	    T key;

		for (j = 1; j < size(); j++)    // Start with 1 (not 0)
		{
			key = m_data[j];
			for (i = j - 1; (i >= 0) && (m_data[i] > key); i--)
			{
				m_data[i + 1] = m_data[i];
			}
			m_data[i + 1] = key;    //Put key into its proper location
		}
		return;
	}

	void resize(int capicity)
	{
		int newCapacity;
		T * newData;

		newCapacity = capicity;

		newData = new T[newCapacity];

		std::memcpy(newData, m_data, newCapacity * sizeof(T));

		delete[] m_data;

		m_capicity = newCapacity;

		m_data = newData;
	}

	int getCapacity()
	{
		return m_capicity;
	}

	void removeByIndex(const int index)
	{
		m_size--;
		for (int i = index; i < m_size; i++)
		{
			m_data[i] = m_data[i + 1];
		}
	}

	void clear()
	{
	    m_size = 0;
	}

	//access first element;
	T front()
	{
		return m_data[0];
	}
	//access last element;
	T back()
	{
		return m_data[m_size - 1];
	}

	int size()
	{
		//return number of elements in array for use else where
		return m_size;
	}

	//overload index operator
	T& operator[](const int index)
	{
		//return a index in the array
		return m_data[index];
	}

private:

	void Expand()
	{
		//newCapacity = the new amount of arrays empty cells
		int newCapacity = m_capicity * 2;
		//newData = new templated array of newCapacity number of empty cells
		T * newData = new T[newCapacity];

		//copy old array element into new array
		std::memcpy(newData, m_data, newCapacity * sizeof(T));

		//delete the old arrays cells
		delete[] m_data;

		//setting the current capacity to the new capacity
		m_capicity = newCapacity;
		//setting current data to the new data
		m_data = newData;
	}

	//pointer to array data
	T * m_data;
	//number of elements in array
	int m_size;
	//arrays empty cells
	int m_capicity;
};

