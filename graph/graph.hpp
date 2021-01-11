#include "general.hpp"

using Pair = pair<int, int>;

vector<int> BellmanFord(vector<Edge> &es, int s, int V = MAX_V, int E = MAX_E);
bool FindNegativeLoop(vector<Edge> &es, int V = MAX_V, int E = MAX_E);

vector<int> Dijkstra(vector<vector<Edge>> G, int s, int V = MAX_V, int E = MAX_E);
vector<int> DijkstraGetPath(vector<vector<int>> &cost, int s, int V = MAX_V, int E = MAX_E);

void WarshallFloyd(vector<vector<int>> &dp, int V = MAX_V);
int Kruskal(vector<Edge> &es, int E = MAX_E, int V = MAX_V);
int Prim(vector<vector<int>> &cost, int V = MAX_V, int E = MAX_E);