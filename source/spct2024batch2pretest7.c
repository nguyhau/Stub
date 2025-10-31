// https://www.hackerrank.com/contests/spct2024batch-2-pretest-7/challenges
// PB2: Graph, group theory: equivalence group, connectivity grap
// PB3: DP: redmine task
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
// PB1:
int problem1()
{
    int n;
    cin >> n;
    vector<pair<string, bool>> bookings;
    for (int i = 0; i < n; i++)
    {
        string fromDate, toDate;
        cin >> fromDate >> toDate;
        bookings.push_back({fromDate, true});
        bookings.push_back({toDate, false});
    }
    sort(bookings.begin(), bookings.end());
    int count = 0;
    int maxCount = 0;
    string maxDate = "";
    for (int i = 0; i < n * 2; i++)
    {
        if (bookings[i].second)
        {
            count++;
        }
        else
        {
            count--;
        }
        if (maxCount < count)
        {
            maxCount = count;
            maxDate = bookings[i].first;
        }
    }
    cout << maxDate << endl;
    return 0;
}
// PB2: Graph, group theory, 
bool cmp(vector<int>& C1, vector<int>& C2)
{
    sort(C1.begin(), C1.end());
    sort(C2.begin(), C2.end());
    for (int i=0; i<C1.size(); i++) {
        if (C1[i] != C2[i]) return false;
    }
    return true;
}

bool solve()
{
    int n, m; cin >> n >> m;
    int Q1[n], Q2[n];
    for (int i=0; i<n; i++) cin >> Q1[i];
    for (int i=0; i<n; i++) cin >> Q2[i];
    
    int x, y;
    vector<vector<int>> adj(n);
    for (int i=0; i<m; i++) {
        cin >> x >> y;
        adj[--x].push_back(--y);
        adj[y].push_back(x);
    }
    vector<bool> vis(n, false);
    for (int i=0; i<n; i++) {
        if (!vis[i]) {
            queue<int> q;
            q.push(i);
            vector<int> C1, C2;
            while(q.size()) {
                int p = q.front();
                q.pop();
                vis[p] = true;
                // create the connectivity of grp 1
                C1.push_back(Q1[p]);
                // create the connectivity of grp 2
                C2.push_back(Q2[p]);
                for (int u : adj[p]) {
                    if (!vis[u]) q.push(u);
                }
            }
            // check two configuration is similar or not
            if (cmp(C1, C2) == false) return false;
        }
    }
    return true;
}

int problem2() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int t; cin >> t;
    while (t--) {
        if (solve()) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
// PB3: DP
int t, n;
int problem3() {
    cin>>t;
    while (t>0) {
        // For each TC
        cin>>n;
        vector<vector<int>> profit;
        profit.resize(49, vector<int> (49,0));
        vector<vector<int>> inps;
        inps.resize(n, vector<int>(3));
        for (int i=0; i<n; i++) {
            cin>>inps[i][0]>>inps[i][1]>>inps[i][2];
        };
        sort(inps.begin(), inps.end());
        int temp;
        int s,e,p;
        int previous = 48;
        for (int i=n-1; i>= 0; i--) {
            s = inps[i][0];
            e = inps[i][1];
            if (e > 48) continue;
            // update previous value
            for(int i = s; i < previous;i++) profit[i][48] = max(profit[i][48],profit[previous][48]);
            p = inps[i][2];
            temp = p+profit[e][48];
            if (temp > profit[s][48]) profit[s][48] = temp;
            previous = s;
        };
        cout<<profit[s][48]<<endl;
        t--;
    }
    return 0;
}
int main() {
    return 0;
}