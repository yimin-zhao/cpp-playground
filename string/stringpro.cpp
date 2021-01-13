#include "stringpro.hpp"

vector<int> SuffixArray(string S) {
    int n = S.length(), k;
    vector<int> sa(n + 1);
    vector<int> Rank(n + 1, 0);
    vector<int> tmp(n + 1, 0);

    auto compare_sa = [&](int i, int j) {
      if (Rank[i] != Rank[j]) return Rank[i] < Rank[j];
      else {
          int ri = i + k <= n ? Rank[i + k] : -1;
          int rj = j + k <= n ? Rank[j + k] : -1;
          return ri < rj;
      }
    };

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

bool SuffixArrayContain(string S, int *sa, string T) {
    int a = 0, b = S.length();
    while (b - a > 1) {
        int c = (b + a) / 2;
        if (S.compare(sa[c], T.length(), T) < 0) a = c;
        else b = c;
    }
    return S.compare(sa[b], T.length(), T) == 0;
}

bool RabinKarp(string a, string b) {
    int al = a.size(), bl = b.size();

    ull t = 1;
    for (int i = 0; i < al; i++) t *= mod;

    ull ah = 0, bh = 0;
    for (int i = 0; i < al; i++) {
        ah = ah * mod + a[i];
        bh = bh * mod + b[i];
    }

    for (int i = 0; i + al <= bl; i++) {

        if (ah == bh) {
            cout << bh << endl;
            return true;
        }
        if (i + al < bl) bh = bh * mod + b[i + al] - b[i] * t;
    }

    return false;
}

int RabinKarpOverlap(string a, string b) {
    int al = a.size(), bl = b.size(), res = 0;
    ull ah = 0, bh = 0, t = 1;
    for (int i = 1; i <= min(al, bl); i++) {
        ah = ah + a[al - i] * t;
        bh = bh * mod + b[i - 1];
        if (ah == bh) res = i;
        t *= mod;
    }
    return res;
}