#include "general.hpp"
int n, k;
vector<int> Rank, tmp;

bool compare_sa(int i, int j) {
    if (Rank[i] != Rank[j]) return Rank[i] < Rank[j];
    else {
        int ri = i + k <= n ? Rank[i + k] : -1;
        int rj = j + k <= n ? Rank[j + k] : -1;
        return ri < rj;
    }
}

vector<int> construct_sa(string S) {
    n = S.length();
    vector<int> sa(n + 1);
    Rank.assign(n + 1, 0);
    tmp.assign(n + 1, 0);

    for (int i = 0; i <= n; i++) {
        sa[i] = i;
        Rank[i] = i < n ? S[i] : -1;
    }
    cout << sa << endl;
    for (k = 1; k <= n; k *= 2) {
        sort(sa.begin(), sa.end(), compare_sa);
        cout << sa << endl;

        tmp[sa[0]] = 0;
        for (int i = 1; i <= n; i++) {
            tmp[sa[i]] = tmp[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
            cout << sa[i] << " " << tmp[sa[i]] << endl;
        }
        for (int i = 0; i <= n; i++) {
            Rank[i] = tmp[i];
        }
        cout << "Rank: " << Rank << endl;
    }
    return sa;
}

bool contain(string S, int *sa, string T) {
    int a = 0, b = S.length();
    while (b - a > 1) {
        int c = (b + a) / 2;
        if (S.compare(sa[c], T.length(), T) < 0) a = c;
        else b = c;
    }
    return S.compare(sa[b], T.length(), T) == 0;
}

int main() {
    auto data = LoadTestcase<string>(__FILE__);
    Run(data, construct_sa);
}