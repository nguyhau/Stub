#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

int n,m;
pair<int,int> curr, ext, spec;
vector<vector<int>> maz;
vector<vector<bool>> mark;
vector<vector<int>> dist;
int ans = -1;
int min_v = INT_MAX;

int get_min_path(pair<int,int> u, pair<int,int> v, bool spec = false) {
    int value = maz[u.first][u.second];
    //cout<<u.first<<" "<<u.second<<" --> "<<v.first<<" "<<v.second<<endl;
    if ((!spec)&&(value != maz[v.first][v.second])) {
        return INT_MAX;
    }
    if ((u.first == v.first)&& (u.second == v.second)) {
        cout<<u.first<<" "<<u.second<<" --> "<<v.first<<" "<<v.second<<" distance "<<0<<endl;
        dist[u.first][u.second] = 0;
        return 0;
    }
    vector<pair<int,int>> direct = {{-1,0},{1,0},{0,-1},{0,1}};
    int row, column;
    queue<pair<int,int>> q;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            mark[i][j] = false;
            dist[i][j] = INT_MAX;
        }
    }
    dist[v.first][v.second] = 0;
    q.push(make_pair(v.first,v.second));
    pair<int,int> temp = q.front();
    while (q.size()> 0) {
        //cout<<"pop "<<endl;
        q.pop();
        for (int i=0; i< 4; i++) {
            row = temp.first + direct[i].first;
            column = temp.second + direct[i].second;
            if ((row < 0) || (row >= n)
                ||(column < 0) || (column >= m)) continue;
            
            if ((!spec)&&(maz[row][column] != value)) continue;       
            
            dist[row][column] = 1+ min(dist[row][column] -1,dist[temp.first][temp.second]);
            if (mark[row][column]) continue;
            mark[row][column] = true;
            q.push(make_pair(row,column));
            //cout<<"push "<<row<<" "<<column<<" dist "<<dist[row][column]<<endl;
        }
        if (q.size()> 0) temp = q.front();
        //else break;
    }    
    return dist[u.first][u.second];
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    cin >>n>>m;
    cin>>curr.first>>curr.second;
    cin>>ext.first>>ext.second;
    cin>>spec.first>>spec.second;
    maz.resize(n, vector<int>(m));
    mark.resize(n, vector<bool>(m, false)); //INT_MAX
    dist.resize(n, vector<int>(m,INT_MAX));
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            cin>>maz[i][j];
        }
    }
    
    //cout<<curr.first<<" "<<curr.second<<endl;
    // cout<<ext.first<<" "<<ext.second<<endl;
    // cout<<spec.first<<" "<<spec.second<<endl;
    // //maz.resize(n, vector<int>(m));
    // for (int i=0; i<n; i++) {
    //     for (int j=0; j<m; j++) {
    //         cout<<maz[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    int r1, r2, r3;
    r1 = get_min_path(curr,spec); 
    //mark.resize(n, vector<bool>(m, false)); //INT_MAX
    //dist.resize(n, vector<int>(m,INT_MAX));
    //cout<<" Find from curr ==> ext"<<endl;
    r2 = get_min_path(curr,ext);
    //cout<<" Find from spec ==> ext"<<endl;
    //r3 = get_min_path(spec,ext,true);
    r3 = abs(spec.first - ext.first) + abs(spec.second - ext.second);
    //cout<<"r1 = "<<r1<<" r2 = "<<r2<<" r3 = "<<r3<<endl;
    if (r2 == INT_MAX) {
        if (r1 == INT_MAX) {
            cout<<ans;
            return 0;
        }        
        ans = r1+r3;
    } else {
        if (r1 == INT_MAX) {
            ans = r2;
        }
        ans = r2 > (r1+r3)?(r1+r3):r2;
    }
    cout<<ans;
    return 0;
}
