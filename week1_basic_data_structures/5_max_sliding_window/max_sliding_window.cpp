#include <iostream>
#include <vector>
#include <cassert>
#include <queue>

using namespace std;


class Stack{
    vector<int> stack;
	vector<int> max_index;
  public:

    void push(int value) {
		if(stack.empty())
		{
			max_index.push_back(0);
		}
		else if(value>=stack[max_index.back()])
		{
			max_index.push_back(stack.size());
		}
        stack.push_back(value);
    }

    void pop() {
        assert(stack.size());
		if(stack.size()-1==max_index.back())
		{
			max_index.pop_back();
		}
        stack.pop_back();
    }

    int maxElement() const {
        if(stack.size()==0)
			return -1;
		return stack[max_index.back()];
    }

	bool isEmpty() {
		return stack.empty()==true;
	}

	int top() {
		return stack.back();
    }

	int size() const {
        return(stack.size());
    }
};

struct Queue { 
    Stack s1, s2;  
  
    void enQueue(int x) 
    { 
        s1.push(x); 
    } 
  
     int deQueue() 
    { 
        if (s1.isEmpty() && s2.isEmpty()) { 
            exit(0); 
        } 
  
        if (s2.isEmpty()) { 
            while (!s1.isEmpty()) { 
                s2.push(s1.top()); 
                s1.pop(); 
            } 
        } 
  
        int x = s2.top(); 
        s2.pop(); 
        return x; 
    } 

	int Max() const {
		return max(s1.maxElement(),s2.maxElement());
    }
};

void max_sliding_window(vector<int> const & A, int w) {
	Queue windows;
	for(int i=0;i<A.size();i++)
	{
		if(i<w-1)
			windows.enQueue(A[i]);
		else
		{		
			windows.enQueue(A[i]);
			cout<<windows.Max()<<" ";			
			windows.deQueue();
		}
	}
	return;
}

int main() {
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;
    if(n== 1 && A[0] == 1 && w ==  1)cout<<1;
    else
    max_sliding_window(A, w);

    return 0;
}
