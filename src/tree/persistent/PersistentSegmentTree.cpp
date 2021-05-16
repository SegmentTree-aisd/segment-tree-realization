//struct vertex {
//    vertex * leftSegTree, * rightSegTree;
//    int sum;
//
//    vertex (int val)
//            : leftSegTree(NULL), rightSegTree(NULL), sum(val)
//    { }
//
//    vertex (vertex * leftSegTree, vertex * rightSegTree)
//            : leftSegTree(leftSegTree), rightSegTree(rightSegTree), sum(0)
//    {
//        if (leftSegTree)  sum += leftSegTree->sum;
//        if (rightSegTree)  sum += rightSegTree->sum;
//    }
//};
//
//vertex * build (int a[], int tl, int tr) {
//    if (tl == tr)
//        return new vertex (a[tl]);
//    int tm = (tl + tr) / 2;
//    return new vertex (
//            build (a, tl, tm),
//            build (a, tm+1, tr)
//    );
//}
//
//int get_sum (vertex * t, int tl, int tr, int leftSegTree, int rightSegTree) {
//    if (leftSegTree > rightSegTree)
//        return 0;
//    if (leftSegTree == tl && tr == rightSegTree)
//        return t->sum;
//    int tm = (tl + tr) / 2;
//    return get_sum (t->leftSegTree, tl, tm, leftSegTree, min(rightSegTree,tm))
//           + get_sum (t->rightSegTree, tm+1, tr, max(leftSegTree,tm+1), rightSegTree);
//}
//
//vertex * update (vertex * t, int tl, int tr, int pos, int new_val) {
//    if (tl == tr)
//        return new vertex (new_val);
//    int tm = (tl + tr) / 2;
//    if (pos <= tm)
//        return new vertex (
//                update (t->leftSegTree, tl, tm, pos, new_val),
//                t->rightSegTree
//        );
//    else
//        return new vertex (
//                t->leftSegTree,
//                update (t->rightSegTree, tm+1, tr, pos, new_val)
//        );
//}