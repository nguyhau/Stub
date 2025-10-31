// https://www.hackerrank.com/contests/spct2024batch-2-pretest-3/challenges
// PB1: Simulate clipboard action: string operator + stack
// PB2: Try to optimize from bottom to top
// Problem3: Binary search + upper_bound + boundary check
// should put loc.clear() in local function that function check condition, make it independent with other check.
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
// PB1: string operator

int problem1() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    string s;
    stack<string> clb;
    //cin>>s;
    getline(cin,s);
    int c;
    string ops;
    cin>>c;
    for (int i = 0; i<c; i++) {
        cin>>ops;
        if (ops == "COPY") {
            int st, ed;
            cin>>st>>ed;
            clb.push(s.substr(st-1, ed-st+1));
        } else if (ops == "CUT") {
            int st, ed;
            cin>>st>>ed;
            clb.push(s.substr(st-1, ed-st+1));
            s=s.substr(0,st-1)+s.substr(ed,s.size()-ed);
        } else if  (ops == "PASTE") {
            int pos;
            cin>>pos;
            s = s.substr(0,pos-1)+clb.top()+s.substr(pos-1,s.size()- pos+1);
            if (clb.size()>1) {
                clb.pop();
            }
        }
    }
    cout<<s;
    return 0;
}
// Try greedy before back-track.
// Try to optimize from bottom to top
int n;
vector<int> discs;
vector<vector<int>> tows;
vector<int> capa;
int numb;
int problem2() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    cin>> n;
    discs.resize(n);
    for (int i = 0; i<n; i++) {
        cin>>discs[i];
    }
    int count = 0;
    int idx = 0;
    bool push_ok = false;
    // push from large to small
    // sort(discs.rbegin(), discs.rend());
    // while (idx < discs.size()) {
    //     push_ok = false;
    //     for (int i = 0; i< capa.size(); i++) {
    //         if (capa[i] > 0) {
    //             push_ok = true;
    //             capa[i] = min(capa[i]-1, discs[idx]);
    //             break;
    //         }
    //     }
    //     if (!push_ok) {
    //         //cout<<idx;
    //         count++;
    //         capa.push_back(discs[idx]);
    //     }
    //     idx++;
    // }
    // push from small to larger
    sort(discs.begin(), discs.end());
    tows.resize(n+1);
    while (idx < discs.size()) {
        push_ok = false;
        for (int i = 1; i<= count; i++) {
            if (tows[i].size() <= discs[idx]) {
                push_ok = true;
                tows[i].push_back(discs[idx]);
                break;
            }
        }
        if (!push_ok) {
            //cout<<idx;
            count++;
            tows[count].push_back(discs[idx]);
        }
        idx++;
    }
    cout<<count;
    return 0;
}
// Problem3: should put loc.clear() in local function that function check condition, make it independent with other check.
uint t, s;
vector<int> loc_s;
vector<int> loc;
bool valid_dist(vector<int>&v, int s, int n, int d) {
    //cout<<"Check for s="<<s<<" n="<<n<<" d="<<d<<endl;
    int temp = v[0];
    int pos = 0;
    bool flag = true;
    loc.clear();
    vector<int>::iterator it;
    while (pos < s){
        it = upper_bound(v.begin()+pos, v.end(),temp);
        pos = it - v.begin();
        if (pos < s) {
            if (v[pos-1] == temp) {
                loc.push_back(pos-1);
            } else {
                loc.push_back(pos);
                pos++;
            }
            if (loc.size() == n) {
                break;
            }
        }
        temp = v[pos-1]+d;
    }
    if (loc.size() < n) {
        //cout<<"Return false"<<endl;
        flag = false; 
    }
    return flag;
}
void Problem3() {
    cin>>t;
    int ans = 0;
    int max_d;
    while (t) {
        ans = 0;
        loc_s.clear();
        cin>>s;
        loc_s.resize(s);
        cin>>n;
        for (int i = 0; i< s; i++) {
            cin>>loc_s[i];
        };
        sort(loc_s.begin(), loc_s.end());
        max_d = loc_s[s-1];
        int l = 0, r = max_d;
        while (l<r) {
            int mid = l + (r-l)/2;
            if (valid_dist(loc_s,s,n,mid)) {
                 ans = mid;
                 l = mid+1; // increase
            } else {
                r = mid;
            };
        }
        // while (l<r) {
        //     int mid = l+(r-l)/2+1;
        //     if (ok) {
        //         ans = mid;
        //         l = mid
        //     } else {
        //         r = D-1;
        //     }
        // }
        cout<<ans<<endl;
        t--;
    }
}
int main() {
    return 0;
}