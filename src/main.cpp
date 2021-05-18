#include <iostream>
#include <vector>
#include <algorithm>

#include "utils/ArraysFunctions.h"
#include "tree/SegmentTree.h"

using namespace std;

int main() {
    int size = 14;

//    vector<long long> arr = generate_array_with_random_numbers(size);
    vector<long long> arr = {0, 1, 2, 3, 4, 5, 6, 7 ,8 , 9, 10, 11, 12, 13};
    vector<long long> tree(size * 4);
    print_array(arr);

    build(tree, arr, 0, 0, size);

    // запрос суммы на отрезке  [5, 7] = 5 + 6 + 7 = 18
    int left = 5;
    int right = 7;
    cout  <<  "sum  on [" << left << ", " << right << "] = " << rsq(tree, 0, 0, size, left, right + 1) << endl;

    // обновление 7 элемента массива на значение 0 (было 7, станет 0)
    update(tree, 0, 0, size, 7, 0);

    // запрос суммы на обновлённом отрезке  [5, 7] = 5 + 10 + 7 = 22
    cout << "sum  on [" << left << ", " << right << "] = " << rsq(tree, 0, 0, size, left, right + 1) << endl;



    // дерево отрезков для задачи поиска максимума на отрезке + его индекса (индекс по условию любого из максимумов)
    vector<pair<long long, int>> treeMax(size * 4);
    build_max(treeMax, arr, 0, 0, size);
    pair<long long, int> ans =  get_max(treeMax, 0, 0, size, left, right + 1);
    cout << "max item: " << ans.first << ", item's index: " << ans.second;

    return 0;
}

