#include <bits/stdc++.h>
#define ll long long
using namespace std;
//query_segment_tree(seg_tree, 1, 3, 0, n - 1, 0)
int query_segment_tree(vector<int> &seg_tree, int qlow, int qhigh, int l, int r, int pos) {
    if (qlow <= l && qhigh >= r) {
        return seg_tree[pos];
    }
    if (qlow > r || qhigh < l) {
        return INT_MAX;
    }
    int mid = (l + r) / 2;
    return min(query_segment_tree(seg_tree, qlow, qhigh, l, mid, 2 * pos + 1),
               query_segment_tree(seg_tree, qlow, qhigh, mid + 1, r, 2 * pos + 2));
}
//update_segment_tree(seg_tree, 2, -1, 0, n - 1, 0);
void update_segment_tree(vector<int> &seg_tree, int idx, int value, int l, int r, int pos) {
    if (l == r) {
        seg_tree[pos] = value;
        return;
    }
    int mid = (l + r) / 2;
    if (idx <= mid) {
        update_segment_tree(seg_tree, idx, value, l, mid, 2 * pos + 1);
    } else {
        update_segment_tree(seg_tree, idx, value, mid + 1, r, 2 * pos + 2);
    }
    seg_tree[pos] = min(seg_tree[2 * pos + 1], seg_tree[2 * pos + 2]);
}
//create_segment_tree(arr, 0, n - 1, seg_tree, 0);
void create_segment_tree(vector<int> &arr, int l, int r, vector<int> &seg_tree, int pos) {
    if (l == r) {
        //
        cout << "-- Creating segment tree at pos " << pos << " with value " << arr[l] << endl;
        seg_tree[pos] = arr[l];
        return;
    }
    int mid = (l + r) / 2;
    create_segment_tree(arr, l, mid, seg_tree, 2 * pos + 1);
    create_segment_tree(arr, mid + 1, r, seg_tree, 2 * pos + 2);
    seg_tree[pos] = min(seg_tree[2 * pos + 1], seg_tree[2 * pos + 2]);
    cout<< "Creating segment tree at pos " << pos << " with value " << seg_tree[pos] << endl;
}
void use_segment_tree() {
    vector<int> arr = {5, 8, 6, 3, 1, 7};
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout<<endl;
    int n = arr.size();
    vector<int> seg_tree(4 * n);
    create_segment_tree(arr, 0, n - 1, seg_tree, 0);
    cout << "Segment Tree: ";
    for (int i = 0; i < seg_tree.size(); i++) {
        cout << seg_tree[i] << " ";
    }
    cout << endl;

    int qlow = 1, qhigh = 3;
    cout << "Minimum in range [" << qlow << ", " << qhigh << "] is: "
         << query_segment_tree(seg_tree, qlow, qhigh, 0, n - 1, 0) << endl;

    update_segment_tree(seg_tree, 2, -1, 0, n - 1, 0);
    cout << "After updating index 2 to -1: ";
    cout << "Minimum in range [" << qlow << ", " << qhigh << "] is: "
         << query_segment_tree(seg_tree, qlow, qhigh, 0, n - 1, 0) << endl;
    for (int i = 0; i < seg_tree.size(); i++) {
        cout << seg_tree[i] << " ";
    }
    cout << endl;
}
void calculate_catalans(int n, vector<int> &dp) {
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            dp[i] += dp[j] * dp[i - 1 - j];
        }
    }
}
void use_catalans() {
    int n = 5;
    vector<int> dp(n + 1, 0);
    calculate_catalans(n, dp);
    cout << "Catalan numbers up to " << n << ": ";
    for (int i = 0; i <= n; i++) {
        cout << dp[i] << " ";
    }
    cout << endl;
}
void use_map(){
    // custom comparator
    auto fncmp = [](pair<int, int> l, pair<int, int> r)->bool{
        return l.second < r.second; // ascending order [1st element]
    };
    map<pair<int, int>, int, decltype(fncmp)> m(fncmp);
    //map<pair<int, int>, int> m;
    m.insert({{1, 2}, 1});
    m.insert({{2, 1}, 2});
    m.insert({{3, 0}, 3});
    m.insert({{0, 5}, 4});
    m.insert({{1, 3}, 5});
    for (auto it = m.begin(); it != m.end(); ++it) {
        cout << it->first.first << " " << it->first.second << " " << it->second << endl;
    }
}
void use_set(){
    // custom comparator
    auto fncmp = [](pair<int, int> l, pair<int, int> r)->bool{
        return l.second < r.second; // ascending order [1st element]
    };
    set<pair<int, int>, decltype(fncmp)> s(fncmp);
    //set<pair<int, int>> s;
    s.insert({1, 2});
    s.insert({2, 1});
    s.insert({3, 0});
    s.insert({0, 5});
    s.insert({1, 3});
    for (auto it = s.begin(); it != s.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
}
void use_pq(){
    auto fncmp = [](vector<ll>l, vector<ll>r)->bool{
        return l[1] > r[1]; // ascending order [2nd element]
    };
    priority_queue<vector<ll>, vector<vector<ll>>, decltype(fncmp)> pq(fncmp);
    pq.push({1, 2});
    pq.push({2, 1});
    pq.push({3, 0});
    while (!pq.empty()) {
        cout << pq.top()[0] << " " << pq.top()[1] << endl;
        pq.pop();
    }
}
void solve_tsp() {
    // tsp
    int n = 4;
    vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX));
    vector<vector<int>> dist = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    dp[1][0] = 0;
    for (int mask = 1; mask < (1 << n); mask++) {
        for (int u = 0; u < n; u++) {
            if (mask & (1 << u)) {
                for (int v = 0; v < n; v++) {
                    if (!(mask & (1 << v))) {
                        dp[mask | (1 << v)][v] = min(dp[mask | (1 << v)][v], dp[mask][u] + dist[u][v]);
                    }
                }
            }
        }
    }
    cout << "Minimum cost: " << dp[(1 << n) - 1][0] << endl;
}
void use_tsp() {
    // tsp
    int n = 4;
    vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX));
    vector<vector<int>> dist = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    dp[1][0] = 0;
    for (int mask = 1; mask < (1 << n); mask++) {
        for (int u = 0; u < n; u++) {
            if (mask & (1 << u)) {
                for (int v = 0; v < n; v++) {
                    if (!(mask & (1 << v))) {
                        dp[mask | (1 << v)][v] = min(dp[mask | (1 << v)][v], dp[mask][u] + dist[u][v]);
                    }
                }
            }
        }
    }
    cout << "Minimum cost: " << dp[(1 << n) - 1][0] << endl;
}
void dijkstra(int n, vector<vector<int>> &a, vector<int> &dist) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, n});// {d,u}
    dist[n] = 0;
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        for (int i = 0; i < a[u].size(); i++) {
            if (dist[a[u][i]] > d + 1) {
                dist[a[u][i]] = d + 1;
                pq.push({dist[a[u][i]], a[u][i]});
            }
        }
    }
}
void use_dijkstra() {
    vector<vector<int>> a = {
        {1, 2},
        {0, 3},
        {0, 3},
        {1, 2}
    };
    vector<int> dist(a.size(), INT_MAX);
    dijkstra(0, a, dist);
    for (int i = 0; i < dist.size(); i++) {
        cout << "Distance from node 0 to node " << i << " is: " << dist[i] << endl;
    }
}
void bfs(int n, int m, vector<vector<int>> &a, vector<vector<int>> &vis) {
    queue<pair<int, int>> q;
    q.push({n, m});
    vis[n][m] = 1;
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) continue;
                int newX = x + i;
                int newY = y + j;
                if (newX >= 0 && newX < a.size() && newY >= 0 && newY < a[0].size() && !vis[newX][newY]) {
                    vis[newX][newY] = 1;
                    q.push({newX, newY});
                }
            }
        }
    }
}
void use_bfs() {
    vector<vector<int>> a = {
        {1, 0, 0, 1},
        {0, 1, 0, 0},
        {1, 0, 1, 1},
        {0, 0, 1, 0}
    };
    vector<vector<int>> vis(a.size(), vector<int>(a[0].size(), 0));
    bfs(2, 2, a, vis);
    for (int i = 0; i < vis.size(); i++) {
        for (int j = 0; j < vis[0].size(); j++) {
            cout << vis[i][j] << " ";
        }
        cout << endl;
    }
}
void dfs(int n, int m, vector<vector<int>> &a, vector<vector<int>> &vis) {
    if (n < 0 || n >= a.size() || m < 0 || m >= a[0].size()) return;
    if (vis[n][m] == 1) return;
    vis[n][m] = 1;
    dfs(n + 1, m, a, vis);
    dfs(n - 1, m, a, vis);
    dfs(n, m + 1, a, vis);
    dfs(n, m - 1, a, vis);
}
void use_dfs() {
    vector<vector<int>> a = {
        {1, 0, 0, 1},
        {0, 1, 0, 0},
        {1, 0, 1, 1},
        {0, 0, 1, 0}
    };
    vector<vector<int>> vis(a.size(), vector<int>(a[0].size(), 0));
    dfs(2, 2, a, vis);
    for (int i = 0; i < vis.size(); i++) {
        for (int j = 0; j < vis[0].size(); j++) {
            cout << vis[i][j] << " ";
        }
        cout << endl;
    }
}
void use_permutation()
{
    vector<int> v = {1, 2, 3};
    int n = v.size();
    do {
        for (int i = 0; i < n; i++) {
            cout << v[i] << " ";
        }
        cout << endl;
    } while (next_permutation(v.begin(), v.end()));
}
void use_util(){
    // // find lower bound of vector
    // vector<int> v = {1, 2, 4, 5, 6};
    // auto it = lower_bound(v.begin(), v.end(), 3);
    // cout << "Lower bound of 3 is at index: " << it - v.begin() << endl;
    // // find upper bound of vector
    // it = upper_bound(v.begin(), v.end(), 3);
    // cout << "Upper bound of 3 is at index: " << it - v.begin() << endl;
    // find lower bound of array
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    auto it = lower_bound(arr, arr + n, 3);
    cout << "Lower bound of 3 in array is at index: " << it - arr << endl;
    //find upper bound of array
    it = upper_bound(arr, arr + n, 3);
    cout << "Upper bound of 3 in array is at index: " << it - arr << endl;
}

int main() {
    //use_pq();
    use_map();

    // Further processing...
    
    return 0;
}