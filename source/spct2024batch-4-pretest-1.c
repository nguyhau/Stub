// https://www.hackerrank.com/contests/spct2024batch-4-pretest-1/challenges
#include <bits/stdc++.h>
using namespace std;

int binStringToInt(string& s, int startPos, int len) {
    int ret = 0;
    for(int i = startPos; i < startPos + len; i++) {
        ret = ret * 2 + (s[i] - '0');
    }
    return ret;
}

int main() {
    int B;
    string base16, baseB, input;
    cin>>B>>base16>>baseB>>input;
    map<char, int> map16;
    int k;
    if (B==32) k = 5;
    else if (B == 64) k = 6;
    for(int i = 0; i < 16; i++) {
        map16[base16[i]] = i;
    }
    
    string binaryStr;
    for(int i = 0; i < input.size(); i++) {
        char c = input[i];
        int value = map16[c];
        //Convert int to binary string
        bitset<4> bits(value);
        binaryStr += bits.to_string();
    }
    //Add zeros
    int totalBits = binaryStr.size();
    int missingBitsCount = k - (totalBits % k);
    if (missingBitsCount == k) missingBitsCount = 0;
    binaryStr.append(missingBitsCount, '0');

    string result;
    //Divide binaryStr into segments of length k and convert to base B
    for(int i = 0; i < binaryStr.size()/k; i++) {
        //Convert binary string to int
        int intValue = binStringToInt(binaryStr, i*k, k);
        result += baseB[intValue];
    }
    cout<<result<<endl;
    return 0;
}
//
// PB2
#include <bits/stdc++.h>
using namespace std;
int N, K;
 
typedef pair<int, int> ii;
 
int ef[10004];
int A[10001]; //left -> right
int B[10001]; //load
int C[10001]; //right -> left
int D[10001]; //unload

//sort by the performance of each truck
//int : truckIndex
bool comp(const int & index1, const int& index2) {
    if (A[index1] + C[index1] == A[index2] + C[index2]) {
        return index1 > index2;
    }
    return A[index1] + C[index1] > A[index2] + C[index2];
}

//sort by the performance
//ii : pair<performance, truckIndex>
struct cmpef {
    bool operator()(ii const& p1, ii const& p2)
    {
        return p1.first > p2.first;
    }
};
 
 
void solve() {
    cin>>N>>K;
 
    for (int i = 0; i < K; i++) {
        cin>>A[i]; //left -> right
    }
    for (int i = 0; i < K; i++) {
        cin>>B[i]; //load
    }
    for (int i = 0; i < K; i++) {
        cin>>C[i]; //right -> left
    }
    for (int i = 0; i < K; i++) {
        cin>>D[i]; //unload
    }

    //calculate performance for each truck (depend on (A+C) and truckIndex)
    vector<int> w;
    for (int i = 0; i < K; i++) {
        w.push_back(i); //store trucks' index to w
    }
    sort(w.begin(), w.end(), comp);
    for (int i = 0; i < K; i++) {
        ef[w[i]] = i;
    }
    //queue for the truck which are waiting to use the bridge
    //ii : pair<performance, truckIndex>
    priority_queue<ii, vector<ii>, cmpef> l, r;
    
    //queue for the truck which are loading and unloading
    //ii : pair<finishTime, truckIndex>
    priority_queue<ii, vector<ii>, greater<ii>> load, unload;
    
    //Add all the truck to queue left
    for (int i = 0; i < K; i++) {
        l.push({ef[i], i});
    }
 
    int timeline = 0;
    int shipmentCount = N;
    //loop used to process at timeline
    while (N) {
        if (!r.empty()) { //has truck waiting to use the bridge from right side
            //take the truck which has the lowest performance
            int id = r.top().second;
            r.pop();
            //Update time to when the vehicle has crossed the bridge
            timeline += C[id];
            //add truck id to unload queue, will finish at {timeline + D[id]}
            unload.push({timeline + D[id], id});
            //Update the number of vehicles that need to cross the bridge
            N--;
        } else if (!l.empty() and shipmentCount > 0) { //has truck waiting to use the bridge from left side and has any shipment need to be moved
            //take the truck which has the lowest performance
            int id = l.top().second;
            l.pop();
            //Update time to when the vehicle has crossed the bridge
            timeline += A[id];
            //add truck id to load queue, will finish at {timeline + B[id]}
            load.push({timeline + B[id], id});
            //Update the number of shipments need to be moved
            shipmentCount--;
        } else {
            //if there is no truck which are waiting to use bridge -> Update timeline to the nearest time finish loading or unloading
            if (unload.empty()) {
                timeline = load.top().first;
            } else if (load.empty()) {
                timeline = unload.top().first;
            } else {
                timeline = min(load.top().first, unload.top().first);
            }
        }

        //Process all the loading job which has finished before timeline
        while (!load.empty() and load.top().first <= timeline) {
            int id = load.top().second;
            load.pop();
            //take the truck from load and add to right queue
            r.push({ef[id], id});
        }
 
        //Process all the unloading job which has finished before timeline
        while (!unload.empty() and unload.top().first <= timeline) {
            //take the truck from unload and add to left queue
            int id = unload.top().second;
            unload.pop();
            l.push({ef[id], id});
        }
    }
 
    //Output :  the time when the truck with the last batch of goods reach to the store
    cout<<timeline<<"\n";
 
   
}
 
 
int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1;
    //cin>>T;
    while (T) {
        solve();
        T--;
    }
 
    return 0;
}
//
#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef pair<int, int> ii;
int n,m,k;
//calculate movement time from a to b
int dist(ii& a, ii& b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}
int32_t main() {
    cin>>n>>m>>k;
    vector<string> arr(n);
    for(int i = 0; i < n; i++) {
        cin>>arr[i];
    }
    //Store the start position of An, Tuan
    vector<ii> startPos;
    //Store the position of flags
    vector<ii> flagPos;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if (arr[i][j] == 's') {
                startPos.push_back({i, j});
            } else if (arr[i][j] == 'f') {
                flagPos.push_back({i, j});
            }
        }
    }

    int minTotal = INT_MAX;
    int minDiff = INT_MAX;
    /*Generate a permutation of the order in which the flags are taken, assuming An takes them first and then Tuan.
    Example: n = 8
    With order : 0 7 2 3 1 6 4 5
    An takes 4 first flags -> An : {0,7,2,3}, Tuan : {1, 6, 4, 5}
    An takes 2 first flags -> An : {0,7}, Tuan : {2, 3, 1, 6, 4, 5}
    */
    do {
        /*Try each case An takes i flags
        -> An : 0 -> i-1
        Tuan : i -> k-1
        */
        for(int i = 0; i <= k; i++) {
            //Calculate the movement time of An (from 0 to i-1)
            int sA = 0;
            if (i > 0) {
                //movement time from startPos to the first flag
                sA += dist(startPos[0], flagPos[0]);
                //movement time from flag j to flag j+1
                for(int j = 0; j < i-1; j++) {
                    sA += dist(flagPos[j], flagPos[j+1]);
                }
                //movement time from startPos to the last flag to start position
                sA += dist(flagPos[i-1], startPos[0]);
            }
            //Calculate the movement time of Tuan (from i to k-1)
            int sB = 0;
            if (i<k) {
                //movement time from startPos to the first flag
                sB += dist(startPos[1], flagPos[i]);
                //movement time from flag j to flag j+1
                for(int j = i; j < k-1; j++) {
                    sB += dist(flagPos[j], flagPos[j+1]);
                }
                //movement time from startPos to the last flag to start position
                sB += dist(flagPos[k-1], startPos[1]);
            }
            int total = sA + sB;
            //Update the result
            if (total < minTotal) {
                minTotal = total;
                minDiff = abs(sA - sB);
            } else if (total == minTotal) {
                int diff = abs(sA - sB);
                minDiff = min(minDiff, diff);
            }
        }
    } while(next_permutation(flagPos.begin(), flagPos.end()));
    cout<<minTotal<<" "<<minDiff<<endl;
    return 0;
}