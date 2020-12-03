#include "general.hpp"

vector<vector<ull>> col, row;

ull compute(vector<string> a, int p, int q) {
    int n = a.size(), m = a[0].size();
    ull t1 = 1;
    for (int i = 0; i < q; i++) t1 *= mod;

    for (int i = 0; i < n; i++) {
        ull e = 0;
        for (int j = 0; j < q; j++)
            e = e * mod + a[i][j];

        for (int j = 0; j + q <= m; j++) {
            row[i][j] =  e;
            if (j + q < m)
                e = e * mod - t1 * a[i][j] + a[i][j + q];
        }
    }

    ull t2 = 1;
    for (int i = 0; i < p; i++) t2 *= prime2;

    for (int j = 0; j + q <= m; j++) {
        ull e = 0;
        for (int i = 0; i < p; i++)
            e = e * prime2 + row[i][j];

        for (int i = 0; i + p <= n; i++) {
            col[i][j] = e;
            if (i + p < n)
                e = e * prime2 - t2 * row[i][j] + row[i + p][j];
        }
    }
    return col[0][0];
}

int solve(vector<string> a, vector<vector<string>> patterns) {
    int n = a.size(), m = a[0].size(),
        p = patterns[0][0].size(), q = patterns[0].size(),
        T = patterns.size();
    multiset<ull> unseen;

    for (int k = 0; k < T; k++)
        unseen.insert(compute(patterns[k], p, q));

    compute(a, p, q);
    for (int i = 0; i + p <= n; i++) {
        for (int j = 0; j + q <= m; j++) {
            unseen.erase(col[i][j]);
        }
    }

    return T - unseen.size();
}

int main() {
    auto src = LoadTestcase<vector<string>, vector<vector<string>>>(__FILE__);
    Run2(src, solve);
}