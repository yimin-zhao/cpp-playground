#include "graph.hpp"

vector<int> BellmanFord(vector<Edge> &es, int s, int V, int E) {
  vector<int> dist(V, INT_MAX);
  dist[s] = 0;
  while (true) {
    bool update = false;
    for (int i = 0; i < E; ++i) {
      Edge e = es[i];
      if (dist[e.from] != INT_MAX && dist[e.to] > dist[e.from] + e.cost) {
        dist[e.to] = dist[e.from] + e.cost;
        update = true;
      }
    }
    if (!update)
      break;
  }
  return dist;
}

bool FindNegativeLoop(vector<Edge> &es, int V, int E) {
  vector<int> dist(V, 0);

  for (int i = 0; i < V; i++) {
    for (int j = 0; j < E; j++) {
      Edge &e = es[j];
      if (dist[e.to] > dist[e.from] + e.cost) {
        dist[e.to] = dist[e.from] + e.cost;
        if (i == V - 1)
          return true;
      }
    }
  }
  return false;
}

vector<int> Dijkstra(vector<vector<Edge>> G, int s, int V, int E) {
  vector<int> dist(V, INT_MAX);
  priority_queue<Pair, vector<Pair>, greater<Pair>> que;
  que.push(Pair(0, s));

  while (!que.empty()) {
    auto p = que.top();
    que.pop();
    int v = p.second;
    if (dist[v] < p.first)
      continue;
    for (int i = 0; i < G[V].size(); i++) {
      Edge e = G[V][i];
      if (dist[e.to] > dist[v] + e.cost) {
        dist[e.to] = dist[v] + e.cost;
        que.push(Pair(dist[e.to], e.to));
      }
    }
  }

  return dist;
}

vector<int> DijkstraGetPath(vector<vector<int>> &cost, int s, int V, int E) {
  vector<int> dist(V, INT_MAX);
  vector<int> used(V, false);
  vector<int> path(V, -1);
  dist[s] = 0;

  while (true) {
    int v = -1;
    for (int u = 0; u < v; u++) {
      if (!used[u] && (v == -1 || dist[u] < dist[v]))
        v = u;
    }

    if (v == -1)
      break;
    used[v] = true;

    for (int u = 0; u < v; u++) {
      if (dist[u] > dist[v] + cost[v][u]) {
        dist[u] = dist[v] + cost[v][u];
        path[u] = v;
      }
    }
  }

  for (; s != -1; s = path[s])
    path.push_back(s);

  reverse(path.begin(), path.end());
  return path;
}

void WarshallFloyd(vector<vector<int>> &d, int V) {
  for (int k = 0; k < V; k++)
    for (int i = 0; i < V; i++)
      for (int j = 0; j < V; j++)
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}

int Kruskal(vector<Edge> &es, int E, int V) {
  sort(es.begin(), es.end(),
       [](const Edge &e1, const Edge &e2) { return e1.cost < e2.cost; });
  UnionFind uf(V);
  int res = 0;
  for (int i = 0; i < E; i++) {
    Edge &e = es[i];
    if (!uf.Same(e.from, e.to)) {
      uf.Unite(e.from, e.to);
      res += e.cost;
    }
  }
  return res;
}