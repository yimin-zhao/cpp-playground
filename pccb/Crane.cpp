#include "general.hpp"
vector<double> vx, vy, ang;

void init(vector<int>& L, int k, int l, int r) {

  if (r - l == 1) {
    vy[k] = L[l];
  } else {
    int left = k * 2 + 1, right = k * 2 + 2;
    init(L, left, l, (l + r) / 2);
    init(L, right, (l + r) / 2, r);
    vy[k] = vy[left] + vy[right];

  }
}

void change(int s, double a, int v, int l, int r) {
  if (s <= l)
    return;
  else if (s < r) {
    int left = v * 2 + 1, right = v * 2 + 2;
    int m = (l + r) / 2;
    change(s, a, left, l, m);
    change(s, a, right, m, r);
    if (s <= m) ang[v] += a;

    double a = sin(ang[v]), c = cos(ang[v]);
    vx[v] = vx[left] + (c * vx[right] - s * vy[right]);
    vy[v] = vy[left] + (s * vx[right] + c * vy[right]);
    cout << v << " " << left << " " << right << endl << vx << vy << endl;
  }
}

vector<string> solve(vector<int> L, vector<int> S, vector<int> A) {
  int N = L.size(), C = S.size();
  vx.assign(2 * N + 1, 0.0), vy.assign(2 * N + 1, 0.0), ang.assign(2 * N + 1, 0.0);
  vector<double> prv(N, M_PI);
  vector<string> res;

  init(L, 0, 0, N);
  cout << vx << vy << ang << endl;
  for (int i = 0; i < C; i++) {
    int s = S[i];
    double a = A[i] / 360.0 * 2 * M_PI;
    change(s, a - prv[s], 0, 0, N);
    prv[s] = a;
    res.push_back(to_string(vx[0]) + " " + to_string(vy[0]));
  }
  return res;
}

int main() {
  auto sets = LoadTestcase<vector<int>, vector<int>, vector<int>>(__FILE__);
  Run2(sets, solve);
}
