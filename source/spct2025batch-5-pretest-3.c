//https://www.hackerrank.com/contests/spct2025batch-5-pretest-3/challenges
#include <bits/stdc++.h>
using namespace std;
int n,m;
vector<vector<vector<int>>> mt;
int get_dist(int idx, vector<vector<vector<int>>>& mt, vector<int>&dist) {    
    priority_queue<pair<int,int>, vector<pair<int,int>>,greater<>>q;
    vector<bool> vs;
    vs.resize(n+1, false);
    
    q.push({0,idx});
    while(q.size()>0) {
        int d = q.top().first;;
        //int x = q.top()[1];
        int y = q.top().second;
        q.pop();
        if ( d < dist[y]) {
            vs[y] = true;
            dist[y] = d;
        } else{
            continue;
        } 
        for(int i=0; i<mt[y].size(); i++) {
            int v = mt[y][i][1];
            //int dyv=mt[y][i][0];
            //int newd = dist[y]+dyv;
            if (mt[y][i][0] > 0) {
                if (vs[v]) continue;

                if (dist[mt[y][i][1]] > (dist[y]+mt[y][i][0])) q.push({dist[y]+mt[y][i][0],mt[y][i][1]});
            }
        }
    }
    return dist[n];
}
//
//int p
int get_new(vector<vector<vector<int>>> mt, int x, int y){
    //cout<<"Disable "<<x<<" "<<y<<endl;
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
    dist2.resize(n+1, INT_MAX);
    //cout<<" calculte dist 2nd ";
    int d = get_dist(1, mt, dist2);
    //cout<<d<<endl;
    return d;
}
struct Edge {
    int to, w, id;
};
vector<vector<Edge>> mmap;
vector<tuple<int, int, int>> edg;
 
vector<int> solve(int start, vector<vector<Edge>> grap) {
    vector<int> dist(n + 1, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    dist[start] = 0;
    pq.emplace(0, start);
 
    while (!pq.empty()) {
        auto [curDist, u] = pq.top(); 
        pq.pop();
        if (curDist > dist[u]) 
            continue;
 
        for (auto& edge : grap[u]) {
            int v = edge.to;
            int w = edge.w;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
            }
        }
    }
    return dist;
}
int main() {
    cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    int ans = INT_MIN;
    cin>>n>>m;
    mt.resize(n+1);
    vector<vector<int>> listVer;
    mmap.assign(n + 1, {});
    for(int i=0; i<m; i++) {
        int x,y,d;
        cin>>x>>y>>d;
        mt[x].push_back({d,y});
        mt[y].push_back({d,x});
        listVer.push_back({x,y,d});
        mmap[x].push_back({y, d, i});
        mmap[y].push_back({x, d, i});
        edg.push_back({x, y, d});
    }
    vector<int> dist_1;
    vector<int> dist_n;
    dist_1.resize(n+1, INT_MAX);
    dist_n.resize(n+1, INT_MAX);
    //cout<<" calculte dist 1st ";
    // get current time
    std::time_t now = std::time(0);
    // Convert to a human-readable string
    char* date_time = std::ctime(&now);
    std::cout << "The start time is: " << date_time << std::endl;
    get_dist(1,mt, dist_1);
    //vector<int> startDist = solve(1, mmap);
    now = std::time(0);
    date_time = std::ctime(&now);
    std::cout << "The end time is: " << date_time << std::endl;
    get_dist(n,mt, dist_n);
    // for(int i=1; i<=n; i++) {
    //     cout<<"For edge "<<i<<" "<<dist_1[i]<<" "<<dist_n[i]<<endl;
    //     for(int j= 0; j<mt[i].size(); j++) cout<<mt[i][j][1]<<" "<<mt[i][j][0]<<endl;
    // }
    // get list edge
    // vector<pair<int,int>> eds;
    // int i = n-1;
    // pre[0] = -1;
    // while (i != 0){
    //     eds.push_back({i,pre[i]});
    //     i=pre[i];
    // }
    // for(int i=0; i< eds.size(); i++){
    //     //cout<<eds[i].first<<" "<<eds[i].second<<endl;
    //     int x=eds[i].first;
    //     int y=eds[i].second;        
    //     int d = get_new(mt, x, y);
    //     //cout<<"Disable "<<x<<" "<<y<<" "<<d<<endl;
    //     if ((d < INT_MAX)&&(d > ans)) {
    //         ans = d;
    //     }
    // } 
    
    for(int i=0; i<listVer.size(); i++){
        int x = listVer[i][0];
        int y = listVer[i][1];
        int d = listVer[i][2];
        //cout<<"Verter ["<<i<<","<<y<<"] = "<<d;
        if ((dist_1[x]+d+dist_n[y]) == dist_1[n]) {
            //cout<<" In short path"<<endl;
            //int tmpd = get_new(mt, x, y);
            // if ((tmpd < INT_MAX)&&(tmpd > ans)) 
            // {
            //     ans = tmpd;
            // }
        }
    }
    // for(int i=1; i<=n; i++) {
    //     for(int j=0; j<mt[i].size(); j++) {
    //         int y = mt[i][j][1];
    //         int d = mt[i][j][0];
    //         //cout<<"Verter ["<<i<<","<<y<<"] = "<<d;
    //         if ((dist_1[i]+d+dist_n[y]) == dist_1[n]) {
    //             //cout<<" In short path"<<endl;
    //             int tmpd = get_new(mt, i, y);
    //             if ((tmpd < INT_MAX)&&(tmpd > ans)) {
    //                 ans = tmpd;
    //             }
    //         }
    //         //cout<<endl;
    //     }
    // }
    
    if (ans > INT_MIN) cout<<ans;
    else cout<<"INF";
    return 0;
}
