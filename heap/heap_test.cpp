#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
#include <unordered_map>

#include "heap.h"
// #include "lib/int_array.h"

using namespace std;

void generate_random_array(int size, vector<int> &nums) {
    nums.reserve(size);
    for (int i = 0; i < size; i++) {
        nums.push_back(std::rand() % size);
    }
}

void print_nums(const vector<int> &nums) {
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }
    cout << endl;
}

int main() {
    std::srand(std::time(nullptr));
    vector<int> nums;
    generate_random_array(10, nums);
    print_nums(nums);
    // for (int i = 0; i < nums.size(); i++) {
    //     h.push(nums[i]);
    // }
    Heap h(nums);
    vector<int> snums;
    h.get(snums);
    print_nums(snums);
    cout << h.check() << endl;
    while (!h.empty()) {
        cout << h.top() << " ";
        h.pop();
    }
    cout << endl;
    return 0;
}
