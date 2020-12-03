#include "general.hpp"


bool contain(string a, string b) {
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

int overlap(string a, string b) {
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

int main() {
    auto set = LoadTestcase<string, string>(__FILE__);
    Run2(set, contain);
}