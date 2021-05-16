#include <iostream>
#include <vector>
#include "SegmentTree.h"

using namespace std;

// построение дерева, принимается массив tree размера 4*N, исходный массив arr размера N, текущая вершина v, левая tl и правая tr границы текущего отрезка, правая - исключительно
// обозначать отрезки будем полуинтервалами типа [0, N) или в отрезках - [0, N - 1]
void build(vector<long long> &tree, const vector<long long> &arr, int v, int tl, int tr)
{
    if (tr - tl == 1) {                                   // условие выхода из рекурсии
        tree[v] = arr[tl];                                // отрезок имеет длину 1, т.е. это 1 элемент, сохраняем его в вершину-лист под текущим индексом v
        return;
    }

    int middle = (tl + tr) / 2;                            // иначе этот отрезок можно разделить пополам и продолжить построение дерева
    build(tree, arr, 2 * v + 1, tl, middle);        // строим дерево левого потомка с вершиной 2*v+1, который содержит в себе отрезок [tl, middle -1] или полуинтервал [tl, middle)
    build(tree, arr, 2 * v + 2, middle, tr);        // строим дерево правого потомка с вершиной 2*v+2, который содержит в себе вторую половину исходного отрезка - [middle, tr - 1] или полуинтервал [middle, tr)
    tree[v] = tree[2 * v + 1] + tree[2 * v + 2];         // вычисляем ассоциативную функцию для данной вершины после построения потомков, в данном случае это сумма на отрезке [tl, tr - 1]
}

// запрос суммы, принимается массив-дерево tree, текущая вершина v, левая и правая границы отрезка tl и tr, за который отвечает текущая вершина дерева, левая и правая границы запроса ql и qr
// из основной программы вызывать нужно rsq(tree, 0, 0, tree.size(), left, right) с учетом того, что в дереве для индексации используются полуинтервалы [left,  right)
int rsq(vector<long long> &tree, int v, int tl, int tr, int ql, int qr) {
    if (tl >= qr || tr <= ql)               // если наш отрезок, содержащийся в вершине v, не входит в запрос, вернуть 0.  T.е. это ситуации, когда отрезки расположены: [ql, qr] [tl, tr] или [tl, tr] [ql, qr]
        return 0;

    if (tl >= ql && tr <= qr)              // если текущий отрезок, содержащийся в вершине v, полностью входит в запрос, вернуть значение на этом отрезке tree[v].  T.е. это ситуации, когда отрезки расположены: [ql, [tl, tr] qr]  [tl=ql, tr=qr]
        return tree[v];

    int tmid = (tr + tl) / 2;             // иначе запрос содержится в половинках текущего отрезка, проверяем их
    return rsq(tree, 2 * v + 1, tl, tmid, ql, qr) + rsq(tree, 2 * v + 2, tmid, tr, ql, qr);
}

// это какая-то модификация с сайта, там нужно будет потом добавить условие выхода
// if (ql > qr) return 0;
// но я пока не тестила
// return rsq(tree, 2 * v + 1, tl, tmid, ql, min(qr, tmid)) + rsq(tree, 2*v + 2, tmid, tr, max(ql, tmid), qr);


// запрос модификации
// пока не проверила
void update (vector<int> &tree, int v, int tl, int tr, int pos, int new_val) {

    if (tl == tr)
        tree[v] = new_val;
    else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update (tree, v * 2 + 1, tl, tm, pos, new_val);
        else
            update (tree, v * 2 + 2, tm, tr, pos, new_val);
        tree[v] = tree[v * 2 + 1] + tree[v * 2 + 2];
    }
}
