#include "general.hpp"

void trimLeftTrailingSpaces(string& input) {
  input.erase(input.begin(), find_if(input.begin(), input.end(),
                                     [](int ch) { return !isspace(ch); }));
}

void trimRightTrailingSpaces(string& input) {
  input.erase(
      find_if(input.rbegin(), input.rend(), [](int ch) { return !isspace(ch); })
          .base(),
      input.end());
}

vector<int> stringToIntegerVector(string input) {
  vector<int> output;
  trimLeftTrailingSpaces(input);
  trimRightTrailingSpaces(input);
  input = input.substr(1, input.length() - 2);
  stringstream ss;
  ss.str(input);
  string item;
  char delim = ',';
  while (getline(ss, item, delim)) {
    output.push_back(stoi(item));
  }
  return output;
}

vector<string> stringToStringVector(string input) {
  vector<string> output;
  trimLeftTrailingSpaces(input);
  trimRightTrailingSpaces(input);
  input = input.substr(1, input.length() - 2);
  stringstream ss;
  ss.str(input);
  string item;
  char delim = ',';
  while (getline(ss, item, delim)) {
    output.push_back(item);
  }
  return output;
}

ListNode* stringToListNode(string input) {
  // Generate list from the input
  vector<int> list = stringToIntegerVector(input);

  // Now convert that list into linked list
  ListNode* dummyRoot = new ListNode(0);
  ListNode* ptr = dummyRoot;
  for (int item : list) {
    ptr->next = new ListNode(item);
    ptr = ptr->next;
  }
  ptr = dummyRoot->next;
  delete dummyRoot;
  return ptr;
}

void prettyPrintTree(TreeNode* node, string prefix, bool isLeft) {
  if (node == nullptr) {
    cout << "Empty tree";
    return;
  }

  if (node->right) {
    prettyPrintTree(node->right, prefix + (isLeft ? "│   " : "    "), false);
  }

  cout << prefix + (isLeft ? "└── " : "┌── ") + to_string(node->val) + "\n";

  if (node->left) {
    prettyPrintTree(node->left, prefix + (isLeft ? "    " : "│   "), true);
  }
}

void prettyPrintLinkedList(ListNode* node) {
  while (node && node->next) {
    cout << node->val << "->";
    node = node->next;
  }

  if (node) {
    cout << node->val << endl;
  } else {
    cout << "Empty LinkedList" << endl;
  }
}

int stringToInteger(string input) { return stoi(input); }

decltype(high_resolution_clock::now()) start;

void recordStartTime() {
  start = high_resolution_clock::now();
  cout << endl
       << "***********************************************************" << endl
       << "******************** Start Running ************************" << endl;
}

void recordEndTime() {
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout << "*** Solution took: " << duration.count() << " us" << endl;
}

void showResourceUsage() {
  ifstream proc("/proc/self/stat", ios_base::in);
  string _;
  long vm_usage, resident_set, vsize, rss;

  for (int i = 0; i < 22; i++) proc >> _;
  proc >> vsize >> rss;
  proc.close();

  long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024;
  vm_usage = vsize / 1024.0;
  resident_set = rss * page_size_kb;
  cout << "*** Used Memory: " << vm_usage << " kb" << endl
       << "*** Resident set size: " << resident_set << " kb" << endl;
  cout << "***********************************************************\n" << endl;
}

ifstream GetDataStream(const char* source) {
  fs::path s(fs::current_path().string() + "/build/" + source);
  ifstream infile(s.parent_path().string() + "/" + s.stem().string() + ".txt");
  return infile;
}

