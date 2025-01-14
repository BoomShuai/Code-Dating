#ifndef QUEUE_H
#define QUEUE_H

#include <iostream> 

#define MAX 1000 

template <typename T>
class Queue {
private:
    T* data;     
    int front;     
    int rear;      
    int maxSize;   
    int count;    

    void expand(); 

public:
    Queue();
    ~Queue();

    void enqueue(const T& item); 
    void dequeue();             
    T& atFront();               
    T& at(int index);
    bool isEmpty() const;       
    int size() const;            
    int capacity() const;        
    void clear();               
};

#include "Queue.cpp" 

#endif
