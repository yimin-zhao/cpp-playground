#include "general.hpp"

vector<vector<int>> nSumTarget(vector<int>& nums, int n, int start, int target) {
  int sz = nums.size();
  vector<vector<int>> res;
  if (n < 2 || sz < n) return res;
  if (n == 2) {
    int lo = start, hi = sz - 1;
    while (lo < hi) {
      int left = nums[lo], right = nums[hi], sum = left + right;
      if (sum < target) {
        while (lo < hi && left == nums[lo]) lo++;
      } else if (sum > target) {
        while (lo < hi && right == nums[hi]) hi++;
      } else {
        res.push_back({left, right});
        while (lo < hi && left == nums[lo]) lo++;
        while (lo < hi && right == nums[hi]) hi++;
      }
    }
  } else {
    for (int i = start; i < sz ; i++) {
      auto cur = nSumTarget(nums, n - 1, i + 1, target - nums[i]);
      for (auto& arr : cur) {
        arr.push_back(nums[i]);
        res.push_back(arr);
      }
      while (i < sz && nums[i] == nums[i + 1]) i++;
    }
  }
  return res;
}

int solve(vector<int> A) {
  sort(begin(A), end(A));
  nSumTarget(A, 3, 0, 0);
  return 0;
}