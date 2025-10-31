// https://www.hackerrank.com/contests/spct2025batch-1-pretest-4/challenges
#include <bits/stdc++.h>
using namespace std;
int n,m;
vector<vector<int>> mt;

int PB2() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    cin>>n>>m;
    mt.resize(n, vector<int>(m));
    for (int i=0; i<n; i++)
        for (int j=0; j<m; j++) cin>>mt[i][j];
    vector<vector<int>> dist;
    dist.resize(n, vector<int>(m, (n*m)));
    dist[0][0] = mt[0][0];
    queue<vector<int>> q;
    q.push({0,0,dist[0][0]});
    vector<pair<int,int>> move = {{-1,0},{1,0},{0,-1},{0,1}};
    while (q.size()>0) {
        vector<int> tmp = q.front();
        q.pop();
        for(auto dir:move) {
            int r = tmp[0]+dir.first;
            int c = tmp[1]+dir.second;
            int d = tmp[2];
            //cout<<" Check for "<<r<<" "<<c<<" "<<d<<endl;
            if ((r<0)||(r==n)||(c<0)||(c==m)) continue;
            if(mt[r][c]==1) {
                d++;
            };
            if (d<dist[r][c]) {
                dist[r][c]=d;
                q.push({r,c,d});
                //cout<<" === Push "<<r<<" "<<c<<" "<<d<<endl;
            }
        }
    }
    cout<<(dist[n-1][m-1]+1);
    return 0;
}
vector<vector<char>> mtc;
vector<vector<vector<int>>> dist;
int PB3() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    cin>>n>>m;
    int u,v;
    int s,t;
    mtc.resize(n, vector<char>(m));
    dist.resize(n, vector<vector<int>>(m, vector<int>(2,n*m)));
    vector<pair<int,int>> hor={{-1,0},{1,0}};
    vector<pair<int,int>> ver={{0,-1},{0,1}};
    for (int i=0; i<n; i++) 
        for (int j=0; j<m; j++) {
            cin>>mtc[i][j];
            if (mtc[i][j]=='C') {
                u=i;
                v=j;
            }
            if (mt[i][j]=='E') {
                s=i;
                t=j;
            }
        }
    queue<vector<int>> q;
    dist[u][v][1]=0;
    dist[u][v][0]=0;
    q.push({u,v,1,dist[u][v][0]});
    q.push({u,v,0,dist[u][v][1]});
    int ans = -1;
    while (q.size()>0) {
        vector<int> tmp = q.front();
        q.pop();
        if(tmp[2]==1) {
            //
            for (auto mov:ver) {
                int r = tmp[0]+mov.first;
                int c = tmp[1]+mov.second;
                int d = tmp[3]+1;
                if ((r<0)||(r==n)||(c<0)||(c==m)) continue;
                if(mtc[r][c]=='#') continue;
                if (dist[r][c][0] > d) {
                    dist[r][c][0]=d;
                    q.push({r,c,0,d});
                }                
            }
        }
        if(tmp[2]==0) {
            for (auto mov:hor) {
                int r = tmp[0]+mov.first;
                int c = tmp[1]+mov.second;
                int d = tmp[3]+1;
                if ((r<0)||(r==n)||(c<0)||(c==m)) continue;
                if(mtc[r][c]=='#') continue;
                if (dist[r][c][1] > d) {
                    dist[r][c][1]=d;
                    q.push({r,c,1,d});
                }
            }
        }
        
    }
    int min_dist = min(dist[s][t][0],dist[s][t][1]);
    if (min_dist < (n*m)) {
        ans = min_dist;
    }
    cout<<ans;
    return 0;
}
int main() {
    return 0;
}