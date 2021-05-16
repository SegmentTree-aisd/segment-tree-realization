#include <iostream>
#include <vector>
#include <algorithm>

#include "utils/ArraysFunctions.h"
#include "tree/SegmentTree.h"

using namespace std;

int main() {
    int size = 14;
    //vector<int> arr = generate_array_with_random_numbers(size);
    vector<long long> arr = {0, 1, 2, 3, 4, 5, 6, 7 ,8 , 9, 10, 11, 12, 13};
    vector<long long> tree(size * 4);
    print_array(arr);

    build(tree, arr, 0, 0, tree.size());

    // запрос суммы на отрезке  [5, 7] = 5 + 6 + 7 = 18
    int left = 0;
    int right = 13;
    cout  << rsq(tree, 0, 0, tree.size(), left, right + 1);

    return 0;
}

