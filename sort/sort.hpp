#include "general.hpp"

namespace yao {

class Heap {
public:
  Heap(size_t size): sz(0), data(vector<int>(size, 0)) {};

  void push(int x) {
    int i = sz++;
    while (i > 0) {
      int pos = (i - 1) / 2;
      if (data[pos] <= x) break;
      data[i] = data[pos];
      i = pos;
    }
    data[i] = x;
  }

  int pop() {
    int res = data[0];
    int x = data[--sz];
    int i = 0;
    while (i * 2 + 1 < sz) {
      int a = i * 2 + 1, b = i * 2 + 2;
      if (b < sz && data[b] < data[a]) a = b;
      if (data[a] >= x) break;
      data[i] = data[a];
      i = a;
    }
    data[i] = x;
    return res;
  }

  void sort() {
    int i = sz;
    while (i > 0)
      data[--i] = pop();
  }

public:
  vector<int> data;
  int sz = 0;
};
}