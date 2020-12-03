#ifndef _HELPER_H_
#define _HELPER_H_

/* c library */
#include <cstdio>
#include <cstdlib>

/* container header */
#include <queue>
#include <stack>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>

/* input output header*/
#include <iostream>
#include <fstream>
#include <sstream>

/* Other */
#include <bitset>
#include <string>
#include <algorithm>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int v):val(v){};
};

void trimLeftTrailingSpaces(string &input);
void trimRightTrailingSpaces(string &input);
vector<int> stringToIntegerVector(string input);
ListNode* stringToListNode(string input);
void ppLinkedList(ListNode* node);
void ppIntegerVector(vector<int>& vec);
void ppStringVector(vector<string>& vec);
void ppInteger(int x);
#endif