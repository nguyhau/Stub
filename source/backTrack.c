#include<bits/stdc++.h>
using namespace std;
// 1x1, 2x2, 3x3, 4x4, 5x5
int n;
vector<int> cfg;
vector<vector<int>> mt;
vector<int> cnt_pie;
int min_pie = INT_MAX;
int cnt;
bool stick_map(int x, int y, int len) {
    if (cnt_pie[len+1] == 0) return false;
    if(((x+len)>=n)||((y+len)>=n)) return false;
    for(int i=0; i<=len; i++){
        for(int j=0; j<=len; j++) if (mt[x+i][y+j] == 0) return false;
    }
    // set value
    for(int i=0; i<=len; i++){
        for(int j=0; j<=len; j++) mt[x+i][y+j] = 0;
    }
    return true;
}
//
int bt(int row, int col, int& cnt){
    // update
    if((row >= n)&&(col >= n)){
        if(min_pie > cnt) {
            //cout<<"Update min ";
            //for(int i=1; i<6; i++) cout<<cfg[i]<<" ";
            //cout<<endl;
            min_pie=cnt;
        }
        return 0;
    }
    if(cnt > min_pie) return 0;
    // find pos that val ==1
    while(row < n){
        while ((col<n)&&(mt[row][col])==0) col++;
        if(col == n){
            row++;
            col = 0;
        } else break;
    }
    //cout<<"Bt for "<<row<<" "<<col<<" "<<cnt<<endl;
    if(row < n) {        
        // try all from big -> small
        for(int k=4; k>=0; k--) {
            if(stick_map(row,col,k)){
                // add
                cnt_pie[k+1]--;
                cnt++;
                //cfg[k+1] = cnt_pie[k+1];
                //cout<<"call to "<<row<<" "<<(col+k)<<endl;
                bt(row, col+k+1, cnt);
                // restore
                cnt_pie[k+1]++;
                cnt--;
                // reset value
                for(int i=0; i<=k; i++){
                    for(int j=0; j<=k; j++) mt[row+i][col+j] = 1;
                }
            }   
        }
    } else{
        //cout<<"Update min at last piece "<<endl;
        if(min_pie > cnt) min_pie=cnt;
        return 0;
    }   
    return 0;
}
int main() {
    n=10;
    cnt_pie.resize(6,5);
    //cfg.resize(6);
    mt.resize(n, vector<int>(n, 0));
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++){
            cin>>mt[i][j];
        }
    }
    //
    bt(0,0,cnt);
    if (min_pie < INT_MAX) cout<<min_pie;
    else cout<<"-1";
    
    return 0;
}
// https://www.hackerrank.com/contests/spct2025batch-5-pretest-2/challenges/oz-witches
#include<bits/stdc++.h>
using namespace std;
int n,k,m;
vector<int> ls;
vector<bool> vs;
map<int,set<int>> map_dis;
vector<int> conf;
int count_ans = 0;
int p_count = 1;
bool check_cfg(vector<int>& v){
    int c_type=0;
    int pre = 0;
    if(map_dis[v[0]].count(v[n-1])>0) return false;
    for(int i=0; i<2*n; i++) {
        
        if(ls[v[i%n]]==pre) {
            c_type++;
            if (c_type > k) return false;
        }else {
            c_type=1;
            pre=ls[v[i%n]];
        }
    }
    //if(ls[v[n-1]]==ls[v[0]]) c_type++;
    if (c_type > k) return false;
    return true;
}
void print_cfg(vector<int>conf){
    for(int i=0; i<n;i++) cout<< conf[i]<<" ";
    cout<<endl;
    for(int i=0; i<n;i++) cout<< ls[conf[i]]<<" ";
    cout<<endl;
}
void bt(vector<int>&ls, vector<int>&conf, int idx, int p_count) {
    //
    if (conf.size() == n) {
        //check conf
        if(check_cfg(conf)) {
            count_ans++;            
        }
        return;
    }
    for(int i = 0; i< n; i++) {
        if (vs[i]) continue;
        if(map_dis[idx].count(i)>0) continue;
        if ((p_count == k)&& (ls[idx]==ls[i])) continue;
        // select i
        conf.push_back(i);
        vs[i] = true;
        if (ls[idx]!=ls[i]) p_count=1;
        bt(ls, conf, i, p_count);
        // non select i;
        conf.pop_back();
        vs[i] = false;
    }
}
int main() {
    cin>>n>>m>>k;
    ls.resize(n);
    vs.resize(n, false);
    //dis.resize(m);
    for(int i=0; i<n; i++) cin>>ls[i];
    int x,y;
    //cout<<" Dislike pair "<<endl;
    for(int j=0; j<m; j++){
        cin>>x>>y;
        map_dis[x-1].insert(y-1);
        map_dis[y-1].insert(x-1);
        //cout<<(x-1)<<" "<<(y-1)<<endl;
    }
    //cout<<"--------------------"<<endl;
    //
    vector<int> conf;
    // select i
    conf.push_back(0);
    vs[0] = true;
    bt(ls, conf, 0, p_count);
    cout<<count_ans;
    return 0;
}

