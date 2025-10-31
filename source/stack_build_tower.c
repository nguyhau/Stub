#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <bits/stdc++.h>
using namespace std;
int prob1_2() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n; cin >> n;
    vector<int> list;
    int nums; int count = 1;
    cin >> nums;   list.push_back(nums);
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
int n;
int pos1(vector<int>& v, int k, int count) {
    vector<int>::iterator upper;
    upper = upper_bound(v.begin(),v.begin()+count-1, k);
    //cout<<"Find "<<k<<" "<<mid<<" "<<map[mid]<<endl; 
    return (upper-v.begin());
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    cin>>n;
    vector<int> k(n);
    int tower_count = 0;
    vector<vector<int>> tower(n,vector<int> (1,INT_MAX));
    vector<int> top(n);
    for (int i=0; i<n;i++) {
        cin>>k[i];
        if (!tower_count) {
            tower[tower_count].push_back(k[i]);
            top[tower_count]=k[i];
            tower_count++;
            continue;
        }
        int temp = top[tower_count-1];
        if (k[i] >= temp) {
            tower[tower_count].push_back(k[i]);
            top[tower_count]=k[i];
            tower_count++;
        } else {
            int idx = pos1(top, k[i],tower_count);
            tower[idx].push_back(k[i]);
            top[idx]=k[i];
        }
    }

    cout<<tower_count;
    return 0;
}