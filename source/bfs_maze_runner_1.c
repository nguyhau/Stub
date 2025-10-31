#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define endl '\n'
#define mod 1000000007
/* global variables */
int T;
int dir[4][2] = {
    {0, 1},
    {1, 0},
    {-1, 0},
    {0, -1},
};
/* main function */
int32_t main() {
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