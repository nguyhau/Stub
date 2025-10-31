#include <bits/stdc++.h>
using namespace std;
void remove(vector<int> &v, int number) {
    while (number--) {
        v.pop_back();
    }
     
}
int main () {
    vector<int> myvector;
    for(int i=0; i<20; i++) myvector.push_back(i*2);
    for (auto idx:myvector) cout<<idx<<" ";
    cout<<endl;
    for(int i=0; i<3; i++) remove(myvector, i+1);
    for (auto idx:myvector) cout<<idx<<" ";
    cout<<endl;
    return 1;
}