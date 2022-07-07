#include "general.hpp"

int cost[MAX_V][MAX_V];
int mincost[MAX_V];
bool used[MAX_V];
int v;

int prim() {
  fill(mincost, mincost + v, INT_MAX);
  fill(used, used + v, false);
  mincost[0] = 0;
  int res = 0;

  while (true) {
    int v = -1;
    for (int u = 0; u < v; u++)
      if (!used[u] && (v == -1 || mincost[u] < mincost[v]))
        v = u;

    if (v == -1) break;
    used[v] = true;
    res += mincost[v];
    for (int u = 0; u < v; u++)
      mincost[u] = min(mincost[u], cost[v][u]);
  }
  return res;
}