#include <vector>
#include <ostream>
#include <random>

class IntArray : public std::vector<int> {
public:
    static void srand(unsigned int seed) {
        std::srand(seed);
    }
    void random(int size) {
        this->resize(size);
        for (int i = 0; i < size; i++) {
            this->at(i) = std::rand() % size;
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const IntArray& arr);
};

std::ostream& operator<<(std::ostream& os, const IntArray& arr) {
    os << "[";
    if (arr.size() >= 1) {
        for (int i = 0; i < arr.size() - 1; i++) {
            os << arr[i] << ", ";
        }
        os << arr.back();
    }
    os << "]";
    return os;
}