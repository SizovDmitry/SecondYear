#include "ArrayHandler.hpp"

int main(){
    ArrayHandler <double> massive;
    for (int i = 1; i <= 5; i++) {
        massive.AppendElem(i);
    }
    cout << massive.GetMax() << endl;
    cout << massive.GetMin() << endl;
};