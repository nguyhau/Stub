#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
int x;
vector<int> cfg(3);
vector<int> min_cfg(3);
int min_v = INT_MAX;
int ans = 0;
string result="23:59:59";
string temp="";
char ch;
bool check_cfg(vector<int> cfg) {   
    int enc =0, value = 0;
    enc = cfg[0] | (cfg[1]<<1) | (cfg[2]<<2);
    temp="";
    for (int i=2;i>=0;i--){
        value += cfg[i]%10 + cfg[i]/10;
        ch = cfg[i]/10+ 48;
        temp +=ch;
        ch = cfg[i]%10+ 48;
        temp +=ch;
        if (i) temp += ':';
    }    
    if (enc==x) {
        if (min_v >= value) {      
            min_v = value;
            if (result > temp) result = temp;
        }
        return true;
    }
    return false;
}
int bt(int idx) {
    if (idx == 3) {
        if (check_cfg(cfg)) {
            ans++;
        };
        return 1;
    }    
    int max_v = 59;
    if (idx == 2) max_v = 23;
    for (int i=0; i<= max_v; i++) {
        cfg[idx] = i;
        bt(idx+1);
    }
    return 1;
    
}
int number_encode(int x) {
    int ret = 0;
    ret = bt(0);
    return ret;
}
int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    cin>>x;
    number_encode(x);
    cout<<ans<<endl;
    if (ans) cout<<result<<endl;
    return 0;
}

