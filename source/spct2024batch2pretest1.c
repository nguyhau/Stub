// https://www.hackerrank.com/contests/spct2024batch-2-pretest-1/challenges
// PB1: Encode: String operator: substr, stoi
// PB2: Greedy: assumption a theory(max, min). equivalence partitioning
// PB3: BFS + Binary Search
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
int problem1(){
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    string s;
    cin>>s;
    int i= s.length() -1;
    string tmp;
    string ans="";
    while (i>=0) {
        if (s[i]=='0') {
            tmp = s.substr(i-2,2);
            char c = stoi(tmp)+'a'-1;
            ans += c;
            i-=3;
            //break;
        } else {
            tmp = s.substr(i,1);
            //cout<<tmp;
            char c = stoi(tmp)+'a'-1;
            ans += c;
            i-=1;
            //break;
        }
    }
    cout<<ans;
    return 0;
}
int n;
vector<pair<int,int>> info;
bool cmp(pair<int,int>&a, pair<int,int>&b) {
    if (a.first == b.first) return (a.second < b.second);
    return (a.first < b.first);
}
//sort(info.begin(), info.end(), cmp);
int problem2(){
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    cin>>n;
    info.resize(n);
    for (int i=0; i<n; i++){
        cin>>info[i].first;
        cin>>info[i].second;
    } 
    //sort(info.begin(), info.end(), cmp);
    vector<vector<int>> grps;
    grps.resize(n+1);
    //for (auto i:info) cout<<i.first<<" "<<i.second<<endl;
    int i = info.size()-1;
    int count = 1;
    grps[count].push_back(i);
    //int limit = info[0].second;
    while (i>0) {
        //push i to count bags
        if (info[i].second >= info[i-1].second) {
            count++;
        } else {
            info[i-1].second = info[i].second;
        }
        i--;
        grps[count].push_back(i);
    }
    vector<int> grp_size;
    for (int i=1; i<= count; i++) grp_size.push_back(grps[i].size());
    sort(grp_size.begin(), grp_size.end());
    cout<<count<<" "<<grp_size[grp_size.size()-1]<<" "<<grp_size[0]<<endl;
    return 0;
}
// Problem3: Road to LG
int m,x;
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
int problem3() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
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
int main() {
    return 0;
}