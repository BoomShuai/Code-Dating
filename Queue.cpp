#ifndef QUEUE_CPP
#define QUEUE_CPP

#include "Queue.h"
using namespace std;

template <typename T>
Queue<T>::Queue() : front(0), rear(0), maxSize(MAX), count(0) {
    data = new T[maxSize];
}

template <typename T>
Queue<T>::~Queue() {
    delete[] data;
}

template <typename T>
void Queue<T>::enqueue(const T& item) {
    if (count == maxSize) {
        expand(); 
    }
    data[rear] = item;
    rear = (rear + 1) % maxSize; 
    ++count;
}


template <typename T>
void Queue<T>::dequeue() {
    if (isEmpty()) {
        cerr << "Error: Queue is empty. Cannot dequeue.\n";
        exit(EXIT_FAILURE); 
    }
    front = (front + 1) % maxSize; 
    --count;
}

template <typename T>
T& Queue<T>::atFront() {
    if (isEmpty()) {
        cerr << "Error: Queue is empty. Cannot access front.\n";
        exit(EXIT_FAILURE);
    }
    return data[front];
}

template <typename T>
T& Queue<T>::at(int index) {
    if (index < 0 || index >= count) {
        cerr << "Index out of range!";  
        exit(EXIT_FAILURE); 
    }
    return data[(front + index) % maxSize];  
}

template <typename T>
bool Queue<T>::isEmpty() const {
    return count == 0;
}

template <typename T>
int Queue<T>::size() const {
    return count;
}

template <typename T>
int Queue<T>::capacity() const {
    return maxSize;
}

template <typename T>
void Queue<T>::clear() {
    front = 0;
    rear = 0;
    count = 0;
}

template <typename T>
void Queue<T>::expand() {
    int newMaxSize = maxSize * 2;
    T* newData = new T[newMaxSize];

    for (int i = 0; i < count; ++i) {
        newData[i] = data[(front + i) % maxSize];
    }

    delete[] data;
    data = newData;
    front = 0;
    rear = count;
    maxSize = newMaxSize;
}

#endif
