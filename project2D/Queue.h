#pragma once

template <class T>
struct Node {

	Node(T value) : m_next(nullptr), m_previous(nullptr) {
		m_value = value;
	}

	void setData(T value) {
		m_value = value;
	}

	void setNextNode(ListNode<T>* next) {
		m_next = next;
	}

	void setPreviousNode(ListNode<T>* previous) {
		m_previous = previous;
	}

	T getData() {
		return m_value;
	}

	Node<T>* getNextNode() {
		return m_next;
	}

	Node<T>* getPreviousNode() {
		return m_previous;
	}

	T m_value;
	Node* m_next;
	Node* m_previous;
};


template <class T>
class Queue
{
public:
	Queue() {

	}

	~Queue() {}

	void push_back(T value) {
		Node<T>* N = new Node<T>();
		++m_size;
		N->setNextNode(nullptr);
		N->setPreviousNode(n_last);
		N->setData(value);

		if (n_first == nullptr) {
			n_first = N;
		}
		if (n_last != nullptr) {
			n_last->setNextNode(N);
		}

		n_last = N;
	}

	void pop_front(){
		// pushFront( value ) – add a new value to the front of the list
		Node<T>* N = new Node<T>();
		++m_size;
		N->setNextNode(n_first);
		N->setPreviousNode(nullptr);
		N->setData(value);

		if (n_last == nullptr) {
			n_last = N;
		}
		if (n_first != nullptr) {
			n_first->setPreviousNode(N);
		}

		m_first = N;
	}

	T front() {
		// front() – return the first element by value, assert if no elements
		if (n_first != nullptr)
			return n_first->getData();
		else
			assert("no value found");
	}

	T back() {
		// back() – return the last element by value, assert if no elements
		if (n_last != nullptr)
			return n_last->getData();
		else
			assert("no value found");
	}

	bool empty() {
		return m_size == 0;
	}

	int size() {
		return m_size;
	}

private:
	int m_size;
	Node* n_first;
	Node* n_last;
};

