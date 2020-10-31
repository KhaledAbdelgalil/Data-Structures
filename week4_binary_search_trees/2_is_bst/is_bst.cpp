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
vector<Node> v;
vector<int> compared;

void in_order(int node, vector<int> & res){
    if(node == -1)return;
    in_order(v[node].left,res);
    res.push_back(v[node].key);
    in_order(v[node].right,res);
}
bool IsBinarySearchTree(const vector<Node>& tree) {
  // Implement correct algorithm here
  if(tree.size() == 0 || tree.size() == 1)return true;
  vector <int> result;
  v = tree;
  in_order(0,result);
  return result == compared;
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
    compared.push_back(key);
  }
  sort(compared.begin(),compared.end());
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
