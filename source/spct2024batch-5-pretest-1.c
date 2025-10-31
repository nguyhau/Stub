// https://www.hackerrank.com/contests/spct2024batch-5-pretest-1/challenges/rain-distribution
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

vector<vector<long long>> fires;
deque<long long> firsts;
deque<long long> seconds;
int n;
long long a,b;
int Problem1() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    cin>>n;
    for (int i=0; i<n; i++) {
        cin>>a>>b;
        fires.push_back({a,b});
    }
    sort(fires.begin(), fires.end());
    long long tmp, max_len;
    max_len = 0;    
    for (int i=0; i<n; i++) {
        if ((firsts.size()>0)&&(seconds.back()>=fires[i][0])) {
            if ((seconds.size()>0)&&(seconds.back()<fires[i][1])) {
                //cout<<"Update back "<<fires[i][1]<<" to queue"<<endl;
                seconds.pop_back();
                seconds.push_back(fires[i][1]);
            }
        } else {
            // Update length
            //cout<<"Push "<<fires[i][0]<<" "<<fires[i][1]<<" to queue"<<endl;
            if (firsts.size()>0) {
                tmp = seconds.back()- firsts.back();
                //cout<<"Calculate lenth "<<tmp<<endl;
                if (max_len < tmp) max_len = tmp;
            }
            firsts.push_back(fires[i][0]);
            seconds.push_back(fires[i][1]);
        }
    }
    tmp = seconds.back()- firsts.back();
    if (max_len < tmp) max_len = tmp;
    cout<<max_len;
    return 0;
}
//
vector<vector<int>> custs;
vector<deque<int>> counters;
vector<int> numb_cus;
int k;
int Prob2() {
    cin>>n>>k;
    custs.resize(n, vector<int>(2));
    counters.resize(k);
    numb_cus.resize(k, 0);
    for (int i = 0; i<n; i++) {
        cin>>custs[i][0]>>custs[i][1];
    }    
    sort(custs.begin(), custs.end());
    int start, end;  
    for (int i = 0; i< n; i++) {
        start = custs[i][0];
        end = custs[i][1];
        int minwait_id = 0;
        //cout<<custs[i][0]<<" "<<custs[i][1]<<endl;
        deque<int> *q;
        for (int j = 0; j< counters.size(); j++) {
            q = &counters[j];
            // Update waiting
            //cout<<" Check for "<<j<<endl;
            while ((q->size() > 0)&&(q->front() <= start)) {
                numb_cus[j]++;
                q->pop_front();
            }
            // Update min
            if (q->size() < counters[minwait_id].size()) {
                minwait_id = j;
            }
            //counters[j] = q;
        }
        // Push to queue
        //cout<<"Push "<<start<<" "<<end<<" to "<<minwait_id<<endl;
        q = &counters[minwait_id];
        if (q->size() > 0) {
            q->push_back(q->back()+end);
        } else {
            q->push_back(start+end);
        }
        //counters[minwait_id] = q;
    }
    // cout all
    //cout<<"Latest"<<endl;
    int time = 0;
    for (int i = 0; i< k; i++) {
        if (counters[i].size() > 0){
            time = max(time, counters[i].back());
            numb_cus[i]+= counters[i].size();
        }
    }
    cout<<(time-1)<<endl;
    for (int i = 0; i< k; i++) {
        cout<<numb_cus[i]<<" ";
    }

    return 0;
}
int main() {
    return 0;
}
