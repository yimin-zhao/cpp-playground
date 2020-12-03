#include "general.hpp"

vector<int> bit;

int sum(int i) {
  int s = 0;
  while (i > 0) {
    s += bit[i];
    i = i & (i - 1);
  }
  return s;
}

void add(int i, int v) {
  while (i <= bit.size()) {
    bit[i] += v;
    i += i & -i;
  }
}

int solve(vector<int> A) {
  int n = A.size();
  bit.assign(n + 1, 0);
  //iota(bit.begin() + 1, bit.end(), 1);

  cout << bit << endl;
  int res = 0;
  for (int j = 0; j < n; j++) {
    res += j - sum(A[j]);
    add(A[j], 1);
  }
  return res;
}

int main() {
  auto data = LoadTestcase<vector<int>>(__FILE__);
  Run(data, solve);
}