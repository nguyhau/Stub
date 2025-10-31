#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

int n,m,x;
//bool great();
int min_value = INT_MAX;
vector<int> cfg;
bool check_cfg(vector<int>& cfg) {
    for (int i=1; i<=m; i++) {
        if (cfg[i] < x) return false;
    }
    if (cfg[0] <= min_value) min_value = cfg[0];
    return true;
}
void bt(const vector<vector<int>>& value,const int index ) {
    //check cfg
    if (check_cfg(cfg)) return ;
    if (index == n) return ;
    // break the branch has lower bound exceed target
    if (*min_element(cfg.begin() + 1, cfg.end()) >= x) {
        if (cfg[0] <= min_value) min_value = cfg[0];
        return;
    }
    // add index
    for (int i=0; i<=m; i++) {
            cfg[i]+= value[index][i];
    }
    bt(value, index+1);
    // restore
    for (int i=0; i<=m; i++) {
            cfg[i]-= value[index][i];
    }
    bt(value, index+1);
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   

    int ret = -1;
    cin>>n>>m>>x;
    cfg.resize(m+1,0);
    
    vector<vector<int>> v(n+1,vector<int> (m+1,0));
    
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<= m; j++) {
           cin>>v[i][j];
           v[n][j] += v[i][j]; 
        }
    }

    for (int j = 1; j<= m; j++) if (v[n][j] < x) {
        cout<<-1;
        return 0;
    }
    min_value = v[n][0];
    
    bt(v, 0);
    cout<<min_value<<endl;
    return 0;
}
