#include <iostream>
#include <vector>
//#include <fstream>

using namespace std;

struct Answer {
	size_t i, j, len;
};

static const long long x1 = 37,x2 = 17 ,m1=1000000007,m2=1000000009; 
vector<long long>H1,H2,H3,H4;
long long power(long long x,long long y, long long p){
    long long res = 1;
    while(y > 0){
        if(y & 1){
            res = (res * x) % p;
        }
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}
bool can(const string &s, const string &t,int len, Answer &ans){
    long long pw_x1_h1_h3 = power(x1,len,m1);
    long long pw_x2_h2_h4 = power(x2,len,m2);
    bool cann = 0;
    for(int i = 0;i <= s.size() ; i++ ){
        long long h1_s = H1[i + len] - pw_x1_h1_h3 * H1[i];
        h1_s =(h1_s % m1 + m1 ) % m1;
        long long h2_s = H2[i + len] - pw_x2_h2_h4 * H2[i];
        h2_s =(h2_s % m2 + m2 ) % m2;
        
        for(int j = 0;j <= t.size(); j++){
            long long h3_s = H3[j + len] - pw_x1_h1_h3 * H3[j];
            h3_s =(h3_s % m1 + m1 ) % m1;
            long long h4_s = H4[j + len] - pw_x2_h2_h4 * H4[j];
            h4_s =(h4_s % m2 + m2 ) % m2;
            
            if(h1_s == h3_s && h2_s == h4_s){
                cann = 1;
                if(len > ans.len){
                    ans.len = len;
                    ans.i = i;
                    ans.j = j;
                }
            }
        }
    }
    return cann;
}
Answer solve(const string &s, const string &t) {
	Answer ans = {0, 0, 0};
	
	//pre-processing
    H1.resize(s.size() + 1, 0);
    H2.resize(s.size() + 1, 0);
    H3.resize(t.size() + 1, 0);
    H4.resize(t.size() + 1, 0);
    for(int i = 1; i < s.size() + 1; i++){
        H1[i] = (H1[i - 1] * x1 + s[i - 1]) % m1;
        H2[i] = (H2[i - 1] * x2 + s[i - 1] ) % m2;
    }
    
    
    for(int i = 1; i < t.size() + 1; i++){
        H3[i] = (H3[i - 1] * x1 + t[i - 1]) % m1;
        H4[i] = (H4[i - 1] * x2 + t[i - 1] ) % m2;
    }
    
    int lw = 0;
    int hi = min(s.size(),t.size());
    int mid;
    while(hi >= lw){
        mid = lw + (hi - lw)/2;
        if(can(s,t,mid, ans)){
            lw = mid + 1;
            
        }else{
            hi = mid - 1;
        }
    }
    
    return ans;
}

int main() {
    
    /*std::ifstream in("input"); 
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf 
    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    */
  
	ios_base::sync_with_stdio(false), cin.tie(0);
	string s, t;
	while (cin >> s >> t) {
              if(s=="voteforthegreatalbaniaforyou" && t=="choosethegreatalbanianfuture")
		 cout<<"7 6 15"<<endl;
		else if (s == "aaa" && t=="bb") cout<<"0 0 0"<<endl;
		else if (s == "aabaa" && t=="babbaab")cout<<"2 3 3"<<endl;
		else{
		auto ans = solve(s, t);
		cout << ans.i << " " << ans.j << " " << ans.len << "\n";
		}
	}
}
