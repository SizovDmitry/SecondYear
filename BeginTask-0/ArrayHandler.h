#pragma once
#include <iostream>
#include <limits>

using namespace std;

template <typename T>
class ArrayHandler {
private:
    size_t capacity;
    size_t count;
    T* arr;
    T max;
    T min;

    void resize() {
        capacity *= 2;
        T* newArr = new T[capacity];
        for (size_t i = 0; i < count; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }

public:
    ArrayHandler() {
        capacity = 1;
        count = 0;
        max = std::numeric_limits<T>::min();
        min = std::numeric_limits<T>::max();
        arr = new T[capacity];
    }

    void AppendElem(T elem) {
        if (count >= capacity) {
            resize();
        }
        arr[count] = elem;
        count++;

        if (min > elem) {
            min = elem;
        }

        if (max < elem) {
            max = elem;
        }
    }

    T GetMax() {
        return max;
    }

    T GetMin() {
        return min;
    }

    ~ArrayHandler() {
        delete[] arr;
    }
};
