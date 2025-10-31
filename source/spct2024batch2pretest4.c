// https://www.hackerrank.com/contests/spct2024batch-2-pretest-4/challenges
// PB1 dynamic program + convert string to long long
// PB2: String operator: get string contain space, check markup tag
// PB3 Binary search + lower_bound + divided
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
// const long long MOD = 1e9 + 7;
 #define int long long
// #define endl "\n"
// #define pb push_back
// const int maxn = 1e5+2;
// PB 1 dynamic program
int n;
vector<vector<string>> mt;
string temp;
string opt="";
vector<char> cfg;
long long convert(string s) {
    long long value = 0;
    int len = s.length();
    for(int i = len-1;i>=0; i--) {
        if (s[i]=='1') {
            value+=1LL<<(len-i-1);
        }
    }
    return value;
};
vector<vector<string>>dp;
int problem1() {
    cin>>n;
    mt.resize(n,vector<string>(n));
    for(int i=0; i<n; i++) {
        for (int j=0; j<n; j++) cin>>mt[i][j];
    }
    // Init for boundary
    dp.resize(n, vector<string> (n,""));
    dp[n-1][n-1] = mt[n-1][n-1];
    for (int i = n-2; i>=0; i--) dp[i][n-1] = mt[i][n-1]+dp[i+1][n-1];
    for (int i = n-2; i>=0; i--) dp[n-1][i] = mt[n-1][i]+dp[n-1][i+1];
    // Calculate for other
    for (int i = n-2; i>=0; i--)
        for(int j=n-2; j>=0;j--) {
            //dp[i][j] = mt[i][j]+ max(dp[i][j+1],dp[i+1][j]);
            // or original
            vector<pair<int,int>> next = {{0,1},{1,0}} ;
            for (auto k:next) {
                temp = mt[i][j]+dp[i+k.first][j+k.second];
                if (dp[i][j] < temp){
                    dp[i][j] = temp;
                }
            }
        }
    cout<<convert(dp[0][0]);
    return 0;
}
// 

int problem1_2() {
    int n;
    string F[50][50];
    long long a;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a;
            // Handle for each row when input
            string ch = (a == 1) ? "1" : "0";
            F[i][j] = max(F[i-1][j], F[i][j-1]) + ch;
        }
    }
    cout << strtoull(F[n][n].c_str(), 0, 2);
    return 0;
}
// PB2: String operator
string inp;
string out;
int problem2() {
    getline(cin,inp);
    int i = 0;
    bool bopen = false;
    string temp = "";
    while (i< inp.length()) {
        
        if (inp[i] == '<') {
            bopen = true;
            out+= '<';
            i++;
            continue;
        }
        if ((inp[i] == '>')&& bopen) {
             bopen = false;
             out+= '>';
             i++;
            continue;
        }
        while ((i< inp.length())&&(inp[i] == ' ')) {
            out+=inp[i];
            i++;
        }
        while ((i< inp.length())&&(inp[i] != '<')&&(inp[i] != '>')&&(inp[i] != ' ')) {
            temp+= inp[i];
            i++;
        }
        if (bopen) {
            out += temp;
            temp = "";
        } else {
            for (int j = temp.length()-1; j>= 0; j--) {
                out+=temp[j];
            }
            temp = "";
        }
    }
    cout<<out;
    return 0;
}

// PB3 Binary search
int k;
vector<int>w;
vector<int>acc_w;
bool check_val(vector<int>&sum, int k, int capa) {
    vector<int>::iterator it;
    int count = 0;
    int acc_capa = 0;
    //cout<<"Check for "<<capa<<endl;
    while (count < k) {
        acc_capa+=capa;
        it = lower_bound(sum.begin(), sum.end(), acc_capa);
        if (it == sum.end()) return true;
        if (*it > acc_capa) acc_capa = *(it-1);
        //cout<<count<<" "<<acc_capa<<endl;
        count++;
    }
    //cout<<endl;
    if (acc_capa < sum[sum.size()-1]) return false;
    return true;
}
int problem3() {
    cin>>n>>k;
    w.resize(n);
    acc_w.resize(n);
    int sum = 0;
    for(int i=0; i<n; i++) {
        cin>>w[i];
        sum+=w[i];
        acc_w[i] = sum;
    }
    int ans = 0;
    //for(int i=0; i<n; i++) cout<<acc_w[i]<<" ";
    //cout<<endl;
    for (int i = acc_w[0]; i<= acc_w[n-1]; i++) {
        if (check_val(acc_w, k, i)) {
            ans = i;
            break;
        }
    }
    cout<<ans;
    return 0;
}

int32_t main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
#endif
	int t;
	cin >> t;
	while (t--)
	{
		//solve();
	}
 
	return 0;
}