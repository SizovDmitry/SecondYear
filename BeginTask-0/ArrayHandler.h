#include <iostream>

using namespace std;

template <typename T>

class ArrayHandler
{

    private:
        size_t size;
        size_t _size;
        T* arr;


    public:

        ArrayHandler() {
            size = 0;
            _size = 0;
            arr = new T[_size];
        };

        void AppendElem(T elem) {
            if (size == _size) {
                if (_size == 0) {
                    _size = 1;
                } else {
                    _size = _size * 2;
                }
                T* new_arr = new T[_size];
                for (size_t i = 0; i < size; i++) {
                    new_arr[i] = arr[i];
                };
                delete []arr;
                arr = new_arr;
            };

            arr[size] = elem;
            size++;                
        };
        
        T GetMax() {
            T max = arr[0];
            for (size_t i = 0; i < size; i++) {
                if (max < arr[i])
                    max = arr[i];
            };
            return max;
        };

        T GetMin() {
            T min = arr[0];
            for (size_t i = 0; i < size; i++) {
                if (arr[i] < min)
                    min = arr[i];
            };
            return min;
        };

        int FindElem(T elem) {
            for (size_t i = 0; i < size; i++) {
                if (arr[i] == elem)
                    return i;
            };
            return -1;
        };

        ~ArrayHandler(){
            delete []arr;
        };
        
};
