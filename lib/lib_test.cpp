#include <ctime>
#include <iostream>
#include "int_array.h"

using namespace std;

int main() {
    IntArray::srand(std::time(nullptr));
    IntArray arr;
    arr.random(20);
    cout << arr << endl;
    // print_nums(arr);
    return 0;
}