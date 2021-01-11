#ifndef __GENERAL_H_
#define __GENERAL_H_

#include <algorithm>
#include <chrono>
#include <numeric>
#include <memory>

#include <string>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <iostream>

#include <map>
#include <set>
#include <queue>
#include <tuple>
#include <vector>

#include <climits>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include <unistd.h>

using namespace std;
using namespace std::chrono;

namespace fs = std::filesystem;

/*
 *  Typedef
 */
typedef unsigned long long ull;

/*
 * Frequent constant numbers
 */
const int mod = 1e9 + 7;
const int MAX_K = 1e5;
const int MAX_N = 1e5;
const int MAX_E = 1e5;
const int MAX_V = 1e5;

const int prime1 = 9973;  // 1e5 - 27
const int prime2 = 19260817;
const int prime3 = 99999989;  // 1e8 - 11

/*
 * Basic structure definitions
 */

struct Edge {
  int from, to, cost;
};

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int v) : val(v) {}
};

struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode(int v, TreeNode* l, TreeNode* r) : val(v), left(l), right(r) {}
  TreeNode(int v) : val(v) {}
};

/*
 *  Input Convertor Functions
 */
int stringToInteger(string input);
vector<int> stringToIntegerVector(string input);
vector<string> stringToStringVector(string input);
ListNode* stringToListNode(string input);

/*
 * PrettyPrint Functions
 */
void prettyPrintVector(vector<int>& vec);
void prettyPrint2DVector(vector<vector<int>>& vec);
void prettyPrintLinkedList(ListNode* node);
void prettyPrintTree(TreeNode* node, string prefix = "", bool isLeft = true);

/*
 * Helper Functions
 */
void recordStartTime();
void recordEndTime();
void showResourceUsage();

ifstream GetDataStream(const char*);

/*
 * Template Functions
 */

template <typename T>
T stringTo(ifstream& in) {
  string input;
  if (!(in >> input)) throw "Not enought data";
  /* TODO
   * stringToListNode
   * stringToTreeNode
   * stringToIntVectorVector
   * stringToStringVectorVector
   */
  if constexpr (is_integral<T>::value)
    return stringToInteger(input);
  else if constexpr (is_same<T, vector<int>>::value)
    return stringToIntegerVector(input);
  else if constexpr (is_same<T, vector<string>>::value)
    return stringToStringVector(input);
  else /* default string */
    return (T)input;
}

template <typename T1, typename T2, typename T3>
vector<tuple<T1, T2, T3>> LoadTestcase(const char* source) {
  vector<tuple<T1, T2, T3>> caseSet;
  auto infile = GetDataStream(source);

  while (!infile.eof()) {
    auto tp = make_tuple(stringTo<T1>(infile), stringTo<T2>(infile),
                         stringTo<T3>(infile));
    caseSet.push_back(tp);
  }
  infile.close();
  return caseSet;
}

template <typename T1, typename T2>
vector<tuple<T1, T2>> LoadTestcase(const char* source) {
  vector<tuple<T1, T2>> caseSet;
  auto infile = GetDataStream(source);

  while (!infile.eof()) {
    auto tp = make_tuple(stringTo<T1>(infile), stringTo<T2>(infile));
    caseSet.push_back(tp);
  }
  infile.close();
  return caseSet;
}

template <typename T>
vector<T> LoadTestcase(const char* source) {
  vector<T> caseSet;
  auto infile = GetDataStream(source);

  while (!infile.eof()) {
    caseSet.push_back(stringTo<T>(infile));
  }
  infile.close();
  return caseSet;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& vec) {
  os << "[";
  for (auto ele : vec) os << ele << ", ";
  os << "]" << endl;
  return os;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& vec) {
  os << "^" << endl;
  int line = 0;
  for (auto row : vec) {
    os << line++ << "  [ ";
    for (auto ele : row) os << ele << ", ";
    os << "]" << endl;
  }
  os << "V" << endl;
  return os;
}

/*
 *  Utility Class
 */
class UnionFind {
public:
  UnionFind(int v) {
    vec.assign(v, -1);
  }

  bool Same(int u, int v) {
    while (vec[u] != v)
      vec[u] = v;
    return vec[u] = v;
  }

  void Unite(int u, int v) {
    vec[v] = vec[u];
  }
private:
  vector<int> vec;
};

/*
 * Macros definition
 */
#define Run(testcase, func)                  \
  {                                          \
    for (auto ele : testcase) {              \
      recordStartTime();                     \
      auto res = func(ele);                  \
      cout << "*** Return: " << res << endl; \
      recordEndTime();                       \
      showResourceUsage();                   \
    }                                        \
    return 0;                                \
  }

#define Run2(testcase, func)                 \
  {                                          \
    for (auto ele : testcase) {              \
      recordStartTime();                     \
      auto res = apply(func, ele);           \
      cout << "*** Return: " << res << endl; \
      recordEndTime();                       \
      showResourceUsage();                   \
    }                                        \
    return 0;                                \
  }

#endif