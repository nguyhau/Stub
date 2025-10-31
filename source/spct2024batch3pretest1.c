// https://www.hackerrank.com/contests/spct2024batch-3-pretest-1/challenges
// PB1: encode
// PB2: Binary search
// PB3: bfs + traveller problem
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
// PB2
bool check(vector<int> &arr, int k, int val) {
    int n = arr.size();
    int cur = 0;
    int cnt = 0;
    for(int i=0; i<n; i++) {
        if(arr[i] > val) return false;
        if(cur + arr[i] <= val) {
            cur += arr[i];
        } else {
            cnt++;
            cur = 0;
            i--;
        }
    }
    return (cnt < k);
}
void solvePB2() {
    int t;
    cin >> t;
    while (t--)
    {
        int n, k; 
        cin >> n >> k;
        vector<int> arr(n);
        for(int i=0; i<n; i++) cin >> arr[i];
        int l = 0, r = 1e9;
        while(l < r) {
            int m = l + (r-l)/2;
            if(check(arr, k, m)) {
                r = m;
            } else {
                l = m+1;
            }
        } 
        cout << l << endl;
    }
}
//
int n, r, c;
int dx[4] = {-1, 1, 0 ,0};
int dy[4] = {0, 0, -1, 1};
vector<vector<int>> ed;
void bfs(vector<string> &arr, int stt, int x, int y) {
    vector<vector<int>> mark(r, vector<int>(c, 0));
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
            if(nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
            if(arr[nx][ny] == 'x' || mark[nx][ny] != 0) continue;
            mark[nx][ny] = mark[cx][cy] + 1;
            q.push({nx, ny});
            if(arr[nx][ny] >= '0' && arr[nx][ny] <= '9') {
                ed[stt][arr[nx][ny] - '0'] = min(ed[stt][arr[nx][ny] - '0'] , mark[cx][cy]);
            }
            if(arr[nx][ny] == 'e') {
                ed[stt][n] = min(ed[stt][n] , mark[cx][cy]);
            }
        }
    }
}
void solvePB3() {
    cin >> n >> c >> r;
    vector<string> arr(r);
    for(int i=0; i<r; i++) cin >> arr[i];
    vector<pair<int, int>> position(n+1);
    ed.clear();
    ed.resize(n+1, vector<int>(n+1, INT_MAX));
    for(int i=0; i<r; i++) {
        for(int j=0; j<c; j++) {
            if(arr[i][j] == 'o' || arr[i][j] == 'x') continue;
            if(arr[i][j] == 'e') {
                position[n].first = i;
                position[n].second = j;
            } else {
                position[arr[i][j] - '0'].first = i;
                position[arr[i][j] - '0'].second = j;
            }
        }
    }
 
    for(int i=0; i<=n; i++) {
        bfs(arr, i, position[i].first, position[i].second);
    }
 
    vector<int> permu;
    for(int i=0; i<n; i++) {
        permu.push_back(i);
    }
 
    int total = 1;
    for(int i=1; i<=n; i++) {
        total *= i;
    }
 
    int ret = INT_MAX;
    for(int i=0; i< total; i++) {
        int cur = ed[n][permu[0]];
        for(int i= 1; i<n; i++) {
            cur += ed[permu[i-1]][permu[i]];
        }
        cur += ed[permu[n-1]][n];
        ret = min(ret, cur);
        next_permutation(permu.begin(), permu.end());
    }
 
    cout << ret << endl;
}
int main() {
    return 0;
}