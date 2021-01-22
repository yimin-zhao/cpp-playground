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
struct is_pair : std::false_type {};
template <typename T, typename U>
struct is_pair<std::pair<T, U>> : std::true_type {};
template <typename T>
inline constexpr bool is_pair_v = is_pair<T>::value;

template <typename T>
struct has_output_function {
  template <class U>
  static auto output(U* ptr)
    -> decltype(std::declval<std::ostream&>() << *ptr,
                std::true_type());
  template <class U>
  static std::false_type output(...);
  static constexpr bool value = decltype(output<T>(nullptr))::value;
};
template <typename T>
inline constexpr bool has_output_function_v = has_output_function<T>::value;

template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& pr);

template <typename T, typename Cont>
auto output_element(std::ostream& os, const T& element,
                    const Cont&, std::true_type)
    -> decltype(std::declval<typename Cont::key_type>(), os);

template <typename T, typename Cont>
auto output_element(std::ostream& os, const T& element,
                    const Cont&, ...)
    -> decltype(os);

template <typename T,
          typename = std::enable_if_t<!has_output_function_v<T>>>
auto operator<<(std::ostream& os, const T& container)
    -> decltype(container.begin(), container.end(), os)
{
  using std::decay_t;
  using std::is_same_v;

  using element_type = decay_t<decltype(*container.begin())>;
  constexpr bool is_char_v = is_same_v<element_type, char>;
  if constexpr (!is_char_v) {
    os << '{';
  }
  auto end = container.end();
  bool on_first_element = true;
  for (auto it = container.begin(); it != end; ++it) {
    if constexpr (is_char_v) {
      if (*it == '\0') {
        break;
      }
    } else {
      if (!on_first_element) {
        os << ", ";
      } else {
        os << ' ';
        on_first_element = false;
      }
    }
    output_element(os, *it, container, is_pair<element_type>());
  }

  if constexpr (!is_char_v) {
    if (!on_first_element) {
      os << ' ';
    }
    os << '}';
  }
  return os;
}

template<typename T, typename Cont>
auto output_element(std::ostream& os, const T& element,
                    const Cont&, std::true_type)
    -> decltype(std::declval<typename Cont::key_type>(), os)
{
  os << element.first << " => " << element.second;
  return os;
}

template <typename T, typename Cont>
auto output_element(std::ostream& os, const T& element,
                    const Cont&, ...)
    -> decltype(os)
{
  os << element;
  return os;
}

template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& pr) {
  os << '(' << pr.first << " , " << pr.second << ')';
  return os;
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