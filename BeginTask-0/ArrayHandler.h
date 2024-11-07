
#include <cstdint>
#include <cstring>
#include <iostream>
template<typename T>
class ArrayHandler {
private:
    size_t _size;
    T* _array;
    T _max;
    T _min;
    size_t _count;
public:
    ArrayHandler(size_t size = 10) { //123
        _size = size;
        _array = new T[_size];
        _max = std::numeric_limits<T>::min();
        _min = std::numeric_limits<T>::max();
        _count = 0;
    }

    void AppendElem(T elem) {
        if (_count == _size) {
            _size *= 7;
            T* new_arr = new T[_size];
            std::memcpy(new_arr, _array, _count * sizeof(T));
            delete[] _array;
            _array = new_arr;
        }
        _array[_count] = elem;
        if (elem > _max) {
            _max = elem;
        }
        if (elem < _min) {
            _min = elem;
        }
        _count++;
    }

    bool IsContains(T elem) {
        std::sort(_array, _array + _count);
        int l = 0, r = _count - 1;
        while (l <= r) {
            int ind = l + (r - l) / 2;
            if (_array[ind] == elem) {
                return true;
            }
            else if (_array[ind] < elem) {
                l = ind + 1;
            }
            else {
                r = ind - 1;
            }
        }
        return false;

    }

    T GetMax() {
        return _max;
    }

    T GetMin() {
        return _min;
    }

    ~ArrayHandler() {
        delete[] _array;
    }
};