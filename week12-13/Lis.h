#pragma once
// Lis.h
#ifndef GUARD_LIS_H
#define GUARD_LIS_H

#include <memory>
#include <iostream>

template <class T> class Node {
	public:
	T value;
	Node<T>* next;
	Node<T>* prev;

	// 생성자
	Node() : value(0), next(0), prev(0) {} //초기화
	Node(T t) : value(t), next(0), prev(0) {} //값이 있으면....
};
template <class T> class NodeItr {
public:
	NodeItr& operator++();
	NodeItr& operator--();
	NodeItr operator++(int);
	NodeItr operator--(int);
	T& operator*() const { return node->value; } //포인터
	bool operator!=(const NodeItr& rhs) const { return node != rhs.node; }

	// 생성자
	NodeItr(Node<T>* n) : node(n) {}

private:
	Node<T>* node;
};

template <class T> NodeItr<T>& NodeItr<T>::operator++() {
	node = node->next;
	return *this;
}

template <class T> NodeItr<T>& NodeItr<T>::operator--() {
	node = node->prev;
	return *this;
}

template <class T> NodeItr<T> NodeItr<T>::operator++(int) {
	NodeItr temp = *this;
	++(*this);
	return temp;
}

template <class T> NodeItr<T> NodeItr<T>::operator--(int) {
	NodeItr temp = *this;
	--(*this);
	return temp;

	node = node->prev;
	return *this;
}

template <class T> class Lis {
public:

	typedef NodeItr<T> iteratror;
	typedef const NodeItr<T> const_iterator;
	typedef size_t size_type;

	//생성하고 초기화
	Lis() : b(0), e(0), s(0) {};
	explicit Lis(size_type n, const T& t = T()) { create(n, t); }
	Lis(const Lis& v) { create(v.begin(), v.end()); }
	Lis& operator=(const Lis& rhs);
	~Lis() { uncreate(); }
	//멤버 함수
	void push_back(const T& t);
	size_type size() const { return s; }
	//반복자 함수
	iteratror begin() {return b;}
	const_iterator begin() const { return b; }

	iteratror end() { return e; }
	const_iterator end() const { return e; }

	//소멸 함수
	void clear() { uncreate(); }
	bool empty() const { return s == 0; }

private:
	Node<T>* b; // 시작의 포인터
	Node<T>* e;//끝의 포인터
	size_type s; // 크기

	//메모리 할당하고 Lis 배열 초기화
	void create(size_type, const T&);
	void create(const_iterator, const_iterator);

	//Lis 배열 소멸하고 메모리 해제
	void uncreate();
};

template <class T>
void Lis<T>::push_back( const T& t) {
	Node<T>* node = new Node<T>(t);

	if (s == 0) 
		b = e = node;
	else {
		e->next = node;
		node->prev = e;
		e = node;
}
	s++;

}
//사이즈 + 값의 생성자
template <class T>
void Lis<T>::create(size_type s, const T& t) {
	for (size_t i = 0; i < s; i++)
		push_back(t);
}

// b와 e 반복자를 사용하여 사본 만드는 create()
template <class T>
void Lis<T>::create(const_iterator b, const_iterator e) {
	while (b != e) {
		push_back(*b++);
	}
}

// 소멸
template <class T>
void Lis<T>::uncreate() {
	Node<T>* node = e;
	while (node != b) {
		Node<T>* node_delete = node;
		node = node->prev;
		delete node_delete;
	
	
	}

	b = e = 0;
	s = 0;
}

// NodeItr<T>에 대한 operator<< 오버로드 추가
template <typename T>
std::ostream& operator<<(std::ostream& os, const typename Lis<T>::iteratror& it) {
    os << &(*it); // 또는 os << static_cast<const void*>(&(*it)); 로 포인터 주소 출력
    return os;
}

template <class T>
Lis<T>& Lis<T>::operator=(const Lis& rhs) {
    if (this != &rhs) {
        uncreate();
        create(rhs.begin(), rhs.end());
    }
    return *this;
}

#endif
