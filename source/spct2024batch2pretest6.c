// https://www.hackerrank.com/contests/spct2024batch-2-pretest-6/challenges
// PB1: Priority queue + time line: HR consult
// PB2: Brute force & permutation: Tuan Headache
// PB3: Encode string and bit operator
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
// Use multiset or priority queue
vector<vector<int>> inps;
bool compare(vector<int>a, vector<int>b) {
    if (a[1] == b[1]) return (a[2] < b[2]);
    return (a[1] < b[1]);
};
// sort by duration, register order 
multiset<vector<int>, bool (*)(vector<int>, vector<int>)> waits(compare);

queue<vector<int>> q;
vector<bool> process;
int problem1() {
    int n;
    cin>>n;
    inps.resize(n, vector<int>(3));
    process.resize(n,false);
    for (int i=0; i< n; i++) cin>>inps[i][0];
    for (int i=0; i< n; i++) cin>>inps[i][1];
    for (int i=0; i< n; i++) inps[i][2]=i+1; //register order
    // sort by income time, duration
    sort(inps.begin(), inps.end());
    // push candidate to queue to travel
    q.push(inps[0]);
    process[0] = true;
    int start = 1;
    int tmp = inps[0][0]; // time stamp of session
    multiset<vector<int>>::iterator it;
    bool all_process = false;
    while ((!q.empty())) {
        vector<int> temp = q.front();
        cout<<temp[2]<<" ";
        q.pop();
        tmp+= temp[1];
        // process candidate when HR busy
        if (!all_process){
            for (int i = start; i<n; i++){
                if (!process[i]) {
                    start = i; // save previous postion
                    if (inps[i][0] <= tmp) {
                        //cout<<"Push to que "<<inps[i].first<<" "<<inps[i].second<<endl;
                        waits.insert(inps[i]); 
                        process[i] = true;
                    }
                    else {
                        break;
                    }
                    // mark if push all to queue
                    if (i == (n-1)){
                        all_process = true;
                    }
                }
            }
        }
        // Get next candidate
        if (waits.size() > 0) {
            // get first element to counsel
            it=waits.begin();
            q.push(*it);
            waits.erase (it);
        } else if (start < (n-1)){ // HR free and wait room empty
            q.push(inps[start]);
            tmp = inps[start][0];
            process[start] = true;
            start++;
        }       
    }
    return 0;
}

//
const int maxn = 1e5+2;
int a[maxn];
 
class Compare {
    public:
       bool operator()(pair<int, int> &a, pair<int,int> &b){
           if(a.first != b.first) return a.first > b.first;
           return a.second > b.second;
      }
};
 
void problem1_2() {
    int n; cin >> n;
    vector<vector<int>> arr(n, vector<int>(3, 0));
    for(int i = 0; i< n; i++) cin >> arr[i][0];
    for(int i = 0; i< n; i++) {
        cin >> arr[i][1];
        arr[i][2] = i;
    }
    sort(arr.begin(), arr.end());
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> q;
    int timestamp = arr[0][0];
    int pos = 0;
    while(pos < n && arr[pos][0] <= timestamp) {
        q.push({arr[pos][1], arr[pos][2]});
        pos++;
    }
    vector<int> ret;
    while(q.empty() == 0 || pos < n) {
        if(q.empty() == 1 && pos < n) {
            timestamp = arr[pos][0];
            while(pos < n && arr[pos][0] <= timestamp) {
                q.push({arr[pos][1], arr[pos][2]});
                pos++;
            }
        } else {
            int f = q.top().first;
            int s = q.top().second;
            q.pop();
            timestamp += f;
            ret.push_back(s+1);
            while(pos < n && arr[pos][0] <= timestamp) {
                q.push({arr[pos][1], arr[pos][2]});
                pos++;
            }
        }
    }
 
    for(int i=0; i<n; i++) {
        cout << ret[i] << " ";
    }
}
// PB2: Brute force & permutation
int problem2() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n; cin >> n;
    int m; cin >> m;
    int a[m], b[m], c[m], p[n+1];
    for (int i=0; i<m; i++) {
        cin >> c[i] >> a[i] >> b[i];
    }
    vector<int> arr(n);
    for (int i=0; i<n; i++) arr[i] = i+1;
    int ans = 0, count = 0;
    do {
		// gen all permutations
        int sum = 0;
        for (int i=0; i<n; i++) {
            p[arr[i]] = i;
        }
        for (int i=0; i<m; i++) {
            if (p[a[i]] < p[b[i]]) sum += c[i];
        }
        if (sum > ans) {
            count = 1;
            ans = sum;
        } else if (sum == ans) count++;
    } while (next_permutation(arr.begin(), arr.end()));
    
    cout << ans << " " << count << endl;
    return 0;
}

// PB3:Encode string and bit operator
string inp;
vector<string> ans;

int32_t problem3() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    cin>>inp;
    int len = inp.length();
    int pos = len%32;
    //cout<<"Pos "<<pos<<endl;
    int count = 0;
    bool bChar = false;
    string value;
    string dump="1111111111";
    int c_count=0;
    while (count < len) {
        //cout<<value<<endl;
        if (!bChar) {
            string temp;
            while (inp[count]<'a') {
                temp+=inp[count];
                count++;
            }
            //string to int
            int i_dec = std::stoi (temp);
            // int to binary string
            string temp_conv = "";
            temp_conv = to_string((i_dec&32)>>5) + to_string((i_dec&16)>>4)+to_string((i_dec&8)>>3)+to_string((i_dec&4)>>2)+to_string((i_dec&2)>>1)+to_string(i_dec&1);
            value += temp_conv;
            bChar = true;
            continue;
        }
        if (bChar) {
            int i_dec = inp[count]-'a'+1;            
            // int to binary string
            string temp_conv = "";
            temp_conv = to_string((i_dec&16)>>4)+to_string((i_dec&8)>>3)+to_string((i_dec&4)>>2)+to_string((i_dec&2)>>1)+to_string(i_dec&1);
            value += temp_conv;                        
            c_count++;
            if (c_count==2) {
                // add dump
                //cout<<"Before add "<<value<<endl;
                //while (value.length()<22) value= value+'1';
                int val_len = value.length();              
                if (pos>=val_len) {
                    while (value.length()<pos) value= value+'1'; 
                    while (value.length()<32) value= '1'+value;
                }else            
                {
                    value =  value.substr(0,val_len-pos)+dump+value.substr(val_len-pos,pos);
                }
                //cout<<"After add "<<value<<endl;
                // push value
                ans.push_back(value);
                value="";
                c_count = 0;
            }
            bChar = false;
            count++;
            continue;
        }
    }
    if (c_count > 0) {
        for (int i=0; i<11; i++) value = value+'0';
        int val_len = value.length();              
        if (pos>=val_len) {
                    while (value.length()<pos) value= value+'1'; 
                    while (value.length()<32) value= '1'+value;
        }else            
        {
            value =  value.substr(0,val_len-pos)+dump+value.substr(val_len-pos,pos);
        }
        //cout<<"After add "<<value<<endl;
        // push value
        ans.push_back(value);
    }
    for (auto i:ans) {
        long n;
        string temp;
        if (i[0]=='1') {
            string temp =i;
            for (int j=0; j<temp.length(); j++) 
                if (temp[j] == '1')temp[j] = '0';
                else temp[j] = '1';
            n = strtol(temp.c_str(), 0, 2);
            n++;
            cout<<'-';
        }
        else {
            n = strtol(i.c_str(), 0, 2);
        }        
        cout<<n<<" ";
    }
    return 0;
}

inline bool is_char(char c)
{
    return (c >= 'a' && c <= 'z') ? true : false;
}

inline bool is_digit(char c)
{
    return (c >= '0' && c <= '9') ? true : false;
}

inline int bit_set_to(int number, int n, bool x) {
    return (number & ~((int)1 << n)) | ((int)x << n);
}

inline int bit_set(int number, int n) {
    return (number | (1 << n));
}

inline bool bit_check(int number, int n) {
    return (number >> n) & (int)1;
}

int problem3_2() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    string s; cin >> s;
    int n = s.length(), count = 0;
    int startIndex = n % 32;
    int target_number = 0, pos = 31;
    
    for (int i=0; i<n; i++) {

        if (is_char(s[i])) {
            int num = 0;
            if (is_digit(s[i-1])) num += (s[i-1] - '0');
            if (i > 1 && is_digit(s[i-2])) num = num + 10 * (s[i-2] - '0');
            int num2 = 1 + (int) (s[i] - 'a');
            if (count % 2 == 0) {
                if (count > 0) cout << target_number << " ";

                target_number = 0;
                pos = 31;
                for (int j=0; j<10; j++) {
                    target_number = bit_set(target_number, (j + startIndex) % 32);
                }
            }
             // set 6 bits for number
            for (int j=5; j>=0; j--) {
                while (bit_check(target_number, pos)) pos--;

                target_number = bit_set_to(target_number, pos, bit_check(num, j));
                pos--;
            }
			 // set 5 bits for char
            for (int j=4; j>=0; j--) {
                
                while (bit_check(target_number, pos)) pos--;

                target_number = bit_set_to(target_number, pos, bit_check(num2, j));
                pos--;
            }
            count++;
        }
    }
    cout << target_number << endl;
    return 0;
}
int main() {
    return 1;
}