//https://www.hackerrank.com/contests/spct2025batch-5-practice-1/challenges/jump-quest

#include <bits/stdc++.h>
using namespace std;
int n,s;
vector<pair<int,int>> pad;
int pad_count;
int des_count;
int max_des = 0;
vector<bool> vst;
int main() {
    cin>>n>>s;
    pad.resize(n+1);
    vst.resize(n+1, false);
    des_count = 0;
    for(int i=1; i<=n; i++) {
        cin>>pad[i].first>>pad[i].second;
        if (pad[i].first == 1)max_des++;
    }    
    int sig = 1;
    int strength = 1;
    des_count = 0;
    set<vector<int>> vs;
    while ((des_count < max_des)&&(s<=n)&& (s>0)) {
        // cout << s;
        // cout << sig;
        // cout << strength<< endl;
        vector<int> st={s, strength, sig};
        if (vs.count(st)) break;
        vs.insert(st);
        if(pad[s].first == 1){
            if ((pad[s].second <= strength)&&!vst[st[0]]) {
                des_count++;
                vst[st[0]] = true;
            }
        } else {
            strength += pad[s].second;
            sig *= (-1);
        }
        s += strength*sig;
    }
    cout<<des_count;
    return 0;
}