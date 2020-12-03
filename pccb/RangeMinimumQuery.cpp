#include "general.hpp"

class RMQ {
public:
  RMQ(int N) {
    int n = 0;
    while (n < N) n *= 2;
    vec.assign(2 * n - 1, INT_MAX);
  }

  void update(int k, int v) {
    int n = vec.size();
    k += n - 1;
    vec[k] = v;
    while (k > 0) {
      k = (k - 1) / 2;
      vec[k] = min(vec[k * 2 + 1], vec[k * 2 + 2]);
    }
  }

  int query(int a, int b, int k, int l, int r) {
    if (r <= a || b <= l) return INT_MAX;
    if (a <= l && r <= b) return vec[k];
    else {
      int vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
      int vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
      return min(vl, vr);
    }
  }
private:
  vector<int> vec;
};

int solve(int N) {
  RMQ rmq(N);
  for (int i = 1; i < N; i++)
    rmq.update(i, i);

  for (int i = 1; i < N; i++)
    rmq.query(i, i + 1, 0, 0, n);
}

int main() {
  auto data = LoadTestcase<int>(__FILE__);
  Run(data, solve);
}