#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
int n,m;
vector<int> s,l;
vector<int> cfg_tmp;
bool check_valid(int d, vector<int>& s, int n) {
    bool ret = true;
    cfg_tmp[0] = (s[0] == 0)? 0:s[0]-1;
    int idx = 1;
    int pre = 0;
    int next; 
    vector<int>::iterator upper;
    while (idx < n) {
        next = cfg_tmp[idx -1]+d;        
        upper = upper_bound(s.begin(),s.end(), next);
        if (upper == s.end()) { // at end of list
            if (s[s.size()-1] < (next-1)){
                ret = false;
                break;
            }
            cfg_tmp[idx] = s[s.size()-1] + 1;
            pre = s.size()-1;
        } else { // normal case
            if ((s[upper - s.begin()-1] +2) > next ) {
                cfg_tmp[idx] = next;
                pre = upper - s.begin()-1;
            } else {
                cfg_tmp[idx] = s[upper - s.begin()] -1;
                pre = upper - s.begin() -1;
            }           
        }
        idx++;
    }
    
    return ret;
}
int get_max(vector<int>& s, int n, int m) {
    int r = 0;
    //int max_v = (s[s.size() - 1] - s[0])/(n-1);
    int max_v = s[s.size() - 1] + 1;
    for (int i=max_v+1; i>= 0; i--) {
        if (check_valid(i, s, n)) {
            r = i;
            break;
        }
    }
    return r;
    
}
bool check_valid2(vector<int>&soc, int n, int d) {
    int i = 0;
    vector<int> loc;
    int tmp = soc[0]-1;
    loc.push_back(tmp);
    vector<int>::iterator it;
    //cout<<"Check for dist "<<d<<endl;
    while ((loc.size() < n)&& (i<soc.size())) {
        tmp += d;
        // find next socket postion
        it = lower_bound(soc.begin()+i, soc.end(),tmp);
        if (it == soc.end()) {
            if ((tmp - *(soc.end()-1)) > 1) return false;
        } else {
            if ((*(it-1)+1) == tmp){// get min pos can accept from dist
                i = it - soc.begin();
            } else {
                if (*it > tmp){ // get min dist can accept from pos i
                   tmp=*it-1; 
                }
                i = (it - soc.begin())+1;
            }
        }
        loc.push_back(tmp);
    }
    if (loc.size() < n) return false;
    //for (auto i:loc) cout<<i<<" ";
    //cout<<endl;
    return true;
}
int find_op(vector<int>& soc, int n, int m) {
    int limit = soc[soc.size()-1] - soc[0];
    int ret = 0;
    // Brute force
    // for (int i=1; i<limit; i++) {
    //     if( check_valid(soc, n, i)){
    //         ret = i;            
    //     } else {
    //         break;
    //     }
    // }
    // Binary search
    int l = 0, r = limit;
    while (l<r) {
        int mid = l+(r-l)/2;
        if (check_valid2(soc, n, mid)) {
            ret = mid;
            l = mid+1;
        } else r = mid;
    }
    return ret;
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    cin>>n>>m;
    s.resize(m);
    l.resize(n);
    cfg_tmp.resize(n);
    for (int i=0; i<m; i++) {
        cin>>s[i];
    }
    sort(s.begin(),s.end());
    cout<<get_max(s,n,m)<<endl;
    //cout<<find_op(s,n,m);
    return 0;
}
