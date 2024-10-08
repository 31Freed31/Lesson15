#include <iostream>

using namespace std;

template <typename T>
void input(T array[8]) {
    cout << "Fill the array (8 elements):" << endl;
    for (int i = 0; i < 8; ++i) {
        cout << "Element " << i + 1 << ": ";
        cin >> array[i];
    }
}

template <typename T>
T calculateAverage(T array[8]) {
    T sum = 0;
    for (int i = 0; i < 8; ++i) {
        sum += array[i];
    }
    return sum / 8;
}

int main() {
    int intArray[8];
    input(intArray);
    cout << "Average (int): " << calculateAverage(intArray) << endl;

    double doubleArray[8];
    input(doubleArray);
    cout << "Average (double): " << calculateAverage(doubleArray) << endl;

    return 0;
}
