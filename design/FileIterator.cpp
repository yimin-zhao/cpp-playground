struct Record {
  unsigned int timestamp;
  string msg;
}

class FileIterator {
private:
  file *f;

public:
  bool HasNextLine();
  Record ReadNextLine();
};

using RC = pair<Record, FileIterator*>;

class CompRecord {
public:
  bool operator() (const RC& rc1, const RC& rc2) {
    return rc1.first.timestamp < rc2.first.timestamp;
  }
};

class SystemS {
private:
  vector<FileIterator*> fileIterators;
  // 优先队列que按照文件的时间戳进行排序，队首总是时间戳最小的数据。
  priority_queue<RC, vector<RC>, CompRecord> que;

public:
  SystemS(vector<FileIterator*> vec);
  bool HasNext();
  void Consume(Entry& entry);
};

SystemS::SystemS(vector<FileIterator*> vec) {
  fileIterators = vec;

  // 如果优先队列que为空，那么首先构建优先队列，从所有的文件中取下一条
  // 记录，然后插入到优先队列中，完成后队列的大小为所有的文件数量，队列
  // 的顶端为最新的一条数据
  if (que.empty()) {
    for (auto& iter : fileIterators) {
      if (iter->HasNextLine()) {
        auto record = iter->ReadNextLine();
        que.push({record, iter});
      } else {
        deleteList.push_back(iter);
      }
    }
  }
}

bool SystemS::HasNext() {
  return !que.empty() || !fileIterators.empty();
}

void SystemS::Consume(Entry& entry) {
  vector<FileIterator*> deleteList;
  // 取出最新的一条数据，并且将他对应文件的下一条记录也插入到队列中。
  // 保持队列的大小等于所有的文件数量 N。
  // 如果对应文件已经读完，则加入到清理队列中等待资源释放
  auto [latestRecord, iter] = que.top();
  que.pop();
  if (iter->hasNextLine()) {
    auto nextRecord = iter->ReadNextLine();
    que.push({nextRecord, iter});
  } else {
    deleteList.push_back(iter);
  }

  // 处理当前最近记录
  entry = Process(latestRecord);

  // 清理空文件
  Cleanup(deleteList);
}

// 复杂度分析
// 文件数量为 N，第一次初始化系统时为 O(NlogN), 以后每次执行Consume为 O(logN)
// 空间复杂度：系统实时保存 N个文件迭代器以及最新的N条记录

// 在实际场景中，读取文件IO耗时通常远远大于文件记录的处理时间，因此应该根据系统的内存
// 大小，尽可能多的缓存数据，例如每个文件的前1000条数据。