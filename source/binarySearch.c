//https://www.hackerrank.com/contests/spct2025batch-5-pretest-2/challenges/truck-delivery-planning
#include <bits/stdc++.h>
#define ull long long
using namespace std;
int n,k;
vector<ull> w;
ull max_w = 0;

bool validate(vector<ull>&w, int k, ull limit) {
    if (max_w > limit) return false;
    int i = 0;
    int count = 0;
    int n = w.size();
    ull sum = 0;
    for(i=0;i<n; i++){
        sum+=w[i];
        if (sum > limit) {
            count++;
            sum = 0;
            i--;
        }
    }
    if (sum) count++;
    if (count<=k) return true;
    return false;
}
int main() {
    cin>>n>>k;
    ull ans = 0;
    w.resize(n);
    for(int i=0; i<n; i++) {
        cin>>w[i];
        if(w[i]> max_w) max_w = w[i];
    }
    ull l=0,r=1e16;
    while (l<=r) {
        ull mid = l+(r-l)/2;
        //cout<<" ---- "<<l<<" "<<mid<<" "<<r<<endl;
        if(validate(w, k, mid)) {
            ans = mid;
            r=mid-1;
        } else{
            l=mid+1;
        }
        //cout<<l<<" "<<mid<<" "<<r<<endl;
    }
    cout<<ans;
    return 0;
}
// https://www.hackerrank.com/contests/spct2025batch-5-pretest-3/challenges/lucky-number-38
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,k;
ll count_val(ll m){
    ll num = 0;
    for(ll i= 1; i<=n; i++) {
        num+= min(n, m/i);
    }
    return num;
}
int main() {
    cin>>n>>k;
    ll ans;
    ll l=1,r=n*n;
    while (l<=r) {
        ll m = l+(r-l)/2;
        //cout<<l<<" "<<r<<" "<<m<<" "<<count_val(m)<<endl;
        if (count_val(m)<k){
            l=m+1;
        }else{
            ans = m;
            r=m-1;
        }
    }   
    cout<<ans;
    return 0;
}
// https://www.hackerrank.com/contests/spct2024batch-2-pretest-1/challenges/road-to-lg-2
#include <bits/stdc++.h>
using namespace std;

int n,m,x;
vector<vector<int>> loc;
vector<int> veh;

bool bfs(vector<vector<int>>loc, int capa, int x) {
    queue<vector<int>> q;
    //cout<<"search for "<<capa<<endl;
    vector<int> tmp;
    int n = loc.size();
    int count = 0;
    vector<bool> vis(n, false);
    q.push({0,0,0});
    //bool flag = false;
    //vis[0] = true;
    while (!q.empty()) {
        tmp = q.front();
        count = tmp[2];
        q.pop();
        for (int i=0;i<n; i++ ) if (!vis[i]){
            if ((abs(loc[i][0]-tmp[0])+abs(loc[i][1]-tmp[1])) <= capa){
                //cout<<(abs(loc[i][0]-tmp[0])+abs(loc[i][1]-tmp[1]))<<endl;
                //cout<<"Push "<<i<<endl;
                if (i == (n-1)) return true;
                loc[i][2] = count+1;
                q.push(loc[i]);
                vis[i] = true;
            }
        }
        count++;
        if (count > x) {
            //cout<<"Break by count >x "<<endl;
            return false;
        }
    }
    //cout<<"Break by que.empty "<<endl;
    return false;
}
using namespace std;
int main() {
    cin>>n;
    cin>>m;
    cin>>x;
    loc.resize(n,vector<int>(3));
    veh.resize(m);
    for(int i= 0; i<n; i++) {
        cin>>loc[i][0];
    }
    for(int i= 0; i<n; i++) {
        cin>>loc[i][1];
        loc[i][2] = 0;
    }    
    for(int i= 0; i<m; i++) cin>>veh[i];
    // for(int i= 0; i<n; i++) cout<<dist[i]<<" ";
    // cout<<endl;
    
    sort(veh.begin(),veh.end());
    //cout<<veh[veh.size()-1]<<endl;   
    //cout<<"Binary"<<endl;
    if (!bfs(loc, veh[veh.size()-1], x+1)) {
        cout<<-1;
        return 0;
    }
    int l=0,r=m;
    int ans = -1;
    while (l<r) {
        int mid = l+(r-l)/2;
        if (bfs(loc, veh[mid], x+1)) {
            ans = mid;
            r = mid;
        }
        else l = mid+1;
    }
    //cout<<ans<<endl;
    cout<<veh[ans];
    return 0;
}
//https://www.hackerrank.com/contests/spct2024batch-2-pretest-3/challenges/spct-distance-rule/problem
#include <bits/stdc++.h>
using namespace std;
uint t, s, n;
vector<int> loc_s;
vector<int> loc;
bool valid_dist(vector<int>&v, int s, int n, int d) {
    //cout<<"Check for s="<<s<<" n="<<n<<" d="<<d<<endl;
    int temp = v[0];
    int pos = 0;
    //int count = 0;
    bool flag = true;
    vector<int>::iterator it;
    while (pos < s){
        //cout<<"check for "<<pos<<" "<<temp<<endl;
        it = upper_bound(v.begin()+pos, v.end(),temp);
        pos = it - v.begin();
        //cout<<pos<<endl;
        if (pos < s) {
            if (v[pos-1] == temp) {
                loc.push_back(pos-1);
            } else {
                loc.push_back(pos);
                pos++;
            }
            //cout<<"Push "<<(pos-1)<<endl;
            if (loc.size() == n) {
                //cout<<"Break by enough "<<endl;
                break;
            }
        } else {
            //cout<<"Break by out scope"<<endl;
            break;
        }
        temp = v[pos-1]+d;
    }
    if (loc.size() < n) {
        //cout<<"Return false"<<endl;
        flag = false; 
    }
    return flag;
    
}
int main() {
    cin>>t;
    int ans = 0;
    int max_d;
    while (t) {
        ans = 0;
        loc_s.clear();
        cin>>s;
        loc_s.resize(s);
        cin>>n;
        //loc.resize(n);
        for (int i = 0; i< s; i++) {
            cin>>loc_s[i];
        };
        sort(loc_s.begin(), loc_s.end());
        max_d = loc_s[s-1];
        int l = 0, r = max_d;        
        while (l<r) {
            loc.clear();
            int mid = l + (r-l)/2;
            if (valid_dist(loc_s,s,n,mid)) {
                 ans = mid;
                 l = mid+1;
            } else {
                r = mid;
            };
        }
        cout<<ans<<endl;
        t--;
    }
    return 0;
}
// https://www.hackerrank.com/contests/spct2024batch-2-pretest-5/challenges/monster-killer-1/problem
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, h;
vector<int> locs;
bool check_valid(vector<int>& locs, int h, int ef) {
    int numb = 0;
    for (int i=0; i<(locs.size()-1); i++) {
        if (locs[i+1]-locs[i]>=ef) numb+=ef;
        else {
            numb+=locs[i+1]-locs[i];
        }
        if (numb >= h) return true;
    }
    numb+=ef;
    if (numb < h) return false;
    return true;
}
int32_t main() {
    cin>>n>>h;
    locs.resize(n);
    set<int> pts;
    vector<int> filter;
    int ans;
    for (int i = 0; i< n; i++){
        cin>>locs[i];
        pts.insert(locs[i]);
    }

    for(auto k:pts) filter.push_back(k);
    int l=1, r=h+1;
    int maxrange = log2(r-l);
    //cout<<maxrange;
    int count = 0;
    while (count < maxrange) {
        int mid = l+(r-l)/2;
        if (check_valid(filter, h, mid)) {
            ans = mid;
            r = mid;
            count++;
        } else {
            l = mid+1;
            count++;
        }
    }
    for (int i = l; i<= r; i++) {
        if (check_valid(filter, h, i)) {
            if (i<ans) ans = i;
            break;
        }
    }
    cout<<ans;
    return 0;
}

