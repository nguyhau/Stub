//https://www.hackerrank.com/contests/spct2025batch-1-pretest-1/challenges
#include <bits/stdc++.h>
using namespace std;

//PB1:
int n, q;
vector<int> a;
map<int,vector<int>> ma;
vector<int>ans;
int PB1() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    cin>>n;
    a.resize(n);
    for (int i=0; i<n; i++) {
        cin>>a[i];
        ma[a[i]].push_back(i+1);
    }
    cin>>q;
    for(int i=0; i<q; i++) {
        int l, r, x;
        cin>>l>>r>>x;
        vector<int> *tmp = &ma[x];
        if (tmp->size() > 0) {
            int st,ed;
            st = lower_bound(tmp->begin(),tmp->end(), l) - tmp->begin();
            ed = upper_bound(tmp->begin(),tmp->end(), r)- tmp->begin()-1;
            cout<<ed-st+1<<endl;
        } else {
            cout<<0<<endl;
        }
        
    }
    return 0;
}

int k,m;
map<int, vector<int>> map_edge;
vector<vector<int>> ver; // 0:->sum_node, 1: count_node, 2:sum_node
vector<bool> visit;
vector<int> acc;
// Custom comparator
struct CustomCompare {
    bool operator()(const pair<int, int>& p1, const pair<int, int>& p2) {
        if (p1.second == p2.second) return p1.first > p2.first;
        return p1.second > p2.second;
    }
};
int PB2() {
    priority_queue<pair<int, int>, vector<pair<int, int>>, CustomCompare> pq;
    cin>>n>>k>>m;
    ver.resize(n+1, vector<int>(3));
    visit.resize(n+1, false);
    // create adjacent list
    for(int i=0; i<(n-1); i++) {
        int u,v;
        cin>>u>>v;
        map_edge[u].push_back(v);
        map_edge[v].push_back(u);
    }
    // push all node to pq
    for(auto idx:map_edge) {
        pq.push({idx.first,idx.second.size()});
    }
    for(int i=1; i<=n; i++) {
        cin>>ver[i][0];
        ver[i][0]%=k;
        ver[i][1]=1;
        ver[i][2]=map_edge[i].size();
    }
    int count = 0;
    while (pq.size() > 0) {
        pair<int,int> p = pq.top();
        pq.pop();
        int idx = p.first;
        //cout<<idx<<" has sum "<<ver[idx][0]<<" and "<<ver[idx][1]<<" node" <<endl;
        if (visit[idx]) continue;        
        vector<int> ls_idx = map_edge[idx]; // list adjacent
        // update for all adjacent
        int tmp;
        for (int i = 0; i< ls_idx.size();i++) { // get current parent of leave
            tmp = ls_idx[i]; 
            if (visit[tmp]) continue;
            ver[tmp][2]--;
            pq.push({tmp,ver[tmp][2]});
            break;
        }  
        if ((ver[idx][1] < m)||((ver[idx][0]%k)!=0)) { // Merge to other
            ver[tmp][0]+=ver[idx][0];
            ver[tmp][1]+=ver[idx][1];
        } else {
            count++;
            //cout<<" break brand"<<endl;
        };
        visit[idx] = true;
    }
    cout<<count;
    return 0;
}

map<int, vector<int>> m_edge;
vector<vector<long long>> sum;

long long get_sum(int u,int k) {
    if (sum[u][k] > 0) return sum[u][k];
    queue<pair<int,int>> q;
    vector<bool> visit;
    visit.resize(n+1, false);
    q.push({u,0});
    for(int i=1; i<=k; i++) {        
        while (q.size()>0) {
            pair<int,int> tmp = q.front();
            if (tmp.second > i) {
                //cout<<"break level: sum["<<u<<"]["<<i<<"] = "<<sum[u][i]<<endl;
                break; // new level
            }
            //cout<<"pop "<<tmp.first<<" level "<<tmp.second<<endl;
            q.pop();
            if (visit[tmp.first]) continue; //ignore
            for (auto new_e:m_edge[tmp.first]) {
                if (visit[new_e]) continue;
                q.push({new_e,tmp.second+1});
                //cout<<"put "<<new_e<<" level "<<tmp.second+1<<endl;
            }
            if (tmp.second == i) sum[u][i]+=tmp.first;
            visit[tmp.first] = true;
        }
        sum[u][i]+=sum[u][i-1];
    }        
    return sum[u][k];
}

int PB3() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    cin>>n>>m;
    sum.resize(n+1,vector<long long>(4,0));
    for(int i=1; i<=n; i++) {
        sum[i][0] = i;
    }
    for(int i=0; i<m; i++) {
        int u,v;
        cin>>u>>v;
        m_edge[u].push_back(v);
        m_edge[v].push_back(u);
    }
    cin>>q;
    for(int i=0; i<q; i++) {
        int x,k;
        cin>>x>>k;
        get_sum(x,3);
        cout<<get_sum(x,k)<<endl;
    }
    return 0;
}
bool dfs(int u, int r, int& count) {
    for (int i=0; i< map_edge[u].size(); i++) {
        int v = map_edge[u][i];
        if (v == r) continue;
        bool ret = dfs(v, u, count);
        if (ret) {
            //cout<<"Detach at "<<v<<" ver[v][0] "<<ver[v][0]<<" ver[v][1] "<<ver[v][1]<<endl;
            count++;
        } else {
            ver[u][0]+=ver[v][0];
            ver[u][1]+=ver[v][1];
        }
        visit[v]=true;
    }
    if ((ver[u][1]<m)||((ver[u][0]%k)!= 0)) return false;
    return true;
}
int PB2_pass() {
    priority_queue<pair<int, int>, vector<pair<int, int>>, CustomCompare> pq;
    cin>>n>>k>>m;
    ver.resize(n+1, vector<int>(3));
    visit.resize(n+1, false);
    for(int i=0; i<(n-1); i++) {
        int u,v;
        cin>>u>>v;
        map_edge[u].push_back(v);
        map_edge[v].push_back(u);
    }
    for(auto idx:map_edge) {
        pq.push({idx.first,idx.second.size()});
    }
    for(int i=1; i<=n; i++) {
        cin>>ver[i][0];
        ver[i][0]%=k;
        ver[i][1]=1;
        ver[i][2]=map_edge[i].size();
    }
    int count = 0;
    for (int i =1; i<=n; i++) {
        if (visit[i]) continue;
        bool ret = dfs(i,0, count);
        if (ret) count++;
    }
    cout<<count;
    return 0;
}
int main() {
    return 0;
}