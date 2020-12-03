#include "general.hpp"

const char *AGCT = "AGCT";

int solve(int N, string S) {
  int K = S.size(), res = 0;
  vector<vector<int>> prefix(K, vector<int>(4)), dp(N + 1, vector<int>(K));

  for (int i = 0; i < K; i++) {
    for (int j = 0; j < 4; j++) {
      string s = S.substr(0, i) + AGCT[j];
      // cout << s << endl;
      while (S.substr(0, s.length()) != s) {
        s = s.substr(1);
      }
      prefix[i][j] = s.length();
    }
  }
  cout << prefix;

  dp[0][0] = 1;

  for (int t = 0; t < N; t++) {
    for (int i = 0; i < K; i++) {
      for (int j = 0; j < 4; j++) {
        int ti = prefix[i][j];
        if (ti == K) continue;
        dp[t + 1][ti] = (dp[t + 1][ti] + dp[t][i]) % mod;
        // cout <<"dp: " << t + 1 << ", "  << ti << " += " << dp[t][i] << endl;
      }
    }
  }
  cout << dp;

  for (int i = 0; i < K; i++) res = (res + dp[N][i]) % mod;

  return res;
}

int main() {
  auto set = LoadTestcase<int, string>(__FILE__);
  Run2(set, solve);
  return 0;
}