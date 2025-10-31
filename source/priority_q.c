//https://www.hackerrank.com/contests/spct2024batch-2-pretest-6/challenges/managing-counseling-schedule
#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
#define int long long
#define endl "\n"
#define pb push_back
const int maxn = 1e5+2;
int a[maxn];
 
class Compare {
    public:
       bool operator()(pair<int, int> &a, pair<int,int> &b){
           if(a.first != b.first) return a.first > b.first;
           return a.second > b.second;
      }
};
 
void solve() {
    int n; cin >> n;
    vector<vector<int>> arr(n, vector<int>(3, 0));    
    for(int i = 0; i< n; i++) cin >> arr[i][0];
    for(int i = 0; i< n; i++) {
        cin >> arr[i][1];
        arr[i][2] = i;
    }
    sort(arr.begin(), arr.end());
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> q;
    int timestamp = arr[0][0];
    int pos = 0;
    while(pos < n && arr[pos][0] <= timestamp) {
        q.push({arr[pos][1], arr[pos][2]});
        pos++;
    }
    vector<int> ret;
    while(q.empty() == 0 || pos < n) {
        if(q.empty() == 1 && pos < n) {
            timestamp = arr[pos][0];
            while(pos < n && arr[pos][0] <= timestamp) {
                q.push({arr[pos][1], arr[pos][2]});
                pos++;
            }
        } else {
            int f = q.top().first;
            int s = q.top().second;
            q.pop();
            timestamp += f;
            ret.push_back(s+1);
            while(pos < n && arr[pos][0] <= timestamp) {
                q.push({arr[pos][1], arr[pos][2]});
                pos++;
            }
        }
    }
 
    for(int i=0; i<n; i++) {
        cout << ret[i] << " ";
    }
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
#ifndef ONLINE_JUDGE
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif
    solve();
    return 0;
}