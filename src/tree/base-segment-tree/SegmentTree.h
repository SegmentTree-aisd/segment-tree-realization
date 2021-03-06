#ifndef SEGMENTTREE_SEGMENTTREE_H
#define SEGMENTTREE_SEGMENTTREE_H
using namespace std;

void build(std::vector<long long> &tree, const std::vector<long long> &arr, int v, int tl, int tr);
long long rsq(std::vector<long long> &tree, int v, int tl, int tr, int ql, int qr);
void update(std::vector<long long> &tree, int v, int tl, int tr, int pos, long long new_val);

void build_max(std::vector<pair<long long, int>> &tree,std::vector<long long> &arr, int v, int tl, int tr);
pair<long long, int> get_max(std::vector<pair<long long, int>> &tree, int v, int tl, int tr, int ql, int qr);

#endif //SEGMENTTREE_SEGMENTTREE_H
