#include <iostream>
#include <vector>
#include <string>
#include <map>

using std::map;
using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, name;
    int number;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    
    map<string,int>name_to_phone;
    map<int,string>phone_to_name;
    
    for (size_t i = 0; i < queries.size(); ++i)
        if (queries[i].type == "add") {
            //re-write
            if(phone_to_name.find(queries[i].number) != phone_to_name.end()){
                string prev_name = phone_to_name[ queries[i].number ];
                phone_to_name[ queries[i].number ] = queries[i].name;
                name_to_phone[ queries[i].name ] = queries[i].number;
                name_to_phone.erase(prev_name);
            } else {
                phone_to_name[ queries[i].number ] = queries[i].name;
                name_to_phone[ queries[i].name ] = queries[i].number; 
            }
        } else if (queries[i].type == "del") {
                name_to_phone.erase( phone_to_name[queries[i].number] );
                phone_to_name.erase(queries[i].number);
        } else {
            string response = "not found";
            if(phone_to_name.find(queries[i].number) != phone_to_name.end())
                response = phone_to_name[queries[i].number];
            result.push_back(response);
        }
    return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
