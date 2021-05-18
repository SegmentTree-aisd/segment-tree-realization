#include <iostream>
#include <vector>
#include <random>
#include "ArraysFunctions.h"

using namespace std;
const long long upper = 1000000000;
const long long lower = -10000000;


void print_array(std::vector<long long> &arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

vector<long long> generate_array_with_random_numbers(int size) {
    vector<long long> newVector(size);

    std::random_device rd;          // Get a random seed from the OS entropy device, or whatever
    std::mt19937_64 eng(rd());      // Use the 64-bit Mersenne Twister 19937 generator
                                    // and seed it with entropy.

    std::uniform_int_distribution<long long> distribution(lower, upper);

    for (int i = 0; i < size; i++) {
        newVector[i] = distribution(eng);
    }

    return newVector;
}

long long generate_random_number(long long lower_bound, long long upper_bound) {
    std::random_device rd;
    std::mt19937_64 eng(rd());

    std::uniform_int_distribution<long long> distribution(lower_bound, upper_bound);

    return distribution(eng);
}

int generate_random_int_number(int lower_bound, int upper_bound) {
    std::random_device rd;
    std::mt19937_64 eng(rd());

    std::uniform_int_distribution<long long> distribution(lower_bound, upper_bound);

    return distribution(eng);
}
