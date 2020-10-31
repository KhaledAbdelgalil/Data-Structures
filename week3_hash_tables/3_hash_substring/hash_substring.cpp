#include <iostream>
#include <string>
#include <vector>


using std::string;
typedef long long ll;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}
ll hash_func(const string &s,ll p, ll x){
    ll hash = 0;
    for(int i = s.size() - 1; i >= 0; i--){
        hash = (hash * x + s[i]) % p;
    }
    return hash;
}

std::vector<ll> precomputes(const string &t,int len,ll p,ll x){
    std::vector<ll>H(t.size() - len + 1);
    H[t.size() - len] = hash_func(t.substr(t.size() - len), p , x);
    
    ll y = 1;
    for(int i = 0; i < len; i++){
        y = (y * x) % p;
    }
    
    for(int i = t.size() - len -1 ;i >= 0; i--){
        H[i] = (x * H[ i + 1 ] + t[i] - y * t[i + len ]);
        if(H[i] < 0)H[i]=(H[i] % p) + p;
        H[i] = H[i] % p;
    }
    return H;
    
}
std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    std::vector<ll>H = precomputes(t,s.size(),8111,37);
    ll patternHash = hash_func(s,8111,37);
    
    /*for(int i = 0; i < H.size(); i++){
        std::cout<<H[i];
    }*/
    
    std::vector<int> ans;
    
    for(int i = 0; i < H.size(); i++){
        if(H[i] != patternHash)continue;
        if(t.substr(i,s.size()) == s)ans.push_back(i);
    }
    
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    
   /* std::vector<ll>H = precomputes("abacaba",3,8111,37);
    ll patternHash = hash_func("cab",8111,37);
    std::cout<<patternHash<<std::endl;
    patternHash = hash_func("aca",8111,37);
    std::cout<<patternHash<<std::endl;
    
    
    for(int i = 0; i < H.size(); i++){
        std::cout<<H[i]<<std::endl;
    }*/
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
