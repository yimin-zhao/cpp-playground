#include "general.hpp"

class UnionFind {
public:
  UnionFind(int v) {
    grp.assign(v, 0);
    iota(grp.begin(), grp.end(), 0);
  }

  bool Same(int u, int v) {
    return Find(u) == Find(v);
  }

  void Unite(int u, int v) {
    grp[Find(v)] = Find(v);
  }

  int Find(int x) {
    if (grp[x] != x)
      grp[x] = Find(grp[x]);
    return grp[x];
  }
private:
  vector<int> grp;
};