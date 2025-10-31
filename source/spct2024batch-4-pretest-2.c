//https://www.hackerrank.com/contests/spct2024batch-4-pretest-2/challenges
#include<bits/stdc++.h>
using namespace std;
bool is_palindrome(int time) {
    int hour = time / 60;
    int minutes = time % 60;
    // HH:MM
    return ((hour / 10) == (minutes % 10))
        && ((hour % 10) == (minutes / 10));
}
void test_case() {
    string s;
    int x;
    cin >> s >> x;
    int time = 0;
    int hour = (s[0] - '0') * 10 + (s[1] - '0');
    int minutes = (s[3] - '0') * 10 + (s[4] - '0');
    time = 60 * hour + minutes;
    set<int> all_time;
    for(int i = 0; i < 1440; ++i) {
        all_time.insert(time);
        time += x;
        time %= 1440;
    }
    int res = 0;
    for(auto& x : all_time) {
        if(is_palindrome(x)) ++res;
    }
    cout << res << endl;
}
int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; ++i)
        test_case();
    return 0;
}
//PB2
#include<bits/stdc++.h>
#define int long long
using namespace std;


// 1. Gen het tat ca truong hop phep toan OK
// 2. Tinh ket qua phep toan
// 3. Check ket qua co phai so dac biet khong


vector<string> all;
void backtrack(string& cur, const string& s, int i) {
    if(i == (int)s.size()) {
        all.push_back(cur);
        return;
    }
    // them dau cong
    cur += '+';
    cur += s[i];
    backtrack(cur, s, i + 1);
    cur.pop_back();
    cur.pop_back();
    
    // them dau tru
    cur += '-';
    cur += s[i];
    backtrack(cur, s, i + 1);
    cur.pop_back();
    cur.pop_back();
    
    // khong lam gi
    cur += s[i];
    backtrack(cur, s, i + 1);
    cur.pop_back();
}
int cal(const string& s) {
    int res = 0;
    int cur = 0;
    int sign = 1;
    for(int i = 0; i < (int)s.size(); ++i) {
        if(s[i] == '+') {
            res += cur * sign;
            cur = 0;
            sign = 1;
        } else if(s[i] == '-') {
            res += cur * sign;
            cur = 0;
            sign = -1;
        } else {
            cur = cur * 10 + (s[i] - '0');
        }
    }
    return res + sign * cur;
}
bool is_special(int x, vector<int>& f) {
    vector<int> fre(10);
    string s = to_string(abs(x));
    for(auto& i : s) {
        fre[i-'0']++;
    }
    for(int i = 0; i < 10; ++i) {
        if(f[i] == -1)
            continue;
        if(f[i] != fre[i])
            return false;
    }
    return true;
}
void test_case() {
    string s;
    cin >> s;
    vector<int> f(10);
    for(auto& x : f) cin >> x;
    string cur = string(1, s[0]);
    all.clear();
    backtrack(cur, s, 1);
    int res = 0;
    for(auto& x : all)
    {
        int val = cal(x);
        if(is_special(val, f))
            ++res;
    }
    cout << res << endl;
    
}
int32_t main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; ++i)
        test_case();
    return 0;
}
//PB3
#include<bits/stdc++.h>
#define int long long
using namespace std;

// Test san pham co thoi gian het han gan nhat -> prority_queue<>
// tai thoi diem T: neu co san pham di vao o T -> add no vao priority_queue
// Tai thoi diem T: neu co san pham chua kip test, het han -> bo ra khoi queue
// Tai thoi diem T bat ky, minh dem dc co bao nhieu may dang hoat dong (X) -> bo ra queue (X) thang dau tien

int32_t main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> machines(n);
    for(auto& x : machines) cin >> x.first >> x.second;
    vector<pair<int, int>> products(m);
    for(auto& x : products) {
        cin >> x.first >> x.second;
        x.second += x.first;
    }
    // [1, 5] [9, 11] [5, 8] -> [1, 5] [5, 8] [9, 11] [101, 102] 100
    sort(products.begin(), products.end());
    int it = 0;
    int res = 0;
    priority_queue<int, vector<int>, greater<int>> pq;
    for(int t = 1; t <= 1e8; ++t) {
        // Them san pham vao queue
        while(it < m && products[it].first <= t)
        {
            pq.push(products[it].second);
            it++;
        }
        
        // Bo di nhung san pham het han
        while(pq.size() && pq.top() < t) {
            pq.pop();
        }
        // Dem so may dang hoat dong
        int cnt = 0;
        for(auto& x : machines) {
            if(x.first <= t && t <= x.second)
                ++cnt;
        }
        // Moi may test 1 sp
        for(int i = 0; i < cnt; ++i) {
            if(pq.size()) {
                pq.pop();
                res++;
            }
        }
       
    }   
    cout << res;
    return 0;
}
