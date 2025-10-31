//https://www.hackerrank.com/contests/spct2025batch-5-practice-1/challenges
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int n;
ll g, b, d;//capa, init
vector<pair<int,ll>> gs;
ll min_cost = INT_MAX;
ll cur_cost = 0;

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    // cout.tie(NULL);
#ifndef ONLINE_JUDGE
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif
    cin>>n>>g>>b>>d;
    gs.resize(n+1);
    for(int i=0; i<n; i++) {
        cin>>gs[i].first>>gs[i].second;
    }
    gs[n].first = d;    
    sort(gs.begin(), gs.end());
    gs[n].second = gs[n-1].second;
    // for(int i=0; i<n; i++) {
    //     cout<<gs[i].first<<" "<<gs[i].second<<endl;
    // }
    //
    //dfs(b, 0, 0, 0);
    //cout<<"================"<<endl;
    cur_cost = 0;
    int cur_pos = 0;
    int cur_fuel = b;
    int cur_price = gs[0].second;
    int i = 0;
    int max_pos = b;
    while (cur_pos < d) {
        //cout<<"Cur pos "<<cur_pos<<" from gs "<<i<<" with cur_price "<<cur_price<<" max_pos "<<max_pos<<endl;
        int count = 0;
        int min_price = i;
        int mount = 0;
        while ((gs[i].first <= max_pos)&&(i<=n)){ // check gs that can be reach
            count++;
            if (gs[min_price].second > gs[i].second) min_price = i;
            if (gs[min_price].second < cur_price) break;
            i++;
        }
        if (count == 0){ // return
            cur_cost = INT_MAX;
            break;
        }
  
        if ((gs[min_price].second <= cur_price)||(min_price == n)) {// buy enough to next_min_price gs 
            mount = gs[min_price].first - cur_pos;
            if(cur_fuel >= mount){
                cur_fuel-= mount;
                mount = 0;
            } else{
                mount-= cur_fuel;
                cur_fuel = 0;
            }
            
        } else { // buy full 
            mount = g-cur_fuel;
            cur_fuel = g-(gs[min_price].first-cur_pos);
        }        
        cur_cost += mount*cur_price;
        cur_price = gs[min_price].second;
        cur_pos = gs[min_price].first;
        max_pos = gs[min_price].first + g;
        //cout<<"Go to "<<gs[min_price].first<<" buy "<<mount<<" cur_pos "<<cur_pos<<" cur cost "<<cur_cost<<endl;
        i= min_price+1;
        
    }
    if(cur_cost == INT_MAX){
        cout<<"-1";
    }else {
        cout<<cur_cost;
    }    
    return 0;
}
