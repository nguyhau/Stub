#include <bits/stdc++.h>
#include <stdio.h>

#define MAX_N (8)
#define ll long long
// x, y, id
using namespace std;
vector<pair<ll,ll>> pars;
pair<ll,ll> locA;
pair<ll,ll> locB;
int n;
vector<vector<int>> dp0;
vector<vector<int>> dp1;
int calDist(pair<int,int> a, pair<int,int> b) {
	return abs(a.first-b.first)+abs(a.second-b.second);
}
void Input_Data(void) {	
	cin>>n;
	cin>>locA.first>>locA.second;
	cin>>locB.first>>locB.second;
	pars.resize(n);
	for(int i=0; i<n; i++) {
		cin>>pars[i].first>>pars[i].second;
	}
	dp0.resize(256, vector<int>(3, INT_MAX));
	dp1.resize(256, vector<int>(3, INT_MAX));
	for(int i = 0; i<n; i++){
		dp0[1<<i][0]=calDist(locA,pars[i])*3;
		dp0[1<<i][1] = 1;
		dp0[1<<i][2] = i;
		dp1[1<<i][0]=calDist(locB,pars[i])*3;
		dp1[1<<i][1] = 1;
		dp1[1<<i][2] = i;
	}
    dp0[0][0]=0;
    dp1[0][0]=0;
    dp0[0][2]=-1;
    dp1[0][2]=-1;
	// dp[0][mask]+dp[1][mask2]
}
ll calculate0(int mask) {
	if (dp0[mask][0] != INT_MAX) {
		//cout<<"Calculate dp0 "<<mask<<" "<<dp0[mask][0]<<endl;
		return dp0[mask][0];
	}
	if (mask == 0){
        //dp0[newMask][2] = -1;
        return 0;
    } 
	int count = 0;
	for(int i=0; i<n; i++) {
		if (mask&(1<<i)) {
			count++;
            int newMask = mask-(1<<i);
			int tmp = calculate0(newMask); 
			int idx = dp0[newMask][2];
			int lev = dp0[newMask][1];
            if (idx != -1)
            {
                tmp += -calDist(locA,pars[idx])*(lev+1)+calDist(pars[i],pars[idx])*(lev+1)+calDist(locA,pars[i])*(lev+2);
            };
			
			if (dp0[mask][0] > tmp) {
				dp0[mask][0] = tmp;
				dp0[mask][2] = i;
			}
		}
	}
	dp0[mask][1] = count;
    // cout<<"Calculate dp0 "<<mask<<" "<<dp0[mask][0]<<endl;
    // cout<<"== Back trace"<<endl;
    // while (mask > 0) {
    //     cout<<mask<<" "<<dp0[mask][0]<<" "<<dp0[mask][1]<<" "<<dp0[mask][2]<<endl;
    //     int idx = dp0[mask][2];
    //     mask = mask-(1<<idx);
    // }
    // cout<<"== End Back trace"<<endl;
	//cout<<"Calculate dp0 "<<mask<<" "<<dp0[mask][0]<<endl;
	return dp0[mask][0];
}
ll calculate1(int mask) {
	if (dp1[mask][0] != INT_MAX) {
		//cout<<"Calculate dp1 "<<mask<<" "<<dp1[mask][0]<<endl;
		return dp1[mask][0];
	}
	if (mask == 0) return 0;
	int count = 0;
	for(int i=0; i<n; i++) {
		if (mask&(1<<i)) {
			count++;
			int newMask = mask-(1<<i);
			int tmp = calculate1(newMask); 
			int idx = dp1[newMask][2];
			int lev = dp1[newMask][1];
            if (idx != -1)
            {
                tmp += -calDist(locB,pars[idx])*(lev+1)+calDist(pars[i],pars[idx])*(lev+1)+calDist(locB,pars[i])*(lev+2);
            };
			//tmp += -calDist(locB,pars[idx])*(lev+1)+calDist(pars[i],pars[idx])*(lev+1)+calDist(locB,pars[i])*(lev+2);
			if (dp1[mask][0] > tmp) {
				dp1[mask][0] = tmp;
				dp1[mask][2] = i;
			}			
		}
	}
	dp1[mask][1] = count;
    // cout<<"Calculate dp1 "<<mask<<" "<<dp1[mask][0]<<endl;
    // cout<<"== Back trace"<<endl;
    // while (mask > 0) {
    //     cout<<mask<<" "<<dp1[mask][0]<<" "<<dp1[mask][1]<<" "<<dp1[mask][2]<<endl;
    //     int idx = dp1[mask][2];
    //     mask = mask-(1<<idx);
    // }
    // cout<<"== End Back trace"<<endl;
	//
	return dp1[mask][0];
}
void solve() {
    int mask=(1<<n)-1;
	calculate0(mask);
	calculate1(mask);
    int ans = INT_MAX;
	auto myCompare = [](vector<int>l, vector<int>r)->bool {
		return ((l[0]+l[1])>(r[0]+r[1]));
	};
	priority_queue<vector<int>,vector<vector<int>>, decltype(myCompare)> pq(myCompare);
	for(int i = 0; i<= mask; i++) {
		int maskB = mask-i;
		if (ans > (dp0[i][0]+dp1[maskB][0])){
            ans = dp0[i][0]+dp1[maskB][0];
            //cout<<"Update ans "<<i<<" "<<maskB<<" "<<ans<<endl;
        }
		//cout<<i<<" "<<dp0[i][0]<<" "<<dp1[maskB][0]<<endl;
	}
    //cout<<"Min is "<<ans<<endl;
    cout<<ans<<endl;
}
int main(void) {
	//int ans = -1;
	Input_Data();
	solve();
	//printf("%d\n", ans);

	return 0;
}