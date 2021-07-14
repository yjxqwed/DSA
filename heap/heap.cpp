#include "heap.h"

Heap::Heap(const std::vector<int> &nums) {
    heap_store_.resize(nums.size() + 1);
    for (int i = 0; i < nums.size(); i++) {
        heap_store_[i + 1] = nums[i];
    }
    heapify();
}

void Heap::push(int x) {
    heap_store_.push_back(x);
    fix_up(heap_store_.size() - 1);
}

int Heap::pop() {
    int ret = heap_store_[1];
    heap_store_[1] = heap_store_[heap_store_.size() - 1];
    heap_store_.pop_back();
    fix_down(1);
    return ret;
}

void Heap::update(int id, int x) {
    if (x > heap_store_[id]) {
        heap_store_[id] = x;
        fix_up(id);
    } else if (x < heap_store_[id]) {
        heap_store_[id] = x;
        fix_down(id);
    }
}

void Heap::fix_up(int id) {
    while (id > 1 && heap_store_[id] > heap_store_[id / 2]) {
        std::swap(heap_store_[id], heap_store_[id / 2]);
        id /= 2;
    }
}

void Heap::fix_down(int id) {
    while (id * 2 < heap_store_.size()) {
        int lc = id * 2, rc = lc + 1;
        int l = rc >= heap_store_.size() || heap_store_[lc] >= heap_store_[rc] ? lc : rc;
        if (heap_store_[l] > heap_store_[id]) {
            std::swap(heap_store_[id], heap_store_[l]);
            id = l;
        } else {
            break;
        }
    }
}

/**
 * To heapify an array, we have 4 options: 
 *   * top-down fix-up        ✅
 *   * top-down fix-down      ❌
 *   * bottom-up fix-up       ❌
 *   * bottom-up fix-down     ✅
 * 
 */
void Heap::heapify() {
    // top-down fix-up (insert as a leaf node)
    // for (int i = 1; i < heap_store_.size(); i++) {
    //     fix_up(i);
    // }

    // bottom-up fix-down (insert as the root node)
    for (int i = heap_store_.size() - 1; i >= 1; i--) {
        fix_down(i);
    }
}

bool Heap::check() const {
    for (int i = 1; i < heap_store_.size(); i++) {
        int lc = i * 2, rc = lc + 1;
        if (lc > heap_store_.size()) {
        } else if (rc > heap_store_.size()) {
            if (heap_store_[i] < heap_store_[lc]) {
                return false;
            }
        } else {
            if (heap_store_[i] < heap_store_[lc] || heap_store_[i] < heap_store_[rc]) {
                return false;
            }
        }
    }
    return true;
}