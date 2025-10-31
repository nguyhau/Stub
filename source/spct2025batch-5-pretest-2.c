//https://www.hackerrank.com/contests/spct2025batch-5-pretest-2/challenges
//PB1
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
int PB1() {
    cin>>n>>k;
    ull ans = 0;
    w.resize(n);
    for(int i=0; i<n; i++) {
        cin>>w[i];
        if(w[i]> max_w) max_w = w[i];
    }
    ull l=0,r=1e16;
    while (l<r) {
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
    if(validate(w, k, l)) {
        ans = l;            
    }
    cout<<ans;
    return 0;
}
// PB2
int m;//n,k,
vector<int> ls;
vector<bool> vs;
map<int,set<int>> map_dis;
vector<int> conf;
int count_ans = 0;
int p_count = 1;
bool check_cfg(vector<int>& v){
    int c_type=0;
    int pre = 0;
    if(map_dis[v[0]].count(v[n-1])>0) return false;
    for(int i=0; i<2*n; i++) {
        
        if(ls[v[i%n]]==pre) {
            c_type++;
            if (c_type > k) return false;
        }else {
            c_type=1;
            pre=ls[v[i%n]];
        }
    }
    //if(ls[v[n-1]]==ls[v[0]]) c_type++;
    if (c_type > k) return false;
    return true;
}
void print_cfg(vector<int>conf){
    for(int i=0; i<n;i++) cout<< conf[i]<<" ";
    cout<<endl;
    for(int i=0; i<n;i++) cout<< ls[conf[i]]<<" ";
    cout<<endl;
}
void bt(vector<int>&ls, vector<int>&conf, int idx, int p_count) {
    //
    if (conf.size() == n) {
        //check conf
        if(check_cfg(conf)) {
            count_ans++;            
        }
        return;
    }
    for(int i = 0; i< n; i++) {
        if (vs[i]) continue;
        if(map_dis[idx].count(i)>0) continue;
        if ((p_count == k)&& (ls[idx]==ls[i])) continue;
        // select i
        conf.push_back(i);
        vs[i] = true;
        if (ls[idx]!=ls[i]) p_count=1;
        bt(ls, conf, i, p_count);
        // non select i;
        conf.pop_back();
        vs[i] = false;
    }
}
int PB2() {
    cin>>n>>m>>k;
    ls.resize(n);
    vs.resize(n, false);
    //dis.resize(m);
    for(int i=0; i<n; i++) cin>>ls[i];
    int x,y;
    //cout<<" Dislike pair "<<endl;
    for(int j=0; j<m; j++){
        cin>>x>>y;
        map_dis[x-1].insert(y-1);
        map_dis[y-1].insert(x-1);
        //cout<<(x-1)<<" "<<(y-1)<<endl;
    }
    //cout<<"--------------------"<<endl;
    //
    vector<int> conf;
    // select i
    conf.push_back(0);
    vs[0] = true;
    bt(ls, conf, 0, p_count);
    cout<<count_ans;
    return 0;
}
// PB3
//int n,m;
vector<vector<char>> mt;
vector<pair<int,int>> v_em;
vector<pair<int,int>> v_ca;
vector<vector<int>>dist;
pair<int,int>st;
vector<vector<bool>> vs3;

void cam_scan(vector<vector<char>>&mt) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if(mt[i][j] == 'C') {
                // up
                for(int k = i-1; k>=0; k--) {
                    if(mt[k][j] == 'W') break;
                    if((mt[k][j] == '.')||(mt[k][j] == 'S')) dist[k][j] = -2;
                }
                // down
                for(int k = i+1; k<n; k++) {
                    if(mt[k][j] == 'W') break;
                    if((mt[k][j] == '.')||(mt[k][j] == 'S')) dist[k][j] = -2;
                }
                // left
                for(int k = j-1; k>=0; k--) {
                    if(mt[i][k] == 'W') break;
                    if((mt[i][k] == '.')||(mt[i][k] == 'S')) dist[i][k] = -2;
                }
                // right
                for(int k = j+1; k<m; k++) {
                    if(mt[i][k] == 'W') break;
                    if((mt[i][k] == '.')||(mt[i][k] == 'S')) dist[i][k] = -2;
                }
            }
        }
    } 
}
void push_e(priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>>& q, vector<int> v) {
    
    int x = v[1];
    int y = v[2];
    //cout<<"push "<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<dist[x][y]<<endl;
    if(vs3[x][y]) return;
   
    if((mt[x][y]=='W')||(mt[x][y]=='C')||(dist[x][y]==(-2))) return;
    if (mt[x][y]!='.') vs3[x][y] = true;
    if (dist[x][y] < 0) dist[x][y] = v[0];
    else if (dist[x][y] <= v[0]) return;
    q.push(v);
}
void bfs(vector<vector<char>>&mt, pair<int,int> st) {
    if (dist[st.first][st.second]<(-1)) return;
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> q; 
    vs3.resize(n, vector<bool>(m, false)); 
    push_e(q,{0, st.first, st.second} ); 
    vector<pair<int,int>> mov = {{-1,0},{1,0},{0,-1},{0,1}};
    while(q.size() > 0) {
        int d = q.top()[0];
        int x = q.top()[1];
        int y = q.top()[2];        
        q.pop();
        //cout<<" Pop "<<x<<" "<<y<<" "<<d<<endl;
        if (mt[x][y] == 'U'){
            if (x > 0) push_e(q, {d,x-1,y});
            continue;                
        }
        if (mt[x][y] == 'D'){
            if (x < (n-1)) push_e(q, {d,x+1,y});
            continue;                
        }
        if (mt[x][y] == 'L'){
            if (y >0) push_e(q, {d,x,y-1});
            continue;                
        }
        if (mt[x][y] == 'R'){
            if (y < (m-1)) push_e(q, {d,x,y+1});
            continue;                
        }
        if (mt[x][y] == '.'){
            if(dist[x][y] > d)dist[x][y] = d;
            vs3[x][y] = true;
        } 
        // add adjacent
        for(int i=0; i<4; i++) {
            int x1 = x+mov[i].first;
            int y1 = y+mov[i].second;
            //cout<<" check "<<x1<<" "<<y1;
            if ((x1<0)||(x1==n)||(y1<0)||(y1==m)) continue;
            push_e(q,{d+1,x1,y1});
        }
        //cout<<endl<<"-------------"<<endl;
    }
}
int main() {
    cin>>n>>m;
    mt.resize(n);
    dist.resize(n);
    for(int i=0; i<n; i++) {
        mt[i].resize(m);
        dist[i].resize(m,-1);
        for(int j=0; j<m; j++) {
            cin>>mt[i][j];
            if(mt[i][j]=='.') {
                v_em.push_back({i,j});
                continue;
            }
            if(mt[i][j]=='C') {
                v_ca.push_back({i,j});
                continue;
            }
            if(mt[i][j]=='S') {
                st.first = i;
                st.second = j;
                //dist[i][j] = 0;
            };
        }
    }
    // cover by came
    cam_scan(mt);
    // for(int i=0; i<n; i++) {
    //     for(int j=0; j<m; j++) cout<<dist[i][j]<<" ";
    //     cout<<endl;
    // }
    // cout<<"---------------------"<<endl;
    // calculate
    
    bfs(mt, st);
    // print result
    for(int i=0; i<v_em.size(); i++) {
        //cout<<v_em[i].first<<" "<<v_em[i].second<<" -- dist ";
        if(dist[v_em[i].first][v_em[i].second] < 0) cout<<"-1"<<endl;
        else
        cout<<dist[v_em[i].first][v_em[i].second]<<endl;
    }
    
    
    return 0;
}
