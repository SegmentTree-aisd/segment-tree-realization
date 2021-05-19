#ifndef SEGMENT_TREE_REALIZATION_SEGMENTTREEWITHLAZYPROPAGATION_H
#define SEGMENT_TREE_REALIZATION_SEGMENTTREEWITHLAZYPROPAGATION_H
#include <iostream>
#include <vector>
using namespace std;
void buildAddOnRange(vector<long long> &tree, const vector<long long> &arr, int v, int tl, int tr);
void updateAddOnRange(vector<long long> &tree, int v, int tl, int tr, int l, int r, int add);
int getAddOnRange (vector<long long> &tree, int v, int tl, int tr, int pos);
void buildAssignOnRange(vector<long long> &tree, const vector<long long> &arr, int v, int tl, int tr);
void push (vector<long long> &tree, int v);
void updateAssignOnRange (vector<long long> &tree, int v, int tl, int tr, int l, int r, int val);
int getAssignOnRange (vector<long long> &tree, int v, int tl, int tr, int pos);

#endif //SEGMENT_TREE_REALIZATION_SEGMENTTREEWITHLAZYPROPAGATION_H
