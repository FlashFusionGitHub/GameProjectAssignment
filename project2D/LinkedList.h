#pragma once
#include <assert.h>

template <class T>
class ListNode
{
public:
	ListNode() {}

	ListNode(T value) : m_next(nullptr), m_previous(nullptr) {
		m_value = value;
	}
	~ListNode() {}

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

	ListNode<T>* getNextNode() {
		return m_next;
	}

	ListNode<T>* getpreviousNode() {
		return m_previous;
	}

private:
	ListNode<T>* m_next;
	ListNode<T>* m_previous;
	T m_value;
};


template <class T>
class LinkedList
{
public:

	class Iterator {
	public:
		Iterator() {}
		Iterator(ListNode<T>* x) :p(x) {}
		Iterator(const Iterator& it) : p(it.p) {}
		Iterator& operator++() { p = p->getNextNode(); return *this; }
		Iterator& operator--() { p = p->getpreviousNode(); return *this; }
		Iterator operator++(int) { Iterator tmp(*this); operator++(); return tmp; }
		bool operator==(const Iterator& rhs) const { return p == rhs.p; }
		bool operator!=(const Iterator& rhs) const { return p != rhs.p; }
		ListNode<T>& operator*() { return *p; }

	private:
		ListNode<T>* p;
	};

	LinkedList() {
		m_first = nullptr;
		m_last = nullptr;
	}
	~LinkedList() {}

	void pushFront(T value) {
		// pushFront( value ) – add a new value to the front of the list
		ListNode<T>* N = new ListNode<T>();
		++m_size;
		N->setNextNode(m_first);
		N->setPreviousNode(nullptr);
		N->setData(value);

		if (m_last == nullptr) {
			m_last = N;
		}
		if (m_first != nullptr) {
			m_first->setPreviousNode(N);
		}

		m_first = N;
	}

	void pushBack(T value) {
		// pushBack( value ) – add a new value to the back of the list
		ListNode<T>* N = new ListNode<T>();
		++m_size;
		N->setNextNode(nullptr);
		N->setPreviousNode(m_last);
		N->setData(value);

		if (m_first == nullptr) {
			m_first = N;
		}
		if (m_last != nullptr) {
			m_last->setNextNode(N);
		}

		m_last = N;
	}

	void insert(Iterator it, T value) {
		// insert( Iterator, value ) – add a new value one-past the specified iterator location
		ListNode<T>* temp = new ListNode<T>(value);
		temp->setNextNode((*it).getNextNode());
		temp->getNextNode()->setPreviousNode(temp);
		(*it).setNextNode(temp);
		temp->setPreviousNode(&(*it));
		m_size++;
	}

	Iterator begin() {
		// begin() – return an iterator to the first element
		return Iterator(m_first);
	}

	Iterator end() {
		// end() – return an iterator to a null element
		return Iterator(nullptr);
	}

	Iterator firstIterator() {
		return Iterator(m_first);
	}

	Iterator lastIterator() {
		return Iterator(m_last);
	}


	T first() {
		// first() – return the first element by value, assert if no elements
		if (m_first != nullptr)
			return m_first->getData();
		else
			assert("no value found");
	}

	T last() {
		// last() – return the last element by value, assert if no elements
		if (m_last != nullptr)
			return m_last->getData();
		else
			assert("no value found");
	}

	T count() {
		// count() – return how many elements exist in the list
		return m_size;
	}

	void erase(Iterator it) {
		// erase( iterator ) – remove an element by its iterator
		if (&(*it) == m_first) { popFront(); }
		else if (&(*it) == m_last) { popBack(); }
		else {
			ListNode<T>* temp = &(*it);
			temp->getpreviousNode()->setNextNode(temp);
			temp->getNextNode()->setPreviousNode(temp);
		}
		--m_size;
	}

	bool remove(T element) {
		// remove( value ) – remove all elements with matching value
		for (Iterator it = begin(); it != end(); ++it) {
			if (it = element)
				--m_size;
			erase(it);
		}
	}

	void popBack() {
		// popBack() – remove the last element
		ListNode<T>* temp = m_last;

		m_last = m_last->getpreviousNode();

		delete temp;

		--m_size;
	}

	void popFront() {
		// popFront() – remove the first element
		ListNode<T>* temp = m_first;

		m_first = m_first->getNextNode();

		delete temp;

		--m_size;
	}

	bool empty() {
		// empty() – return a Boolean, true if the list is empty, false otherwise
		return m_size == 0;
	}

	void clear() {
		//* clear() – remove all elements from the list
		while (m_first != nullptr) { popFront(); }
		m_size = 0;
	}

private:
	int m_size = 0;
	ListNode<T>* m_first;
	ListNode<T>* m_last;
};

