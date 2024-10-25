#ifndef HEAP_H_
#define HEAP_H_

#include <string>
#include <sstream>
#include "exception.h"
#include <iostream>

template <class T>
class Heap {
    private:
    T *data;
	int length;
	int count;
	int parent(int);
	int left(int);
	int right(int);
	void heapify(int);
	void swap(int, int);

    public:
    Heap(int);
    void push(T);
    void pop();
    T top();
    bool empty();
    bool full();
    int size();
	std::string toString();
};

template <class T>
Heap<T>::Heap(int sze)  {
	length = sze;
	data = new T[length];
	if (data == 0) {
		throw OutOfMemory();
	}
	count = 0;
}

template <class T>
void Heap<T>::push(T val)  {
	int pos;
	if (full()) {
		throw Overflow();
	}
	pos = count;
	count++;
	while (pos > 0 && val < data[parent(pos)]) {
		data[pos] = data[parent(pos)];
		pos = parent(pos);
	}
	data[pos] = val;
}

template <class T>
bool Heap<T>::full() {
	return (count == length);
}
template <class T>
bool Heap<T>::empty() {
	return (count == 0);
}
template <class T>
int Heap<T>::parent(int pos) {
	return (pos - 1) / 2;
}

template <class T>
int Heap<T>::left(int pos) {
	return ((2 * pos) + 1);
}

template <class T>
int Heap<T>::right(int pos) {
	return ((2 * pos) + 2);
}

template <class T>
std::string Heap<T>::toString() {
	std::stringstream aux;
	aux << "[";	for (unsigned int i = 0; i < count; i++) {
		if (i != 0) {
			aux << " ";
		} aux << data[i];
	} aux << "]";
	return aux.str();
}

#endif 