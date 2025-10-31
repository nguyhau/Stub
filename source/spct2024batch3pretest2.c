// https://www.hackerrank.com/spct2024batch-3-pretest-2
// PB1 simulator
// PB2: bfs, backtrack, dp
// PB3:
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
int m,n;
vector<vector<char>> sp;
vector<char> ans;
int solvePB1() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    cin>>m>>n;
    sp.resize(m,vector<char>(n));
    for(int i=0; i<m; i++)
        for (int j=0; j<n; j++) cin>>sp[i][j];
    int count = 0;
    bool h = true;
    bool next = true;
    int l, r, t, b;
    l=0;r=n-1;
    t=0;b=m-1;
    while ((t<=b)&&(l<=r)) {
        if (h) {
            count+=r-l+1;
            if (next) {
                for (int i = l; i<=r; i++) {
                    ans.push_back(sp[t][i]);
                    //cout<<sp[t][i];
                }
                t= t+1;
            } else {
                for (int i = r; i>=l; i--){
                    ans.push_back(sp[b][i]);
                    //cout<<sp[b][i];
                } 
                b = b-1;
            }
            h= false;
        } else {
            //cout<<endl;
            count+=b-t+1;
            if (next) {
                for (int i = t; i<=b; i++){
                    ans.push_back(sp[i][r]);
                    //cout<<sp[i][r];
                }
                r= r-1;
                next = false;
            } else {
                for (int i = b; i>=t; i--){
                    ans.push_back(sp[i][l]);
                    //cout<<sp[i][l];
                }
                l = l+1;
                next = true;
            }
            h = true;
        }
    }
    for (auto i:ans)cout<<i;
    return 0;
}
//
//int n;
vector<int> p1;
vector<int> st;

int bfs(vector<int>&p, int idx) {
    if (idx >= n) return 0;
    if (st[idx] != -1) return st[idx];
    //cout<<" Calculate "<<idx<<endl;
    int ret = INT_MAX;
    for (int i = (p[idx]-1); i<= (p[idx]+1); i++) {
        if (i <= 0) continue;
        ret = min(ret, 1 + bfs(p,idx+i));
    }
    st[idx] = ret;
    return st[idx];
}

int solvePB2() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    cin>>n;
    p1.resize(n);
    st.resize(n, -1);
    for(int i = 0; i < n; i++) {
        cin>>p1[i];
    }
    cout<<bfs(p1, 0);
    // DP
    // vector<int> m;
    // m.resize(n+1, INT_MAX);
    // m[n] = 0;
    // for (int j = n-1; j>= 0; j--) {
    //     if ((j+p[j]+1)>=n) m[j] = min(m[j], m[n]+1);
    //     else {
    //         m[j] = min(m[j], m[j+p[j]+1]+1);
    //         m[j] = min(m[j], m[j+p[j]]+1);
    //         m[j] = min(m[j], m[j+p[j]-1]+1);
    //     }
    // }
    // cout<<m[0];
    
    return 0;
}
//
int e, p, r, c;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
vector<string> arr;
vector<vector<int>> mark;
vector<int> bfs(int x, int y) {
    mark.clear();
    mark.resize(r+1, vector<int>(c+1, 0));
    vector<int> dis(n);
    queue<pair<int, int>> q;
    q.push({x, y});
    mark[x][y] = 1;
    while(!q.empty()) {
        int cx = q.front().first;
        int cy = q.front().second;
        q.pop();
        for(int i=0; i<4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            if(nx < 0 || nx >=r || ny < 0 || ny >= c) continue;
            if(arr[nx][ny] == 'x' || mark[nx][ny] != 0) continue;
            mark[nx][ny] = mark[cx][cy] + 1;
            q.push({nx, ny});
            if(arr[nx][ny] >= '0' && arr[nx][ny] <= '9') {
                dis[arr[nx][ny] - '0'] = mark[cx][cy];
            }
        }
    }
 
    return dis;
}
void solvePB3() {
    cin >> n >> e >> p;
    cin >> c >> r;
    arr.resize(r);
    for(int i=0; i<r; i++) cin >> arr[i];
    vector<pair<int, int>> Ent;
    vector<pair<int, int>> relic(n);
    for(int i=0; i<r; i++) {
        for(int j=0; j<c; j++) {
            if(arr[i][j] == 'e') {
                Ent.push_back({i,j});
            } else if(arr[i][j] >= '0' && arr[i][j] <= '9') {
                relic[arr[i][j] - '0']= {i,j};
            }
        }
    }
 
    vector<vector<int>> disent(e, vector<int>(n, 0));
    vector<vector<int>> disrelic(n, vector<int>(n, 0));
 
    for(int i=0; i<e; i++) {
        vector<int> ans = bfs(Ent[i].first, Ent[i].second);
        for(int pos=0; pos<n; pos++) {
            disent[i][pos] = ans[pos];
        }
    }
 
    for(int i=0; i<n; i++) {
        vector<int> ans = bfs(relic[i].first, relic[i].second);
        for(int pos=0; pos<n; pos++) {
            disrelic[i][pos] = ans[pos];
        }
    }
 
    vector<int> permu(n);
    int total = 1;
    for(int i=0; i<n; i++) {
        permu[i] = i;
        total *= i+1;
    }
 
    int maxn = 0;
    for(int i=0; i<total; i++) {
        int step = INT_MAX;
        int cnt = 0;
        for(int en = 0; en < e; en++) {
            if(disent[en][permu[0]] < step) {
                step = disent[en][permu[0]];
            }
        }
        if(step >= p) continue;
        int re;
        for(re=0; re<n; re++) {
            for(int en = 0; en < e; en++) {
                if(step + disent[en][permu[re]] <= p ) {
                    cnt++;
                    break;
                }
            }
            if(re == n-1) break;
            if(step + disrelic[permu[re]][permu[re+1]] >=p) {
                break;
            } 
            step += disrelic[permu[re]][permu[re+1]];
        }
        maxn = max(maxn, cnt);
        if(maxn == n) break;
        next_permutation(permu.begin(), permu.end());
    }
 
    cout << maxn << endl;
}
int main() {
    return 0;
}