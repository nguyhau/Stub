//https://www.hackerrank.com/contests/spct2024batch-2-pretest-5/challenges
// PB1 string operator: set + map
// PB2 simulate game: head->tail->head->tail
// PB3 binary search + divided group
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
const long long MOD = 1e9 + 7;
//#define int long long
#define endl "\n"
using namespace std;
// PB1 string operator
int t;
string inp;
int problem1() {
    cin>>t;
    set<char>::iterator it;
    int len;
    while (t>0) {
        // do
        set<char> temps;
        string out="";
        string dict = "";
        map<char,char> maps;
        cin>>inp;
        for (int i = 0; i< inp.length(); i++) {
            temps.insert(inp[i]);
        }
        for (auto i:temps) dict+= i;
        len = dict.length();
        for (int i=0; i< len; i++) {
            maps[dict[i]] = dict[len-i-1];
        }
        for (int i = 0; i< inp.length(); i++) {
            out+=maps[inp[i]];
        }
        cout<<out<<endl;
        // decrease tc
        t--;
    }
    return 0;
}
// PB2 simulate
int n,m,k;
vector<int> boats;
int32_t problem2() {
    cin>>n>>m>>k;
    int ans = 0;
    boats.resize(n);
    bool bfirst = true;
    for (int i = 0; i<n; i++) {
        cin>>boats[i];
    };
    int head = 0, tail=n-1;
    int def_1, def_n, min_def;
    while ((tail-head+1) >(n- m)) {
        def_1 = boats[head] / k;
        def_n = boats[tail] / k;
        min_def = def_1>def_n?def_n:def_1;
        if (min_def>1) {
            boats[head] = boats[head] - (min_def-1)* k;
            boats[tail] = boats[tail] - (min_def-1)* k;
            ans+=2*(min_def-1);
        }
        if (bfirst) {
            boats[head] = boats[head] - k;
            if (boats[head] <= 0) head++;
            bfirst = false;
            ans++;
        } else {
            boats[tail] = boats[tail] - k;
            if (boats[tail] <= 0) tail--;
            bfirst = true;
            ans++;
        }
    }
    cout<<ans;
    return 0;
}
int problem2_2() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int m, n, k;
    cin>> n  >> m >> k;
    vector<int> A(n);
    for(int i = 0; i < n; i++) {
        cin>> A[i];
        if(A[i] % k == 0) A[i] = A[i] / k;
        else A[i] = A[i] / k + 1;
    }
    const int HEAD = 0;
    const int TAIL = 1;
    int pos = HEAD;
    int headI = 0, tailI = n - 1;
    long long ret = 0;
    while(m > 0) {
        //So sanh thuyen o dau va cuoi xem thuyen nao se chim tiep theo
        if(A[headI] < A[tailI]) { // => danh chim thiyen o head truoc
            if(pos == HEAD) {
                ret = ret + (A[headI] + A[headI] - 1);
                A[tailI] -= (A[headI] - 1);
            } else {
                ret = ret + A[headI] + A[headI];
                A[tailI] -= A[headI];
            }
            headI++;
            pos = TAIL;
        } else if(A[headI] > A[tailI]) { // => danh chim tail truoc
            if(pos == HEAD) {
                ret = ret + (A[tailI] + A[tailI]);
                A[headI] -= A[tailI];
            } else{
                ret = ret + (A[tailI] + A[tailI] - 1);
                A[headI] -= (A[tailI] - 1);
            }
            tailI--;
            pos = HEAD;
        } else {
            if(pos == HEAD) { //=> danh chim head truoc
                ret = ret + (A[headI] + A[headI] - 1);
                headI++;
                A[tailI] = 1;
                pos = TAIL;
            } else { //danh chim tail truoc
                ret = ret + (A[tailI] + A[tailI] - 1);
                tailI--;
                A[headI] = 1;
                pos = HEAD;
            }
        }
        m--;
    }
    cout << ret << "\n";
    return 0;
}
//PB3 binary search
int h;
vector<int> locs;
bool check_valid(vector<int>& locs, int h, int ef) {
    int numb = 0;
    for (int i=0; i<(locs.size()-1); i++) {
        if (locs[i+1]-locs[i]>=ef) numb+=ef;
        else {
            numb+=locs[i+1]-locs[i];
        }
        if (numb >= h) return true;
    }
    numb+=ef;
    if (numb < h) return false;
    return true;
}
int32_t problem3() {
    cin>>n>>h;
    locs.resize(n);
    set<int> pts;
    vector<int> filter;
    int ans;
    for (int i = 0; i< n; i++){
        cin>>locs[i];
        pts.insert(locs[i]);
    }
    for(auto k:pts) filter.push_back(k);
    int l=1, r=h+1;
    int maxrange = log2(r-l);
    //cout<<maxrange;
    int count = 0;
    while (count < maxrange) {
        int mid = l+(r-l)/2;
        if (check_valid(filter, h, mid)) {
            ans = mid;
            r = mid;
            count++;
        } else {
            l = mid+1;
            count++;
        }
    }
    for (int i = l; i<= r; i++) {
        if (check_valid(filter, h, i)) {
            if (i<ans) ans = i;
            break;
        }
    }
    cout<<ans;
    return 0;
}

int32_t main () {
    return 0;
}