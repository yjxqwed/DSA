#include <vector>

class Heap {
public:
    Heap() : heap_store_() {}
    Heap(const std::vector<int> &nums);

    inline int top() const { return heap_store_[0]; }
    inline bool empty() const { return heap_store_.empty(); }

    void push(int x);
    int pop();
    void update(int id, int x);

    bool check() const;

    void get(std::vector<int> &nums) const {
        nums.assign(heap_store_.begin(), heap_store_.end());
    }
private:
    void fix_up(int id);
    void fix_down(int id);
    void heapify();
private:
    std::vector<int> heap_store_;
};