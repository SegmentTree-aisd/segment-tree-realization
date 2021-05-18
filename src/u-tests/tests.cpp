#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>

#include "../utils/ArraysFunctions.h"
#include "../tree/SegmentTree.h"

using namespace std;
const long long upper = 1000000000;
const long long lower = -10000000;

int main() {
    vector<int> sizes = {100, 5000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000,
            150000, 200000, 250000, 300000, 350000, 400000, 450000, 500000, 550000, 600000, 650000, 700000, 750000, 800000, 850000, 900000};
//    vector<int> sizes = {1000000};

    ofstream buildDataFile;
    buildDataFile.open ("/home/regina/Repositories/Algorythmes and data structure/Семестровки АиСД/segment tree/segment-tree-realization/src/u-tests/build.txt");
    ofstream rsqDataFile;
    rsqDataFile.open ("/home/regina/Repositories/Algorythmes and data structure/Семестровки АиСД/segment tree/segment-tree-realization/src/u-tests/rsq-random-ranges.txt");
    ofstream updateDataFile;
    updateDataFile.open ("/home/regina/Repositories/Algorythmes and data structure/Семестровки АиСД/segment tree/segment-tree-realization/src/u-tests/update.txt");

    for (int size : sizes) {
        cout << "SIZE = " << size << endl;
        int counter = 10;

        while (counter > 0) {
            cout << counter << endl << endl;

            vector<long long> arr = generate_array_with_random_numbers(size);
            vector<long long> tree(size * 4);
            //print_array(arr);

            auto start = std::chrono::high_resolution_clock::now();
            build(tree, arr, 0, 0, size);                               ///build
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

            buildDataFile << duration.count() << endl;
            cout << "       builded tree by time: " << duration.count() << endl;

//            int left = generate_random_int_number(0, size);
//            int right = left + 51;
//
//            while (right >= size) {
//                left = generate_random_int_number(0, size);
//                right = left + 51;
//            }

            int right = generate_random_int_number(0, size);
            int left = generate_random_number(0, size);
            while (left >= right) {
                left = generate_random_int_number(0, size);
                right = generate_random_int_number(0, size);
            }

            auto start1 = std::chrono::high_resolution_clock::now();
            long long sum = rsq(tree, 0, 0, size, left, right + 1);          ///rsq
            auto stop1 = std::chrono::high_resolution_clock::now();
            auto duration1 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop1 - start1);

            rsqDataFile << duration1.count() << endl;
            cout << "       sum on [" << left << ", " << right << "] = " << sum << ", time:" << duration1.count() << endl;

//            int random_position = generate_random_int_number(0, size);
            int random_position = 10;
//            long long random_value = generate_random_number(-100,1000);
            long long random_value = 0;

            auto start2 = std::chrono::high_resolution_clock::now();
            update(tree, 0, 0, size, random_position, random_value);  ///update
            auto stop2 = std::chrono::high_resolution_clock::now();
            auto duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop2 - start2);

            updateDataFile << duration2.count() << endl;
            cout << "       changed " << random_position << " element = " << arr[random_position] << " on " << random_value << ", time: " << duration2.count() << endl;


            auto start3 = std::chrono::high_resolution_clock::now();
            long long sum3 = rsq(tree, 0, 0, size, left, right + 1);  ///rsq
            auto stop3 = std::chrono::high_resolution_clock::now();
            auto duration3 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop3 - start3);

            //rsqDataFile << duration3.count() << endl;
            cout << "       sum after update on [" << left << ", " << right << "] = " << sum3 << ", time:" << duration3.count() << endl;

            counter--;
        }

        buildDataFile << "---" << endl;
        updateDataFile << "---" << endl;
        rsqDataFile << "---" << endl;
    }

    buildDataFile.flush();
    updateDataFile.flush();
    rsqDataFile.flush();

    buildDataFile.close();
    updateDataFile.close();
    rsqDataFile.close();

    return 0;
}
