#include <bits/stdc++.h>
using std::priority_queue;
using std::vector;
using std::cin;
using std::cout;
using std::pair;
using std::greater;
class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  struct min_heap{
      int size = 0;
     pair<long long, int>  tree[100005];//<start_time ,worker_index>
    pair<long long,int> ExtractMin(){
        pair < long long ,int> top = tree[0];
        swap(tree[size - 1],tree[0]);
        size--;
        siftDown(0);
        return top;
    }
    void siftDown(int index){
        int min_index = index;
        
        //let's see left
        if(index * 2 + 1 < size && tree[min_index].first > tree[index * 2 + 1].first){
            min_index = index * 2 + 1;
        }else if(index * 2 + 1 < size && tree[min_index].first == tree[index * 2 + 1].first && tree[min_index].second > tree[index * 2 + 1 ].second){
            min_index = index * 2 + 1;
        }
        
        
        if(index * 2 + 2 < size && tree[min_index].first > tree[index * 2 + 2].first){
            min_index = index * 2 + 2;
        }else if(index * 2 + 2 < size && tree[min_index].first == tree[index * 2 + 2].first && tree[min_index].second > tree[index * 2 + 2 ].second){
            min_index = index * 2 + 2;
        }
        if(index == min_index)return;
        swap(tree[index],tree[min_index]);
        siftDown(min_index);
    }
    void insert(pair<long long,int>node){
        tree[size++] = node;
        siftUp(size - 1);
    }
    void siftUp(int index){
        if(index == 0 )return;
        int parent_index;
       
        if(index % 2 == 0){
            parent_index = (index - 2 )/2;
        }else {
            parent_index = (index - 1 )/2;
        }
        
        if(tree[index].first < tree[parent_index].first){
            swap(tree[index],tree[parent_index]);
            siftUp(parent_index);
        }else if(tree[index].first == tree[parent_index].first && tree[index].second < tree[parent_index].second){
            swap(tree[index],tree[parent_index]);
            siftUp(parent_index);
        }
    }
  };
  
  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }
  void AssignJobs() {
       assigned_workers_.resize(jobs_.size());
       start_times_.resize(jobs_.size());
       struct min_heap q;
       for(int i = 0; i < num_workers_; i++){
           q.insert({0,i});
       }
       for(int i = 0 ;i < jobs_.size();i++){
           pair<long long ,int> curr_thread = q.ExtractMin();
           assigned_workers_[i] = curr_thread.second;
           start_times_[i] = curr_thread.first;
           curr_thread.first = curr_thread.first + jobs_[i];
           q.insert(curr_thread);
       }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
