//https://www.hackerrank.com/contests/spct2024batch-2-pretest-2/challenges
// PB1: Binary Search
// PB2: Greedy
// PB3: Brute Force, Boundary Valuate, check overlap object on matrix
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
#include <set>
using namespace std;


void problem1(){
    int n;
    vector<int>vote;
    vector<int>ranks;
    int m;
    vector<int> l_vote;
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    cin>>n;
    vote.resize(n);
    ranks.resize(n);
    int count = 1;
    for (int i=0; i<n; i++){
        cin>>vote[i];
    }
    sort(vote.rbegin(),vote.rend());
    for (int i=0; i<n; i++){
        if ((i>0) && (vote[i] < vote[i-1])) {
            count++;
        }
        ranks[i] = count;
    }
    cin>>m;
    l_vote.resize(m);
    for (int i=0; i<m; i++){
        cin>>l_vote[i];
    }
    //cout<<endl;
    for (int i=0; i<m; i++){
        int l=0,r=vote.size()-1;
        int ans=0;
        if (vote[l] <= l_vote[i]){
            cout<<1<<endl;
            continue;
        }
        if (vote[r] > l_vote[i]){
            cout<<(ranks[r]+1)<<endl;
            continue;
        }
        while (l<r) {
            int mid = l+(r-l)/2;
            if (vote[mid]<=l_vote[i]){
                r = mid;
            } else {
                ans = mid;
                l=mid+1;
            }
        }
        
        cout<<(ranks[ans]+1)<<endl;
    }
}
void problem1_2(){
    set<int> votes; 
    int n, m;
    int v;
    cin >> n;
    // put all vote to set to remove duplicate value (same value same rank)
    for(int i = 0; i < n; i++) {
        cin >> v;
        votes.insert(v);
    }
    vector<int> ladder;
    for(auto i: votes) {
        ladder.push_back(i);
    }

    cin >> m;
    int D;
    for(int i = 0; i < m; i++) {
        cin >> D;
        // find the postion of vote in increasing vector
        int index = lower_bound(ladder.begin(), ladder.end(), D) - ladder.begin(); 
        if(ladder[index] == D) {
            cout << ladder.size() - index << "\n"; // revert postion to get rank
        } else{ 
            cout << ladder.size() - index + 1 << "\n";
        }
    }
}
// For PB2
int n;
vector<pair<int,int>> price;
bool cmp(pair<int,int>&a, pair<int,int>&b) {
    //if (a.second -  == b.second) return (a.first < b.first);
    return ((a.second - a.first) > (b.second-b.first));
}
void problem2(){
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    cin>>n;
    price.resize(n);
    for (int i=0; i<n;i++) {
        cin>>price[i].first;
    };
    for (int i=0; i<n;i++) {
        cin>>price[i].second;
    };
    sort(price.begin(),price.end(),cmp);
    //for (auto i:price) cout<<i.first<<" "<<i.second<<endl;
    int rest = 0;
    int i = 0;
    int need = rest;
    while (i<n){
        if (rest < price[i].second) {
            need += price[i].second - rest;
            rest = price[i].second;
        }
        // update the rest after buy ith house
        rest -= price[i].first;
        //cout<<"Buy "<<(i)<<" need "<<need<<" rest "<<rest<<endl;
        i++;
    }
    cout<<need;
}
// For PB3
int m;
vector<vector<char>> mt;
bool check_valid(vector<vector<char>>&mt, int x, int y, int d) {
    //cout<<"Check "<<x<<" "<<y<<" "<<d<<endl;
    vector<pair<int,int>> mv={{-1,0},{1,0},{0,-1},{0,1}};
    int r,c;
    for (auto ad:mv) {
        r = x+ad.first*d;
        c = y+ad.second*d;
        if ((r<0)||(r>=n)||(c<0)||(c>=m)||(mt[r][c]!='P')) {
            //cout<<"False"<<endl;
           return false; 
        }
    }
    //cout<<"True"<<endl;
    return true;
}
bool cmp2(vector<int>v1, vector<int>v2) {
    return (v1[2]>v2[2]);
}
// Check over by mark the first pluses by special value
bool not_over(vector<vector<int>> v, int s, int t) {
    //cout<<"Check over "<<v[s][0]<<" "<<v[s][1]<<" and "<<v[t][0]<<" "<<v[t][1]<<endl;
    vector<pair<int,int>> mv={{-1,0},{1,0},{0,-1},{0,1}};
    int r,c;
    bool ret = true;
    // mark for s
    for (int i = 0; i<= v[s][2];i++){
        for (auto ad:mv) {
            r = v[s][0]+ad.first*i;
            c = v[s][1]+ad.second*i;
            mt[r][c]='0';
        }
    }
    for (int i = 0; i<= v[t][2];i++){
        for (auto ad:mv) {
            r = v[t][0]+ad.first*i;
            c = v[t][1]+ad.second*i;
            if (mt[r][c] =='0') {
                ret = false;
                //cout<<" --> False";
                break;
            }
        }
        if (!ret) break;
    }
    // restore for s
    for (int i = 0; i<= v[s][2];i++){
        for (auto ad:mv) {
            r = v[s][0]+ad.first*i;
            c = v[s][1]+ad.second*i;
            mt[r][c]='P';
        }
    }
    return ret;
}
vector<vector<int>>cfg;
void problem3(){
    cin>>n;
    cin>>m;
    mt.resize(n, vector<char>(m));
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) cin>>mt[i][j];
    }
    for (int i=0; i<n; i++) 
        for(int j=0; j<m; j++) if (mt[i][j] == 'P') {
            cfg.push_back({i,j,0});
            int d;
            for (d=1; d<(n+1)/2; d++) {
                if (!check_valid(mt,i,j,d)) break;
                cfg.push_back({i,j,d});
            }
        }
    sort(cfg.begin(), cfg.end(), cmp2);
    int opt = 0;
    int temp;
    //for (auto i:cfg) cout<<i[0]<<" "<<i[1]<<" "<<i[2]<<endl;
    //cout<<"Find optimize product"<<endl;
    for (int i=0; i< (cfg.size()-1); i++) {
        // if maximum product is less than opt -> break
        if (((4*cfg[i][2]+1)*(4*cfg[i][2]+1)) < opt) break;
        for (int j=i+1; j< cfg.size(); j++) {
            if (not_over(cfg,i,j)) {
                temp = (4*cfg[i][2]+1)*(4*cfg[j][2]+1);
                if (temp > opt){
                    opt = temp;
                    //cout<<i<<" "<<j<<" "<<opt<<endl;
                };
                break;
            }
        }
    }
    cout<<opt<<endl;
}
int main() {
    
    return 0;
}
