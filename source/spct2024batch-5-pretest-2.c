#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

int n,m;
vector<int> miles;
map<string,int> listm;
map<int,string> getname;
vector<vector<int>> data_votes;
vector<vector<int>> data_miles;
vector<int> wins;
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    freopen("input.txt", "r", stdin);
    cin>>n>>m;
    miles.resize(m);
    // data_votes.resize(m+1, vector<int>(n,0));
    // data_miles.resize(m+1, vector<int>(n,0));
    //data_votes.resize(m+1);
    //data_miles.resize(m+1);
    wins.resize(n, 0);
    int count = -1;
    int id, pre_find;
    for(int i=0; i<m; i++) {
        cin>>miles[i];
    }
    pre_find = 0;
    for(int i=0; i<n; i++) {
        string tmp;
        long time;
        cin>>tmp>>time;
        //cout<<"=== Process "<<tmp<<" at "<<time<<endl;
        map<string,int>::iterator it;
        it = listm.find(tmp);
        if (it == listm.end()) {
            count++;
            listm.insert(pair<string,int>(tmp,count));
            getname[count]=tmp;
            //votes[count].push_back(time);
            id=count;
            data_votes.push_back(vector<int>(m+1,0));
            data_miles.push_back(vector<int>(m+1,0));
        }else {
            //votes[it->second].push_back(time);
            id = it->second;
        }
        // update vote for miles
        std::vector<int>::iterator low;
        low=std::lower_bound (miles.begin()+pre_find, miles.end(), time);
        pre_find = low-miles.begin();
        for(int j=low-miles.begin(); j<= m; j++) {
            data_votes[id][j]++;
            data_miles[id][j]=time;
            //cout<<getname[count]<<" is "<<data_votes[j][count]<<endl;
        }
    }
    //
    // for (int i=0; i<= m; i++) {
    //     cout<<"===== Vote at "<<miles[i]<<endl;
    //     for (int j=0; j<= count; j++) {
    //         cout<<" Vote of "<<getname[j]<<" is "<<data_votes[i][j]<<endl;
    //     }
    // }
    //
    for (int i=0; i<m; i++) {
        int win = 0;
        for (int j=1; j<= count; j++) {
            if (data_votes[j][i] > data_votes[win][i]) {
                win = j;
            } else if ((data_votes[j][i] == data_votes[win][i])&&(data_miles[j][i] > data_miles[win][i])) {
                win = j;
            }
        }
        wins[win]++;
        //wins[idx][1]=data_miles[i][idx];
        //cout<<"Winer at "<<miles[i]<<" is "<<getname[idx]<<" with "<<data_votes[i][idx]<<endl;
    }
    int global_win = 0;
    for (int i=1; i<= count; i++) {
        if (wins[i] > wins[global_win]) {
            global_win = i;
        }
        else if ((wins[i] == wins[global_win])&&(data_votes[i][m] > data_votes[global_win][m])) {
            global_win = i;
            //cout<<"Last vote of "<<getname[i]<<" is "<<data_votes[m][i]<<endl;
        }
    };
    cout<<getname[global_win]<<endl;
    return 0;
}
