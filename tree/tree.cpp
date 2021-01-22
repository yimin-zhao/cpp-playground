#include "tree.hpp"

enum Color { Red, Black };

struct RBNode {
  int data;
  bool color;
  RBNode *left, *right, *parent;
  RBNode(int data)
      : data(data), left(nullptr), right(nullptr), parent(nullptr),
        color(Red){};
};

class RBTree {
public:
  RBTree() { root = nullptr; }
  void insert(const int &n);
  void inorder();
  void levelOrder();

  void rotateLeft(RBNode *&, node *&);
private:
  RBNode *root;
};