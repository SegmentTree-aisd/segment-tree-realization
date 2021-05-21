#include "SegmentTreeWithLazyPropagation.h"
#include <iostream>
#include <vector>

using namespace std;

// построение дерева, принимается массив tree размера 4*N, исходный массив arr размера N, текущая вершина v, левая tl и правая tr границы текущего отрезка, правая - исключительно
// обозначать отрезки будем полуинтервалами типа [0, N) или в отрезках - [0, N - 1]
void buildAddOnRange(vector<long long> &tree, const vector<long long> &arr, int v, int tl, int tr) {
    if (tr - tl == 1) {
        tree[v] = arr[tl];
        return;
    }
    tree[v] = 0; // начальная метка на узлах, не являющихся листьями
    int middle = (tl + tr) / 2;
    buildAddOnRange(tree, arr, 2 * v + 1, tl, middle);
    buildAddOnRange(tree, arr, 2 * v + 2, middle, tr);
}

void updateAddOnRange(vector<long long> &tree, int v, int tl, int tr, int l, int r, int add) {
    if(l > r)    // прерываем работу, если левая граница оказалась больше правой
        return ;

    if (l == tl && r == tr)           // помечаем отрезок, если он полностью состоит из нужных элементов массива
        tree[v] += add;
    else {
        int tm = (tl + tr) / 2;
        updateAddOnRange(tree, 2*v + 1, tl, tm, l, min(tm, r), add);
        updateAddOnRange(tree, 2*v + 2, tm + 1, tr, max(l, tm), r, add);
    }
}

// запрос элемента в случае, когда обновление - прибавление на отрезке
long long getAddOnRange (vector<long long> &tree, int v, int tl, int tr, int pos) {
    if (tl == tr) {
        return tree[v];
    }
    int tm = (tl + tr) / 2;
    if (pos < tm) {
        return tree[v] + getAddOnRange(tree, 2*v + 1, tl, tm, pos);
    }
    else {
        return tree[v] + getAddOnRange(tree, 2*v + 2, tm, tr, pos);
    }
}

// построение дерева, принимается массив tree размера 4*N, исходный массив arr размера N, текущая вершина v, левая tl и правая tr границы текущего отрезка, правая - исключительно
// обозначать отрезки будем полуинтервалами типа [0, N) или в отрезках - [0, N - 1]
// случай, в котором обновление - присвоение всему отрезку некоторого значения
void buildAssignOnRange(vector<long long> &tree, const vector<long long> &arr, int v, int tl, int tr) {
    if (tr - tl == 1) {
        tree[v] = arr[tl];
        return;
    }
    tree[v] = -1; // начальная метка на узлах, не являющихся листьями
    int middle = (tl + tr) / 2;
    buildAssignOnRange(tree, arr, 2 * v + 1, tl, middle);
    buildAssignOnRange(tree, arr, 2 * v + 2, middle, tr);
}

// операция проталкивания метки из родительского узла дочерним
void push (vector<long long> &tree, int v) {
    if (tree[v] != -1) { // проверка на то, что узел не является непомеченным
        tree[2*v + 1] = tree[2*v + 2] = tree[v];
        tree[v] = -1;
    }
}

// операция обновления - присвоения всему отрезку некоторого значения
void updateAssignOnRange (vector<long long> &tree, int v, int tl, int tr, int l, int r, int val) {
    if (l > r) {
        return;
    }
    if (l == tl && tr == r) {
        tree[v] = val;
    }
    else {
        push(tree, v); // проталкиваем метку родительского узла дочерним
        int tm = (tl + tr) / 2;
        updateAssignOnRange(tree, 2*v + 1, tl, tm, l, min(r,tm), val);
        updateAssignOnRange(tree, 2*v + 2, tm, tr, max(l,tm), r, val);
    }
}

// операция получения в случае, когда обновление - присвоение всему отрезку некоторого значения
long long getAssignOnRange (vector<long long> &tree, int v, int tl, int tr, int pos) {
    if (tr - tl == 1) {
        return tree[v];
    }
    push(tree, v); // проталкиваем метку до листьев, если она есть
    int tm = (tl + tr) / 2;
    if (pos < tm) {
        return getAssignOnRange(tree, 2*v + 1, tl, tm, pos);
    }
    else {
        return getAssignOnRange(tree, v * 2 + 1, tm, tr, pos);
    }
}
