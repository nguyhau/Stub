// https://www.hackerrank.com/contests/spct-pretest-1-batch-4/challenges
// PB1: Use map structure 
// PB2: Use Binary Search, upper bound
// PB3: Use Back Track
#include <bits/stdc++.h>

using namespace std;
// PB1 
string s;
int find_maximum_towers(const int &start)
{
    if (start == s.length()) return 0;
    int number_of_firsts, number_of_seconds, result;
    result = number_of_firsts = number_of_seconds = 0;
    map<char,int> al_count;
    vector<char> temp;
    char idx;
    for (int i = 0; i < s.length(); ++i) {
        idx = s[i];
        if (!al_count[idx]) temp.push_back(idx);
        al_count[idx]++;
    }
    int numb_alpha = temp.size();
    al_count.clear();
    temp.clear();
    //cout<<numb_alpha<<endl;
    for (int i = 0; i < s.length(); ++i) {
        if (i < start) {
            continue;
        }
        idx = s[i];
        if (!al_count[idx]) temp.push_back(idx);
        al_count[idx]++;
        if (temp.size() == numb_alpha) {
            int n = al_count[temp[0]];
            bool next = false;
            for(int j=1; j< temp.size(); j++) {
                if (al_count[temp[j]] != n) {
                    next = true;
                    break;
                }
            }
            if (next) continue;
            else {
                temp.clear();
                al_count.clear();
                result++;
            }
        }
    }
    return result;
}

int problem1()
{
    cin >> s;
    cout << find_maximum_towers(0) << endl;
    return 0;
}
// PB2: Binary Search
int n;
int pos1(vector<int>& v, int k, int count) {
    vector<int>::iterator upper;
    upper = upper_bound(v.begin(),v.begin()+count-1, k);
    return (upper-v.begin());
}
int problem2() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    cin>>n;
    //vector<int> k(n);
    int k;
    int tower_count = 0;
    vector<vector<int>> tower(n,vector<int> (1,INT_MAX));
    vector<int> top(n);
    for (int i=0; i<n;i++) {
        cin>>k;
        if (!tower_count) {
            tower[tower_count].push_back(k);
            top[tower_count]=k;
            tower_count++;
            continue;
        }
        int temp = top[tower_count-1];
        if (k >= temp) {
            tower[tower_count].push_back(k);
            top[tower_count]=k;
            tower_count++;
        } else {
            int idx = pos1(top, k,tower_count);
            tower[idx].push_back(k);
            top[idx]=k;
        }
    }
    cout<<tower_count;
    return 0;
}
int problem2_2() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n; cin >> n;
    vector<int> list;
    int nums; int count = 1;
    cin >> nums;
    list.push_back(nums);
    for(int i = 1; i < n; i++){
        cin >> nums;
        //checking
        auto it = upper_bound(list.begin(),list.end(), nums);
        if(it!=list.end()){
            //cout << "value of it = " << *it << endl;
            *it = nums;
        }else{
            list.push_back(nums);
            count ++;
        }
    }
    cout << count << endl;
    return 0;
}
// PB3: Use back-track to check configure
int m,x;//n
//bool great();
int min_value = INT_MAX;
vector<int> cfg;
bool check_cfg(vector<int>& cfg) {
    for (int i=1; i<=m; i++) {
        if (cfg[i] < x) return false;
    }
    if (cfg[0] <= min_value) min_value = cfg[0];
    return true;
}
void bt(const vector<vector<int>>& value,const int index ) {
    //check cfg
    if (check_cfg(cfg)) return ;
    if (index == n) return ;
    // add index
    for (int i=0; i<=m; i++) {
            cfg[i]+= value[index][i];
    }
    bt(value, index+1);
    // restore
    for (int i=0; i<=m; i++) {
            cfg[i]-= value[index][i];
    }
    bt(value, index+1);
}
int problem3() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int ret = -1;
    cin>>n>>m>>x;
    cfg.resize(m+1,0);
    vector<vector<int>> v(n+1,vector<int> (m+1,0));
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<= m; j++) {
           cin>>v[i][j];
           v[n][j] += v[i][j];
        }
    }
    for (int j = 1; j<= m; j++) if (v[n][j] < x) {
        cout<<-1;
        return 0;
    }
    min_value = v[n][0];
    bt(v, 0);
    cout<<min_value<<endl;
    return 0;
}
// PB3: Use Dynamic Bit Mask
int problem3_2() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    int n, m, x; cin >> n >> m >> x;
    int costs[n], skills[n][m];
    for (int i=0; i<n; i++) {
        cin >> costs[i];
        for (int j=0; j<m; j++) cin >> skills[i][j];
    }
    int ans = 1e9;
    for (int i=0; i<(1 << n); i++) {
        vector<int> my_skill(m, 0);
        int total_cost = 0;
        for (int j=0; j<n; j++) {
            if (i & (1 << j)) {
                for (int k=0; k<m; k++) {
                    my_skill[k] += skills[j][k];
                }
                total_cost += costs[j];
            }
        }
        if (*min_element(my_skill.begin(), my_skill.end()) >= x) ans = min(ans, total_cost);
    }
    if (ans == 1e9) cout << -1 << endl;
    else cout << ans << endl;
    return 0;
}
int main() {
    return 0;
}