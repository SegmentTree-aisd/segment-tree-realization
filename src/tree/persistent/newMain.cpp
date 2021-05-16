#include <algorithm>

using namespace std;

struct segmentTree {
    int tl, tr; // левые и правые границы отрезков, левая - включително, правая - исключительно
    int sum = 0; // сумма на текущем отрезке
    segmentTree *leftSegTree = 0, *rightSegTree = 0;

    segmentTree (int lb, int rb) {
        tl = lb, tr = rb;

        if (tl + 1 < tr) {
            int tmid = (tl + tr) / 2;                  // если это не лист, содержащий 1 элемент, то создаем левое и правое поддеревья-потомки
            leftSegTree = new segmentTree(tl, tmid);
            rightSegTree = new segmentTree(tmid, tr);
        }
    }

    void add (int k, int x) {
        sum += x;
        if (leftSegTree) {
            if (k < leftSegTree->tr)
                leftSegTree->add(k, x);
            else
                rightSegTree->add(k, x);
        }
    }
    int get_sum (int lq, int rq) {
        if (tl >= lq && tr <= rq)           // если мы лежим полностью в отрезке запроса, вывести сумму
            return sum;
        if (max(tl, lq) >= min(tr, rq))     // если границы запроса выходят за пределы текущего отрезка, вывести ноль
            return 0;

            // иначе запрос содержится в потомках
        return leftSegTree->get_sum(lq, rq) + rightSegTree->get_sum(lq, rq);
    }
};