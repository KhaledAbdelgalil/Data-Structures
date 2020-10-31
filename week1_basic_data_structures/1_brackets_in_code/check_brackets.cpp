#include <iostream>
#include <stack>
#include <string>
using std::cout;
using std::endl;

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    Bracket()
    {}
    
    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);
    bool found_ans = 0;
    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
            Bracket B(next,position);
            opening_brackets_stack.push(B);
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
            if(opening_brackets_stack.empty()){
                cout<<position + 1<<endl;
                found_ans = 1;
                break;
            }
            else {
                Bracket B = opening_brackets_stack.top();
                opening_brackets_stack.pop();
                if(B.Matchc(next)) continue;
                else{
                    cout<<position + 1<<endl;
                    found_ans = 1;
                    break;
                }
            }
        }
    }

    // Printing answer, write your code here
    if(found_ans == 0){
        if(opening_brackets_stack.empty())cout<<"Success"<<endl;
        else{
            Bracket B;
            while(!opening_brackets_stack.empty()){
                B = opening_brackets_stack.top();
                opening_brackets_stack.pop();
            }
            cout<<B.position + 1<<endl;
        }
    }
    return 0;
}
