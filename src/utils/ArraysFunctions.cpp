#include <iostream>
#include <vector>
#include <random>
#include "ArraysFunctions.h"

using namespace std;
const int rangeOfNumbers = 1000;

void print_array(std::vector<long long> &arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

vector<long long> generate_array_with_random_numbers(int size) {
    vector<long long> newVector(size);
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist6(1, rangeOfNumbers);

    for (int i = 0; i < size; i++) {
        newVector[i] = dist6(rng);
    }

    return newVector;
}
