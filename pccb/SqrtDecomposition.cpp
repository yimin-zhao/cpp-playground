#include "general.hpp"

vector<int> solve(vector<int> A, vector<vector<int>> queries) {
  int n = A.size(), m =  queries.size();
  vector<vector<int>> bucket(3);
  vector<int> res;
  auto nums = A;

  for (int i = 0; i < n; i++) {
    bucket[i / 3].push_back(A[i]);
  }

  sort(nums.begin(), nums.end());
  for (int i = 0; i < n / 3; i++)
    sort(bucket[i].begin(), bucket[i].end());

  for (int i = 0; i < m; i++) {
    int l = queries[i][0], r = queries[i][1], k = queries[i][2];

    int lb = -1, ub = n - 1;
    while (ub - lb > 1) {
      int md = lb + (ub - lb) / 2;
      int x = nums[md];
      int tl = l, tr = r, c = 0;

      while (tl < tr && tl % 3 != 0) if (A[tl]++ <= x) c++;
      while (tl < tr && tr % 3 != 0) if (A[--tr] <= x) c++;
      while (tl < tr) {
        int b = tl / 3;
        c += upper_bound(bucket[b].begin(), bucket[b].end(), x) - bucket[b].begin();
        tl += 3;
      }

      if (c >= k) ub = md;
      else lb = md;
    }

    res.push_back(nums[ub]);
  }

  return res;
}

int main() {
  auto data = LoadTestcase<vector<int>, vector<vector<int>>>(__FILE__);
  Run2(data, solve);
}