#include <vector>
#include <iostream>

using namespace std;

const int MAXN = 100;

struct segTreeNode {                                        // структура - вершина дерева
    long val;                                               // значение суммы на отрезке, за который отвечает вершина
    segTreeNode* left, *right;                              // указатели на левую и правые вершины

    segTreeNode(segTreeNode* l, segTreeNode* r, int v) {
        left = l;
        right = r;
        val = v;
    }
};

segTreeNode* version[MAXN];                               // массив со ссылками на корневые вершины различных версий
int curVersion = -1;


void build(segTreeNode* node, vector<long> arr, int tl, int tr) {

    if (tr - tl == 1) {         // вершинка-лист, содержащая значение одного элемента, учитываем, что работаем с полуинтервалами [tl, tr)
        node->val = arr[tl];
        return;
    }

    int mid = (tl + tr) / 2;
    node->left = new segTreeNode(nullptr, nullptr, 0);
    node->right = new segTreeNode(nullptr, nullptr, 0);
    build(node->left, arr, tl, mid);
    build(node->right, arr, mid, tr);
    node->val = node->left->val + node->right->val;
}

// создание первой версии дерева, сложность O(nlogn)
// эта функция должна вызываться из main, принимается исходный массив arr, левая и правая границы tl и tr
void build(vector<long> arr, int tl, int tr) {
    segTreeNode* root = new segTreeNode(nullptr, nullptr, 0);           // создадим вершину-корень дерева для версии version-0

    curVersion = 0;
    version[curVersion] = root;                                                 // сохраним корень-вершину node нулевой (изначальной, создаваемой при построении) версии
    build(root, arr, tl, tr);
}


void upgrade(segTreeNode* prev, segTreeNode* cur, int tl, int tr, int idx, int value) {
    if (idx > tr || idx < tl || tl > tr)
        return;

    if (tl + 1 == tr) {                                             // изменение значения в новой версии дерева
        cur->val = value;
        return;
    }

    int tmid = (tl + tr) / 2;
    if (idx <= tmid) {
        cur->right = prev->right;                                      // создание ссылки на правого потомка из предыдущей версии
        cur->left = new segTreeNode(nullptr, nullptr, 0);     // создание новой вершины segTreeNode в текущей версии

        upgrade(prev->left, cur->left, tl, tmid, idx, value);
    }
    else {
        cur->left = prev->left;                                        // создание ссылки на левое поддерево в предыдущей версии
        cur->right = new segTreeNode(nullptr, nullptr, 0);    // создание новой вершины segTreeNode в текущей версии

        upgrade(prev->right, cur->right, tmid, tr, idx, value);
    }

    cur->val = cur->left->val + cur->right->val;                // подсчет суммы в текущей версии, используя значения в вершинках предыдущей версии и текущих модифицированных
}

// Обновление значения элемента arr[inx] на value, создание новой версии
// Временная сложность : O(logn), Сложноть по памяти : O(logn)
// эта функция должна вызываться из main, принимаются левая и правая границы всего дерева tl и tr, позиция подифицируемого элемента pos и его новое значение value
void upgrade(int tl, int tr, int idx, int value) {
    segTreeNode* prev = version[curVersion];                          // prev : указывает на вершину segTreeNode предыдущей версии
    curVersion++;                                                     // переход на новую версию

    if (curVersion >= MAXN)
        throw std::overflow_error("too big");

    version[curVersion] = new segTreeNode(nullptr, nullptr, 0);    // cur  : указывает на вершину segTreeNode текущей версии
    segTreeNode* cur = version[curVersion];

    upgrade(prev, cur, tl, tr, idx, value);
}

long rsq(segTreeNode* node, int tl, int tr, int ql, int qr) {
    if (ql >= tr || qr <= tl || tl > tr)
        return 0;

    if (tl >= ql && tr <= qr)
        return node->val;

    int mid = (tl + tr) / 2;
    long p1 = rsq(node->left, tl, mid, ql, qr);
    long p2 = rsq(node->right, mid, tr, ql, qr);
    return p1 + p2;
}

// эта функция должна вызываться из main, принимаются: значение версии k, левая и правая границы всего дерева tl и tr, левая и правая границы запроса ql и qr
long rsq(int k, int tl, int tr, int ql, int qr) {
    segTreeNode* node = version[k];
    return rsq(node, tl, tr, ql, qr);
}

//
int main(int argc, char const *argv[]) {
    vector<long> arr= {1,2,3,4,5};
    int n = arr.size();

    build(arr, 0, n);
    cout << "tree is built" << endl;

    upgrade( 0, n, 0, 10);               // обновление до version-1
    cout << "tree is updated 1" << endl;

    upgrade(0, n, 0, 20);                // обновление до version-2
    cout << "tree is updated 2" << endl;

    // {1,2,3,4,5}
    cout << "Для дерева версии  0 , запрос суммы на отрезке [0,3] : ";
    cout << rsq(0, 0, n, 0, 4) << endl;

    // {10,2,3,4,5};
    cout << "Для дерева версии 1 , запрос суммы на отрезке [0,3] : ";
    cout << rsq(1, 0, n, 0, 4) << endl;

    // {20,2,10,4,5};
    cout << "Для дерева версии 2 , запрос суммы на отрезке [0,3] : ";
    cout << rsq(2, 0, n, 0, 4) << endl;


    return 0;
}

