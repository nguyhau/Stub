// https://www.hackerrank.com/contests/swpct-batch-5-pretest-3/challenges
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;


int solvePB1() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int t;
    cin>>t;
    while (t) {
        int k, n;
        cin>>k>>n;
        vector<char> bulks;
        int count = 0;
        int i;
        bulks.resize(k);
        for(i=0; i<k; i++) {
            cin>>bulks[i];
        };
        i = 0;
        while (i<k) {
            while ((i<k&&(bulks[i] == '0')))i++;
            if (i<k) {
                count++;
                int j;
                for(j=i; j<min(k,i+n); j++) {
                    bulks[j]='1';
                };
                i = j;
            }
            
        }
        cout<<count<<endl;
        t--;
    }
    return 0;
}

bool check_valid(vector<long long>& a, int n, long long val, long long x) {
    long long sum = 0;
    for (int i=0; i<n; i++) {
        if (a[i]< val) sum+=(val - a[i]);
        if (sum > x) return false;
    }
    return (sum <= x);
}
int solvePB2() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int t;
    cin>>t;
    while (t) {
        int n,x, ans = 0;
        vector<long long> ar;
        cin>>n>>x;
        ar.resize(n);
        for (int i=0; i<n; i++) cin>>ar[i];
        int l=1, r=2*1e9;
        while (l<r) {
            long long mid = l+(r-l)/2;
            if (check_valid(ar, n , mid, x)) {
                ans = mid;
                l = mid+1;
            } else {
                r= mid-1;
            }
        }
        if (check_valid(ar, n , r, x)) {
                ans = r;
            }
        cout<<ans<<endl;
        t--;
    }
    return 0;
}

int solvePB3() {
    int n, x;
    vector<vector<int>> loc;
    vector<vector<int>> adj;
    vector<bool>visit;
    cin >>n>>x;
    loc.resize(n+2, vector<int>(2));
    adj.resize(n+2);
    visit.resize(n+2, false);
    for (int i=0; i<=n; i++) {
        cin>>loc[i][0]>>loc[i][1];
    }
    loc[n+1][0] = 0;
    loc[n+1][1] = 0;
    for (int i=0; i< (n+1); i++) {
        //cout<<"Adj of "<<i<<" ";
        for (int j=i+1; j<(n+2); j++) {
            int tmp = abs(loc[j][0]-loc[i][0]) + abs(loc[j][1]-loc[i][1]);
            //cout<<j<<" "<<tmp<<endl;
            if (tmp <= x) {
                adj[i].push_back(j);
                adj[j].push_back(i);
                //cout<<j<<" ";
            };
            //cout<<endl;
        }
    }
    int ans = 0;
    if (adj[0].size() > 0) {
        queue<vector<int>> q;
        q.push({0,0});
        visit[0] = true;
        while (q.size() > 0) {
            vector<int> tmp = q.front();
            q.pop();
            for (auto i:adj[tmp[0]]) {
                if (i == (n+1)) {
                    ans = tmp[1];
                    break;
                };
                if (visit[i]) continue;
                q.push({i, tmp[1]+1});
                visit[i] = true;
            };
            if (ans>0) {
                break;
            }
        }
    }
    else {
        ans = -1;
    }
    cout<<ans<<endl;
    return 0;
}

int main() {
    return 0;
}