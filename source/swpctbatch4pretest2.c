// https://www.hackerrank.com/contests/swpct-batch-4-pretest-2/challenges
// PB1: Back track
// PB2: BFS Graph
// PB3: Binary search
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
int prob1() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    cin>>x;
    number_encode(x);
    cout<<ans<<endl;
    if (ans) cout<<result<<endl;
    return 0;
}
// Prob 2
int T;
int dir[4][2] = {
    {0, 1},
    {1, 0},
    {-1, 0},
    {0, -1},
};
int32_t problem2() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // cin >> T;
    T = 1;
    while (T--) {
        int n, m;
        cin >> n >> m;
        int sx, sy;
        cin >> sx >> sy;
        int x, y;
        cin >> x >> y;
        int z, t;
        cin >> z >> t;
        vector<vector<int>> mat(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) cin >> mat[i][j];
        }
        vector<vector<bool>> check(n, vector<bool>(m, false));
        queue<int> Q;
        Q.push(sx);
        Q.push(sy);
        Q.push(0);
        check[sx][sy] = true;
        int len = INT_MAX, lens = INT_MAX;
        int cx, cy, clen;
        while (Q.size()) {
            cx = Q.front();
            Q.pop();
            cy = Q.front();
            Q.pop();
            clen = Q.front();
            Q.pop();
            // cout << cx << " " << cy << endl;
            if (cx == x && cy == y) {
                len = clen;
            }
            if (cx == z && cy == t) {
                lens = clen;
            }
            for (int i = 0; i < 4; ++i) {
                int nx = cx + dir[i][0];
                int ny = cy + dir[i][1];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && !check[nx][ny] &&
                    mat[nx][ny] == 0) {
                    Q.push(nx);
                    Q.push(ny);
                    Q.push(clen + 1);
                    check[nx][ny] = true;
                }
            }
        }
        if (len == INT_MAX && lens == INT_MAX) {
            cout << -1 << endl;
            continue;
        }
        cout << std::min(len, lens + abs(z - x) + abs(t - y)) << endl;
    }
    return 0;
}
// Problem 3
int n, m;
vector<int> soc;
bool check_valid(vector<int>&soc, int n, int d) {
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
    return true;
}
int find_op(vector<int>& soc, int n, int m) {
    int limit = soc[soc.size()-1] - soc[0];
    int ret = 0;
    int l = 0, r = limit;
    while (l<r) {
        int mid = l+(r-l)/2;
        if (check_valid(soc, n, mid)) {
            ret = mid;
            l = mid+1;
        } else r = mid;
    }
    return ret;
}
int problem3() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    cin>>n;
    cin>>m;
    soc.resize(m);
    for (int i=0; i<m; i++) cin>>soc[i];
    sort(soc.begin(), soc.end());
    cout<<find_op(soc,n,m);
    return 0;
}
int main() {


    return 0;
}