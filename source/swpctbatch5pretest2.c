// https://www.hackerrank.com/contests/swpct-batch-5-pretest-2/challenges
#include <bits/stdc++.h>
 
using namespace std;
typedef pair<int, int> iPair;
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<int> w;
bool checkValidation(vector<int>w, int val, int k) {    
    int day=0,i=0, sum =0;
    bool ret = true;
    while ( i < w.size()) {
        if (w[i] > val) {
            ret = false;
            break;
        } ;
        if (sum+w[i] > val) {
            day++;
            sum=0;
        }
        sum+=w[i];        
        if (day == k){
            ret = false;
            break;
        } ;
        i++;
    }
    //cout<<"Check for "<<val<<" "<<day<<" "<<ret<<endl;
    return ret;
}
int problem1() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    cin>>n>>k;
    w.resize(n);
    int ceil=0,floor;
    int sum = 0;
    int ans;
    for (int i=0; i<n; i++) {
        cin>>w[i];
        sum+=w[i];
        if(ceil < w[i]) ceil = w[i];
    }
    if (k == 1) cout<<sum<<endl;
    else {
        //ceil = ceil>(sum/(k-1)+1)?ceil:(sum/(k-1)+1);
        floor = sum/(k+1);
        int l=floor, r=sum;
        //cout<<l<<" "<<r<<endl;
        while (l<r) {
            int mid = (l+r)/2 +1;
            if (checkValidation(w,mid, k)) {
                ans = mid;
                r = mid-1;
            } else {
                l=mid+1;
            }
            //cout<<l<<" "<<r<<endl;
        }
        if (checkValidation(w,r, k)) {
                ans = r;
        }
        cout<<ans<<endl;
    }
    return 0;
}
int problem2() {
    int h,v;
    vector<vector<bool>> visit;
    cin>>h>>v;
    char c;
    queue<vector<int>> q;
    visit.resize(h, vector<bool>(v,false));
    for(int i=0; i<h; i++)
        for(int j=0; j<v; j++) {
            cin>>c;
            if (c=='#') {
                visit[i][j] = true;
                q.push({i,j, 0});
            }
        }
    // Start process
    int pre, count;
    pre = 0;
    count = 0;
    vector<int> tmp;
    vector<vector<int>> mov = {{-1,0},{1,0},{0,-1},{0,1}};
    while (q.size()>0) {
        tmp = q.front();
        q.pop();
        if (tmp[2] > pre) {
            count++;
            pre++;
        }
        for (auto idx:mov) {
            int r,c;
            r = idx[0]+tmp[0];
            c = idx[1]+tmp[1];
            if ((r<0)||(c<0)||(r==h)||(c==v)) continue;
            if (visit[r][c]) continue;
            q.push({r,c,tmp[2]+1});
            visit[r][c] = true; // soon mark to avoid re-push
        }
    }
    cout<<count<<endl;
    return 0;
}

int problem3() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int N, M;
    cin >> N >> M;
    vector<iPair> data;
    for (int i = 0; i < N; i++) {
        int A, B;
        cin >> A >> B;
        data.push_back({A, B});
    }
    // sort by increasing date
    sort(data.begin(), data.end());
    int ans = 0;
 
    int next = 0;
    priority_queue<int> pq;
 
    for(int i = 1; i < M + 1; i++) {
        // Push all avaiable task to queue
        while (next < N && data[next].first == i) {
            pq.push(data[next].second);
            next++;
        }
        if (!pq.empty()) {
            ans += pq.top(); // Each day must select one task
            pq.pop();
        }
    }
    cout << ans << endl;
    return 0;
}
int main() {
    return 0;
}