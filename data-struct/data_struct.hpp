#include "general.hpp"

class UnionFind {
public:
  UnionFind(int v) {
    grp.assign(v, 0);
    iota(grp.begin(), grp.end(), 0);
    connections = n;
  }

  bool Same(int u, int v) {
    return Find(u) == Find(v);
  }

  void Unite(int u, int v) {
    grp[Find(v)] = Find(u);
    connections--;
  }

  int Find(int x) {
    if (grp[x] != x)
      grp[x] = Find(grp[x]);
    return grp[x];
  }

  bool IsAllConnected() {
    return connections == 1;
  }
private:
  vector<int> grp;
  int connections;
};