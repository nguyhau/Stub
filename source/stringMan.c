//https://www.hackerrank.com/contests/spct2025batch-5-pretest-1/challenges/password-24

#include <bits/stdc++.h>
using namespace std;
long long x;
string s_x="";
#define num 64
int main() {
    cin>>x;
    std::bitset<64> mybits(x);
    int count = mybits.count();
    int top_idx;
    for(int i= count; i< 64; i++) if ((1<<i) > x) {
        top_idx = i;
        break;
    }
    //cout<<top_idx<<endl;
    std::string mystring = mybits.to_string<char,std::string::traits_type,std::string::allocator_type>();
    //cout<<mystring<<endl;
    // calculate a
    int idx = -1;
    for(int i=62; i>(63-top_idx); i--) if((mystring[i]=='1')&&(mystring[i+1]=='0')){// .. 10..
        idx = i;
        break;
    }
    if (idx > 0) {
        std::string str2 = mystring.substr (0,idx);
        str2+="01";
        std::bitset<64> baz (str2);
        //cout<<str2<<endl;
        int rest = count-baz.count();
        for(int j= 0; j<rest; j++) str2+='1';
        while (str2.length()<64) str2+='0';
        //cout<<str2<<endl;
        std::string::size_type sz = 0;
        cout<<std::stoull(str2,&sz,2)<<" ";
    } else {
        cout<<"0"<<" ";
    }
    //cout<<endl<<mystring<<endl;
    idx = -1;
    for(int i=62; i>(63-top_idx); i--) if((mystring[i]=='0')&&(mystring[i+1]=='1')){// .. 01..
        idx = i;
        break;
    }
    std::string str2;
    if (idx > 0) { // exist pos
        str2 = mystring.substr (0,idx);
    } else {
        str2 = mystring.substr (0,63-top_idx);
    }
    str2+="10";
    std::bitset<64> baz (str2);
    //cout<<str2<<endl;
    int rest = count-baz.count();
    while (str2.length()<(64-rest)) str2+='0';
    for(int j= 0; j<rest; j++) str2+='1';
    //cout<<str2<<endl;
    std::string::size_type sz = 0;
    cout<<std::stoull(str2,&sz,2)<<endl;
    return 0;
}
// https://www.hackerrank.com/contests/spct2024batch-2-pretest-1/challenges/encode-password/problem
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    string ans;
    string inp;
    cin>>inp;
    int i= inp.length()-1;
    while (i>=0) {
        int j=i;
        string tmp;
        if (inp[j]=='0') {
            j=j-2;
            tmp = inp.substr(j,2);
        }else {
            tmp = inp.substr(j,1);
        }
        //cout<<tmp<<"\n";
        char c = stoi(tmp)-1+'a';
        ans+=c;
        //cout<<ans<<"\n";
        i=j-1;
    }
    cout<<ans<<"\n";
    return 0;
}
//https://www.hackerrank.com/contests/spct2025batch-5-pretest-1/challenges/words-malnipulation/problem
// Traver reverse way
#include <bits/stdc++.h>
using namespace std;

string x;
string y;
int main() {
    queue<string> q;
    cin>>x>>y;
    bool flag = true;
    q.push(y);
    int len_x = x.length();   
    if (y.length() < x.length()) {
        cout<<"NO";
        return 0;
    }
    while (q.size()>0) {
        string a = q.front();
        q.pop();
        if (a.length() > len_x){
            if (a.back()=='A') {
                a.pop_back();
                q.push(a);
            } else if (a.back()=='B') {
                a.pop_back();
                reverse(a.begin(), a.end());
                q.push(a);
            } 
        } else {
            if (a.compare(x) == 0) {
                flag = false;
                cout<<"YES";
                break;
            }        
        }
    }
    if (flag) cout<<"NO";
    return 0;
}
//https://www.hackerrank.com/contests/spct2024batch-2-pretest-4/challenges/binary-path-1
#include <bits/stdc++.h>
using namespace std;
int n;
vector<vector<char>> mt;
vector<vector<string>> str;


int main() {
    cin>>n;
    mt.resize(n, vector<char>(n));
    str.resize(n, vector<string>(n,""));
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++) cin>>mt[i][j];
    str[0][0] +=mt[0][0]; 
    for(int j=1; j<n; j++) str[0][j]=str[0][j-1]+mt[0][j];
    for(int i=1; i<n; i++){
        str[i][0]=str[i-1][0]+mt[i][0];
        for(int j=1; j<n; j++) str[i][j]=max(str[i][j-1],str[i-1][j])+mt[i][j];
    }
    string::size_type sz = 0;
    cout<<std::stoll(str[n-1][n-1],&sz,2);
    return 0;
}