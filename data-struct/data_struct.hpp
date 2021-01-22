#include "general.hpp"

class UnionFind {
public:
  UnionFind(int v) {
    grp.assign(v, 0);
    iota(grp.begin(), grp.end(), 0);
  }

  bool Same(int u, int v) {
    return grp[u] == grp[v];
  }

  void Unite(int u, int v) {
    grp[v] = grp[u];
  }

  int Find(int x) {
    if (grp[x] != x)
      grp[x] = Find(grp[x]);
    return grp[x];
  }
private:
  vector<int> grp;
};