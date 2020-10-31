#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif
using std::pair;
class Node;

class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
      this->parent = NULL;
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
    int height_of_tree(){
        std::queue< pair<Node *,int> >q;
        q.push({this,0});
        int height = 0;
        while(!q.empty()){
            pair< Node*, int> f = q.front();
            q.pop();
            height = std::max(f.second,height);
            for(int i = 0; i < f.first->children.size(); i++){
                q.push({f.first->children[i],f.second + 1});
            }
        }
        return height + 1;
    }
};


int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  std::cin >> n;

  std::vector<Node> nodes;
  nodes.resize(n);
  int parent_index_among_nodes;
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    std::cin >> parent_index;
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
    else parent_index_among_nodes = child_index;
    nodes[child_index].key = child_index;
  }

  // Replace this code with a faster implementation
  /*int maxHeight = 0;
  for (int leaf_index = 0; leaf_index < n; leaf_index++) {
    int height = 0;
    for (Node *v = &nodes[leaf_index]; v != NULL; v = v->parent)
      height++;
    maxHeight = std::max(maxHeight, height);
  }*/
    
  std::cout << nodes[parent_index_among_nodes].height_of_tree() << std::endl;
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }

#endif
  return main_with_large_stack_space();
}
