#include "general.hpp"
#include "sort.hpp"

int main() {
  vector<int> vec = {43, 64, 12, 65, 87, 27, 124, 76, 23, 65, 15, 65, 32, 1, 64, 88, 92, 9};
  yao::Heap hp(vec.size());
  for (auto num : vec) {
    hp.push(num);
    cout << hp.data << endl;
  }
  hp.sort();
  cout << hp.data << endl;
}