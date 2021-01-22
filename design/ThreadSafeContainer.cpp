class ThreadSafeContainer {
public:
  void Put(int key, int value) {
    int h = hash(key);
    WriteLock lck(data[h].lock);
    auto& lst = data[h].l;
    for (auto it = lst.begin(); it != lst.end(); it++) {
      if ((*it).first == key) {
        (*it).second = value;
        return;
      }
    }
    lst.push_back(make_pair(key, value));
  }

  void Delete(int key) {
    int h = hash(key);
    WriteLock lck(data[h].lock);
    auto &lst = data[h].l;
    for (auto it = lst.begin(); it != lst.end(); it++) {
      if ((*it).first == key) {
        lst.erase(it);
        return;
      }
    }
  }

  bool Get(int key, int& value) {
    int h = hash(key);
    ReadLock lck(data[h].lock);
    auto& lst = data[h].l;
    for (auto it = lst.begin(); it != lst.end(); it++) {
      if ((*it).first == key) {
        value = (*it).second;
        return true;
      }
    }
    return false;
  }

private:
  using kv = pair<int, int>;
  class DataNode {
    list<kv> l;
    rwLock lock;
  };

  vector<DataNode> data;
  static const int base = 9973;
  static int hash(int key) {
    return key % base;
  }
};