#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool IsBinarySearchTree(const vector<Node>& tree, int node) {
  // Implement correct algorithm here
  if(tree[node].left == -1 && tree[node].right == -1)return true;//leaf
  
  if(tree[node].right == -1){
      if(tree[node].key <= tree[tree[node].left].key)return false;
      int left = tree[node].left;
      if(tree[left].right != -1 && tree[node].key <= tree[tree[left].right].key )return false;
      return IsBinarySearchTree(tree,tree[node].left);
  }else if(tree[node].left == -1){
      if(tree[node].key > tree[tree[node].right].key)return false;
      int right = tree[node].right;
      if(tree[right].left != -1 && tree[node].key > tree[tree[right].left].key )return false;
      return IsBinarySearchTree(tree, tree[node].right);
  }else{
      if(tree[node].key <= tree[tree[node].left].key)return false;
      int left = tree[node].left;
      if(tree[left].right != -1 && tree[node].key <= tree[tree[left].right].key )return false;
      if(tree[node].key > tree[tree[node].right].key)return false;
      int right = tree[node].right;
      if(tree[right].left != -1 && tree[node].key > tree[tree[right].left].key )return false;
      return IsBinarySearchTree(tree, tree[node].right) && IsBinarySearchTree(tree,tree[node].left); 
  }
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (nodes == 0 || nodes == 1 || IsBinarySearchTree(tree, 0) ){
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
