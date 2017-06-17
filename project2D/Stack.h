#pragma once
template <class T>
class Stack
{
public:
	//take in a stack size (capacity)
	Stack(int capacity) {
		m_capacity = capacity;
		//SET data to array of capacity elements
		m_data = new T[m_capacity];
		//SET size to capacity
		m_size = m_capacity;
		//SET top to -1
		m_top = -1;
	}

	~Stack() {
		delete[] m_data;
	}

	int size() {
		return m_size;
	}

	bool empty() {

		return m_size == 0;
	}

	void push(T value) {
		//INCREMENT top by 1
		m_top++;

		//IF top equals size -1
		if (m_top == m_size - 1)
		{
			//resize data array
			int newCapacity = m_capacity * 2;
			//SET size to new size
			m_size = newCapacity;

			T * newData = new T[newCapacity];

			memcpy(newData, m_data, newCapacity * sizeof(T));

			delete[] m_data;

			m_capacity = newCapacity;
			m_data = newData;
		}

		//SET data[top] to value
		m_data[m_top] = value;
	}

	void pop() {
		if (m_top >= 0) {
			m_data[m_top] = NULL;
			m_top--;
		}
	}

	T top() {
		if (m_top < 0)
			return NULL;
		else
			return m_data[m_top];
	}


private:
	int m_top;
	int m_size;
	int m_capacity;
	T * m_data;
};

