#include <bits/stdc++.h>
using namespace std;
void init_matrix_graph(vector<vector<int>>& mt, int m, int n) {
    mt.resize(m, vector<int>(n, 2));
    // for (auto i:mt) {
    //     for (auto j:i) cout<<j<<" ";
    //     cout<<endl;
    // }
};
void print_mt_gr(vector<vector<int>>& mt, int m, int n) {
    //mt.resize(m, vector<int>(n, 0));
    for (auto i:mt) {
        for (auto j:i) cout<<j<<" ";
        cout<<endl;
    }
};
void int_adjacent_graph(vector<set<int>>& adj_graph, vector<vector<int>>& mt) {
    int m = mt.size();
    int n = mt[0].size();
    adj_graph.resize(m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (mt[i][j] > 0) adj_graph[i].insert(j);
        }
    }
    for (int i = 0; i <adj_graph.size(); i++) {
        cout<<"adjacent of "<<i<<" ";
        for (auto j:adj_graph[i]) cout<<j<<" ";
        cout<<endl;
    }
}
//void dist_from()
void calculate_dist(vector<set<int>>& adj_graph, vector<vector<int>>& mt, vector<vector<int>>& dist) {
    int m = mt.size();
    dist.resize(m, vector<int> (m, INT_MAX));
    for (int i = 0; i <dist.size(); i++) {
        cout<<"distant from "<<i<<" ";
        for (auto j:dist[i]) cout<<j<<" ";
        cout<<endl;
    }
    for (int i = 0; i <dist.size(); i++) {
        for (auto j:adj_graph[i]) {
            
        }
    }
}
int main() {
    vector<vector<int>> mt = {  {0,4,0,5,0},
                                {0,6,1,0,0},
                                {0,0,0,3,0},
                                {0,0,1,0,2},
                                {1,0,0,4,0}
                                };
    vector<set<int>> adj;
    vector<vector<int>> dist;
    //init_matrix_graph(mt, 2,3);
    print_mt_gr(mt, 2,3);
    int_adjacent_graph(adj, mt);
    calculate_dist(adj, mt, dist);
    return 0;
}