#ifndef SORT_H
#define SORT_H

#include <iostream> 
using namespace std; 

template <typename T>
int partition(T arr[], int low, int high) {
    T pivot = arr[high];  
    int i = low - 1; 
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            i++;  
            swap(arr[i], arr[j]);  
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

template <typename T>
void quickSort(T arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

template <typename T>
void quickSort(T arr[], int size) {
    if (size > 1) {
        quickSort(arr, 0, size - 1);
    }
}

#endif  
