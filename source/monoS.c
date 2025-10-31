#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n;
vector<ll> v;
ll max_area = 0;
int main() {
    cin>>n;
    v.resize(n+1);
    for(ll i=1; i<=n; i++) cin>>v[i];
    stack<ll> st;
    st.push(1);
    ll temp_area;
    ll h;
    for(ll i=2; i<n; i++) {
        while((st.size()>0)&&(v[st.top()]> v[i])){
            h = v[st.top()];
            st.pop();
            if(st.size()>0) temp_area = (i-st.top()-1)*h;
            else temp_area = (i-1)*h;
            if(max_area < temp_area){
                max_area = temp_area;
            }
        }
        while((st.size()>0)&&(v[st.top()]== v[i])) st.pop();
        st.push(i);
    }
    h = v[st.top()];
    while(st.size()>1){
        st.pop();
        ll id=st.top();
        temp_area = (n-id)*h;
        if(max_area < temp_area){
            max_area = temp_area;
        }
        h = v[st.top()];
    }
    temp_area = n*h;
    if(max_area < temp_area){
        max_area = temp_area;
    }
    cout<<max_area;
    return 0;
}
// https://www.hackerrank.com/contests/spct2025batch-5-practice-1/challenges/hogwarts-3-1
#include <bits/stdc++.h>
using namespace std;
int n,q;
string s;
vector<int> ans;
vector<int> fw;
vector<int> bw;
int main() {
    cin>>n>>q;
    ans.resize(q);
    fw.resize(n);
    bw.resize(n);
    cin>>s;
    int c = 0;
    stack<char> mns;
    fw[0] = 0;
    for(int j=1; j<= n; j++) {
        while ((mns.size()>0)&&(s[j-1] <= mns.top())){
            if (s[j-1] < mns.top()) c++;
            mns.pop();
        }
        mns.push(s[j-1]);
        fw[j]=c+mns.size();
        //cout<<j<<" "<<fw[j]<<endl;
    }    
    stack<char> mns2;
    c=0;
    mns2.push(s[n-1]);
    bw[n-1]=1;
    //cout<<"=== back ==="<<endl;
    for(int j=n-2; j>0; j--) {
        while ((mns2.size()>0)&&(s[j] <= mns2.top())){
            if (s[j] < mns2.top()) c++;
            mns2.pop();
        } 
        mns2.push(s[j]);
        bw[j] = c+mns2.size();
        //cout<<j<<" "<<bw[j]<<endl;
    }   
    for(int i=0; i<q; i++) {
        int l,r;
        cin>>l>>r;
        l--;
        ans[i] = fw[l]+bw[r];
    }
    for(int i = 0; i<q; i++) cout<<ans[i]<<endl;
    return 0;
}

