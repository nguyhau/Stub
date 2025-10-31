//https://www.hackerrank.com/contests/spct2025batch-5-practice-1/challenges/long-way-to-work
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int n;
ll g, b, d;//capa, init
vector<pair<ll,ll>> gs;
ll cur_cost = 0;
int main() {
    cin>>n>>g>>b>>d;
    gs.resize(n+1);
    for(int i=0; i<n; i++) {
        cin>>gs[i].first>>gs[i].second;
    }
    gs[n].first = d;
    gs[n].second = 0; // set min price
    sort(gs.begin(), gs.end());
    cur_cost = 0;
    ll cur_pos = 0;
    ll cur_fuel = b;
    ll cur_price = gs[0].second;
    ll i = 0;
    ll max_pos = b;
    while (cur_pos < d) {
        //cout<<"Cur pos "<<cur_pos<<" from gs "<<i<<" with cur_price "<<cur_price<<" max_pos "<<max_pos<<endl;
        ll count = 0;
        ll min_price = i;
        ll mount = 0;
        while ((gs[i].first <= max_pos)&&(i<=n)){ // check gs that can be reach
            count++;
            if (gs[min_price].second > gs[i].second) min_price = i;
            if (gs[min_price].second < cur_price) break;
            i++;
        }
        if (count == 0){ // return
            cur_cost = LLONG_MAX;
            break;
        }
        if ((gs[min_price].second <= cur_price)||(gs[min_price].first == d)) {// buy enough to next_min_price gs 
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
            cur_fuel = g+cur_pos-gs[min_price].first;
        }        
        cur_cost += mount*cur_price;
        cur_price = gs[min_price].second;
        cur_pos = gs[min_price].first;
        max_pos = gs[min_price].first + g;
        //cout<<"Go to "<<gs[min_price].first<<" buy "<<mount<<" cur_pos "<<cur_pos<<" cur cost "<<cur_cost<<endl;
        i= min_price+1;
    }
    if(cur_cost == LLONG_MAX){
        cout<<"-1";
    }else {
        cout<<cur_cost;
    }
    return 0;
}
// https://www.hackerrank.com/contests/spct2025batch-5-practice-3/challenges/boadandtheroadtripchallenge
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll dest, start, n;
vector<vector<ll>> gs;

int main() {
    cin>>dest>>start>>n;
    //cout<<n;
    ll max_f = 0;
    gs.resize(n+2, vector<ll>(2, LLONG_MAX));
    for(ll i=1; i<=n; i++){
        cin>>gs[i][0]>>gs[i][1];
        if (max_f < gs[i][1]) max_f = gs[i][1];
    }    
    gs[0][0] = 0;
    gs[0][1] = start;
    sort(gs.begin(),gs.end());
    //for(int i=0; i<n; i++) cout<<gs[i][0]<<" "<<gs[i][1]<<" "<<gs[i][2]<<endl;
    ll r = n;    
    while (gs[r][0] > dest) r--;
    r++;
    gs[r][0] = dest;
    gs[r][1] = max_f+1;
    ll ans = LLONG_MAX;   
    ll idx = 1;
    ll c = 0;
    ll max_pos = start;
    priority_queue<pair<ll,ll>> q;
    while((max_pos<dest)&&(idx<= r)){
        
        while ((idx<= r)&&(gs[idx][0]<= max_pos)){
            q.push({gs[idx][1], idx});
            idx++;
        }
        if(q.size() == 0){
            c = LLONG_MAX;
            break;
        }
        c++;
        max_pos+= q.top().first;
        //cout<<" Add fuel at "<<q.top().second<<" max_pos="<<max_pos<<endl;
        //idx = q.top().second+1;
        q.pop();
    }
    ans = c;
    if(ans < LLONG_MAX) {
        cout<<ans;
    }else{
        cout<<"-1";
    }
    return 0;
}
