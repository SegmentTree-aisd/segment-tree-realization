#ifndef SEGMENTTREE_SEGMENTTREE_H
#define SEGMENTTREE_SEGMENTTREE_H

void build(std::vector<long long> &tree, const std::vector<long long> &arr, int v, int tl, int tr);
int rsq(std::vector<long long> &tree, int v, int tl, int tr, int ql, int qr);
void update(std::vector<long long> &tree, int v, int tl, int tr, int pos, int new_val);
#endif //SEGMENTTREE_SEGMENTTREE_H
