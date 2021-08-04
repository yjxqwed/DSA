#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

void generate_random_array(int size, vector<int> &nums) {
    nums.reserve(size);
    for (int i = 0; i < size; i++) {
        nums.push_back(std::rand() % size);
    }
}

/* ========================================================================== */
/* =============================== quick sort =============================== */
/* ========================================================================== */

// [begin, end): left-close and right-open
int get_pivot(vector<int> &nums, int begin, int end) {
    // pivot should be the median to get the best performance
    // return end - 1;
    return begin + std::rand() % (end - begin);  // randomized quick sort
}

// [begin, end): left-close and right-open
int partition(vector<int> &nums, int begin, int end) {
    int p = get_pivot(nums, begin, end);
    std::swap(nums[begin], nums[p]);
    int pivot = nums[begin];
    int i = begin + 1, j = end - 1;
    while (true) {
        while (i < end && nums[i] < pivot) {
            i++;
        }
        while (j > begin && nums[j] >= pivot) {
            j--;
        }
        if (i < j) {
            std::swap(nums[i], nums[j]);
            i++;
            j--;
        } else {
            break;
        }
    }
    // j should be either the last element that violates 'nums[j] >= pivot' or the <begin>
    std::swap(nums[begin], nums[j]);
    return j;
}

// [begin, end): left-close and right-open
void quick_sort(vector<int> &nums, int begin, int end) {
    if (end - begin < 2) {
        return;
    }
    int p = partition(nums, begin, end);
    quick_sort(nums, begin, p);
    quick_sort(nums, p + 1, end);
}

void quick_sort(vector<int> &nums) {
    quick_sort(nums, 0, nums.size());
}

/* ========================================================================== */
/* =============================== merge sort =============================== */
/* ========================================================================== */

// top down
// [begin, end): left-close and right-open
void merge_sort(vector<int> &nums, int begin, int end) {
    int len = end - begin;
    if (len < 2) {
        return;
    }
    int hend = begin + len / 2;
    merge_sort(nums, begin, hend);
    merge_sort(nums, hend, end);
    // merge process
    int i = begin, j = hend;
    vector<int> tmp;
    tmp.reserve(len);
    while (i < hend && j < end) {
        if (nums[i] < nums[j]) {
            tmp.push_back(nums[i++]);
        } else {
            tmp.push_back(nums[j++]);
        }
    }
    while (i < hend) {
        tmp.push_back(nums[i++]);
    }
    while (j < end) {
        tmp.push_back(nums[j++]);
    }
    for (int k = begin; k < end; k++) {
        nums[k] = tmp[k - begin];
    }
}

void merge_sort(vector<int> &nums) {
    merge_sort(nums, 0, nums.size());
}

// bottom up
// [begin, end): left-close and right-open
void merge_sort_bu(vector<int> &nums, int begin, int end) {
    int len = end - begin;
    if (len < 2) {
        return;
    }
    vector<int> tnums(len);

    int cover = 2;
    while (cover < len) {
        cover *= 2;
    }

    for (int step = 2; step <= cover; step *= 2) {
        for (int i = 0; i < len; i += step) {
            int e = std::min(i + step, end);
            int ll = e - i;
            int he = std::min(i + step / 2, end);
            int j = i, k = he;
            int l = i;
            while (j < he && k < e) {
                if (nums[j] < nums[k]) {
                    tnums[l++] = nums[j++];
                } else {
                    tnums[l++] = nums[k++];
                }
            }
            while (j < he) {
                tnums[l++] = nums[j++];
            }
            while (k < e) {
                tnums[l++] = nums[k++];
            }
            for (int m = i; m < e; m++) {
                nums[m] = tnums[m];
            }
        }
    }
}

void merge_sort_bu(vector<int> &nums) {
    merge_sort_bu(nums, 0, nums.size());
}

/* ========================================================================== */
/* =============================== heap sort ================================ */
/* ========================================================================== */

void fix_down(vector<int> &nums, int id, int len) {
    while (id * 2 + 1 < len) {
        int lc = id * 2 + 1, rc = lc + 1;
        int l = rc >= len || nums[lc] >= nums[rc] ? lc : rc;
        if (nums[l] > nums[id]) {
            std::swap(nums[id], nums[l]);
            id = l;
        } else {
            break;
        }
    }
}

void heapify(vector<int> &nums, int len) {
    for (int i = len / 2; i >= 0; i--) {
        fix_down(nums, i, len);
    }
}

void heap_sort(vector<int> &nums) {
    if (nums.size() <= 1) {
        return;
    }
    heapify(nums, nums.size());
    for (int i = 0; i < nums.size() - 1; i++) {
        std::swap(nums[0], nums[nums.size() - 1 - i]);
        fix_down(nums, 0, nums.size() - 1 - i);
    }
}

/* ========================================================================== */
/* =============================== test & main ============================== */
/* ========================================================================== */

void print_nums(const vector<int> &nums) {
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }
    cout << endl;
}

typedef void (*sort_fun_t)(vector<int> &);

static unordered_map<string, sort_fun_t> sorters = {
    { "quick_sort", quick_sort },
    { "merge_sort", merge_sort },
    { "merge_sort_bu", merge_sort_bu },
    { "heap_sort", heap_sort }
};

const string USAGE = "Usage: ./sort.exe <quick_sort|merge_sort|merge_sort_bu|heap_sort> <size>";

static void print_err(const string &err) {
    cerr << err << endl << USAGE << endl;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        print_err("Bad args!");
        return -1;
    }
    std::srand(std::time(nullptr));
    string sorter_name = string(argv[1]);
    if (sorters.find(sorter_name) == sorters.end()) {
        print_err("Unknown sorter!");
        return -1;
    }
    string size_str = string(argv[2]);
    int size = -1;
    try {
        size = std::stoi(size_str);
    } catch (...) {
        print_err("Bad size!");
        return -1;
    }
    if (size < 1) {
        print_err("Bad size!");
        return -1;
    }

    sort_fun_t sorter = sorters[sorter_name];
    vector<int> nums;
    generate_random_array(size, nums);
    vector<int> std_nums(nums.begin(), nums.end());

    cout << "before sorting" << endl;
    print_nums(nums);

    auto start = std::chrono::high_resolution_clock::now();
    quick_sort(nums, 0, nums.size());
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    cout << "after sorting (" << sorter_name << "); time elapsed = " << microseconds << "us" << endl;
    print_nums(nums);

    start = std::chrono::high_resolution_clock::now();
    std::sort(std_nums.begin(), std_nums.end());
    elapsed = std::chrono::high_resolution_clock::now() - start;
    microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    cout << "after sorting (std::sort); time elapsed = " << microseconds << "us" << endl;
    print_nums(std_nums);
    for (int i = 0; i < size; i++) {
        if (nums[i] != std_nums[i]) {
            cerr << "Failed to sort!" << endl;
            return -1;
        }
    }
    cout << "Succeeded to sort!" << endl;
    return 0;
}