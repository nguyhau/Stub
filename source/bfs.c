https://www.hackerrank.com/contests/lgedv-pretest-pool-2025/challenges/excavate-the-relics
#include <bits/stdc++.h>
using namespace std;
int n,e,p;
int w,h;
vector<vector<char>> mt;
vector<vector<int>> di;
vector<bool> vs;
int ans = 0;
vector<int> bfs(int x, int y){    
    vector<int> dist;
    dist.resize(n);
    vector<vector<int>> d;
    d.resize(w, vector<int>(h, INT_MAX));
    d[x][y] = 0;
    char c_b = mt[x][y];
    mt[x][y]='o';
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> q;
    q.push({0, x, y});    
    vector<pair<int,int>> mov={{-1,0},{1,0},{0,-1},{0,1}};
    int count = 0;
    while(q.size() > 0) {
        int tmd = q.top()[0];
        int row = q.top()[1];
        int col = q.top()[2];
        q.pop();
        //
        if((mt[row][col] >= '0')&&(mt[row][col] <= '9')){
            int val = mt[row][col] -'0';
            dist[val] = tmd;
            count++;
            if(count == n) break;
        }
        //
        for(int i=0; i<4; i++){
            int r = row + mov[i].first;
            int c = col + mov[i].second;
            if((r<0)||(r==w)||(c<0)||(c==h)) continue;
            if (mt[r][c]=='x') continue;
            if(d[r][c] > (d[row][col]+1)){
                d[r][c] = d[row][col]+1;
                q.push({d[r][c],r,c});
            }
        }
    }    
    mt[x][y]=c_b;
    return dist;
}
int bt(int idx, int& count, int& sum){
    if ((sum + di[n][idx])>p) return 0;
    //cout<<"Bt "<<idx<<
    if ((sum + di[n][idx])<= p){
        // update
        if (count > ans) {
            ans = count;
        }
        for(int i=0; i<n; i++) if(!vs[i]){
            sum+= di[idx][i];
            count++;
            vs[i] = true;
            bt(i, count, sum);
            vs[i] = false;
            count--;
            sum-= di[idx][i];
        }
    }    
    return 0;
}
int main() {
    cin>>n>>e>>p;
    cin>>w>>h;
    vector<pair<int,int>> vp;
    di.resize(n+1, vector<int>(n, INT_MAX));
    mt.resize(w, vector<char>(h));
    for(int i= 0; i<w; i++)
        for(int j=0; j<h; j++) {
            cin>>mt[i][j];
            if (((mt[i][j]>='0')&&(mt[i][j]<='9'))||(mt[i][j]=='e'))
                vp.push_back({i,j});
        }
    //
    for(int i=0; i<vp.size(); i++){
        int x = vp[i].first;
        int y = vp[i].second;
        if((mt[x][y] >= '0')&&(mt[x][y] <= '9')){
            int val = mt[x][y] -'0';
            //cout<<"Calculate dist to edge "<<val<<" ["<<x<<"] ["<<y<<"]"<<endl;
            di[val] = bfs(x,y);
            //for(int j = 0; j<n; j++) cout<<di[val][j]<<" ";
            //cout<<endl;
        }else if(mt[x][y] == 'e'){
            vector<int> tmp = bfs(x,y);
            for(int j=0; j<n; j++) di[n][j] = min(di[n][j], tmp[j]);
        }
    }
    //cout<<"Calculate dist to exit/entrance "<<endl;    
    //for(int j = 0; j<n; j++) cout<<di[n][j]<<" ";
    //cout<<endl;
    //
    // Get subsets that cost <= p
    vs.resize(n, false);
    for(int i=0; i<n; i++) {
        int cnt = 1;
        int sum = di[n][i];
        vs[i] = true;
        bt(i, cnt, sum);
        vs[i] = false;
    }
    // Get minimum cost getting all n relics: use permutation
    //int ans=INT_MAX;
    vector<int> myints;
    myints.resize(n);
    for(int i=0; i<n; i++) myints[i]=i;
    do {
        int sum = 0;
        sum+=d[n][myints[0]];
        for(int i=0; i<(n-1); i++){
            sum+=d[myints[i]][myints[i+1]];
        }
        sum+=d[n][myints[n-1]];
        if(ans>sum) ans=sum;
        //std::cout << myints[0] << ' ' << myints[1] << ' ' << myints[2] << '\n';
    } while (next_permutation(myints.begin(),myints.end()) );
    cout<<ans;
    return 0;
}
// https://www.hackerrank.com/contests/spct2025batch-5-pretest-2/challenges/underground-escape
#include <bits/stdc++.h>
using namespace std;
int n,m;
vector<vector<char>> mt;
vector<pair<int,int>> v_em;
vector<pair<int,int>> v_ca;
vector<vector<int>>dist;
pair<int,int>st;
vector<vector<bool>> vs;

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
    if(vs[x][y]) return;
   
    if((mt[x][y]=='W')||(mt[x][y]=='C')||(dist[x][y]==(-2))) return;
    if (mt[x][y]!='.') vs[x][y] = true;
    if (dist[x][y] < 0) dist[x][y] = v[0];
    else if (dist[x][y] <= v[0]) return;
    q.push(v);
}
void bfs(vector<vector<char>>&mt, pair<int,int> st) {
    if (dist[st.first][st.second]<(-1)) return;
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> q; 
    vs.resize(n, vector<bool>(m, false)); 
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
            vs[x][y] = true;
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
// https://www.hackerrank.com/contests/spct2025batch-5-pretest-3/challenges/world-peace-1-1
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
int n,m;
vector<vector<vector<int>>> mt;
vector<int>pre;
int get_dist(vector<vector<vector<int>>> mt, vector<int>&dist, bool save) {
    
    priority_queue<vector<int>,vector<vector<int>>, greater<vector<int>>>q;
    vector<bool> vs;
    vs.resize(n, false);
    q.push({0,0,0});
    vs[0] = true;
    while(q.size()>0) {
        int d = q.top()[0];
        int x = q.top()[1];
        int y = q.top()[2];
        q.pop();
        if ( d <= dist[y]) {
            dist[y] = d;
            if(save) pre[y] = x;
        } 
        for(int i=0; i<mt[y].size(); i++) {
            int v = mt[y][i][1];
            int newd = dist[y]+mt[y][i][0];
            if (mt[y][i][0] > 0) {
                if (dist[v] > newd){
                    q.push({newd,y,v});
                    dist[v] = newd;
                } 
            }
        }
    }
    return dist[n-1];
}
//
//int p
int get_new(vector<vector<vector<int>>> mt, int x, int y){
    // disable edge (x,y)
    for(int i=0; i<mt[x].size(); i++){
        if (mt[x][i][1] == y){
            mt[x][i][0] = -1;
            break;
        }
    }
    for(int i=0; i<mt[y].size(); i++){
        if (mt[y][i][1] == x){
            mt[y][i][0] = -1;
            break;
        }
    }
        
    vector<int> dist2;
    dist2.resize(n, INT_MAX);
    //cout<<" calculte dist 2nd ";
    int d = get_dist(mt, dist2, false);
    return d;
}
//
int get_dist(int idx, vector<vector<vector<int>>>& mt, vector<int>&dist) {    
    priority_queue<vector<int>,vector<vector<int>>,greater<vector<int>>>q;
    q.push({0,idx});
    while(q.size()>0) {
        int d = q.top()[0];
        //int x = q.top()[1];
        int y = q.top()[1];
        q.pop();
        if ( d <= dist[y]) {
            dist[y] = d;
        } else{
            continue;
        } 
        for(int i=0; i<mt[y].size(); i++) {
            int v = mt[y][i][1];
            int dyv=mt[y][i][0];
            int newd = dist[y]+dyv;
            if (dyv > 0) {
                if (dist[v] > newd){
                    q.push({newd, v});
                    dist[v] = newd;
                } 
            }
        }
    }
    return dist[n];
} 
void solve2() {
    int ans = INT_MIN;
    cin>>n>>m;
    mt.resize(n+1);
    vector<vector<int>> listVer;
    for(int i=0; i<m; i++) {
        int x,y,d;
        cin>>x>>y>>d;
        mt[x].push_back({d,y});
        mt[y].push_back({d,x});
        listVer.push_back({x,y,d});
    }
    vector<int> dist_1;
    vector<int> dist_n;
    dist_1.resize(n+1, INT_MAX);
    dist_n.resize(n+1, INT_MAX);
    //cout<<" calculte dist 1st ";
    get_dist(1,mt, dist_1);
    get_dist(n,mt, dist_n);
    //
    for(int i=0; i<listVer.size(); i++){
        int x = listVer[i][0];
        int y = listVer[i][1];
        int d = listVer[i][2];
        //cout<<"Verter ["<<i<<","<<y<<"] = "<<d;
        if ((dist_1[x] == INT_MAX)||(dist_n[y] == INT_MAX)) continue;
        if ((dist_1[y] == INT_MAX)||(dist_n[x] == INT_MAX)) continue;
        if ((dist_1[x]+d+dist_n[y]) == dist_1[n]) {
            //cout<<" In short path"<<endl;
            int tmpd = get_new(mt, x, y);
            if ((tmpd < INT_MAX)&&(tmpd > ans)) {
                ans = tmpd;
            }
        }
    }
    if (ans > INT_MIN) cout<<ans;
    else cout<<"INF";
}
int main() {
    int ans = INT_MIN;
    cin>>n>>m;
    mt.resize(n);
    pre.resize(n);
    for(int i=0; i<m; i++) {
        int x,y,d;
        cin>>x>>y>>d;
        mt[x-1].push_back({d,y-1});
        mt[y-1].push_back({d,x-1});
    }
    vector<int> dist;
    dist.resize(n, INT_MAX);
    //cout<<" calculte dist 1st ";
    get_dist(mt, dist, true);
    // get list edge
    vector<pair<int,int>> eds;
    int i = n-1;
    pre[0] = -1;
    while (i != 0){
        eds.push_back({i,pre[i]});
        i=pre[i];
    }
    for(int i=0; i< eds.size(); i++){
        //cout<<eds[i].first<<" "<<eds[i].second<<endl;
        int x=eds[i].first;
        int y=eds[i].second;        
        int d = get_new(mt, x, y);
        //cout<<"Disable "<<x<<" "<<y<<" "<<d<<endl;
        if ((d < INT_MAX)&&(d > ans)) {
            ans = d;
        }
    } 
    
    if (ans > INT_MIN) cout<<ans;
    else cout<<"INF";
    return 0;
}
