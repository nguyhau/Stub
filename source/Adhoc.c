//https://www.hackerrank.com/contests/spct2024batch-2-pretest-1/challenges/lgedvs-marathon-2
#include <bits/stdc++.h>
using namespace std;
int n;
vector<pair<int,int>> info;
bool cmp(pair<int,int>&a, pair<int,int>&b) {
    if (a.first == b.first) return (a.second < b.second);
    return (a.first < b.first);
}
int main() {
    cin>>n;
    info.resize(n);
    for (int i=0; i<n; i++){
        cin>>info[i].first;
        cin>>info[i].second;
    } 
    //sort(info.begin(), info.end(), cmp);
    vector<vector<int>> bags;
    bags.resize(n+1);
    //for (auto i:info) cout<<i.first<<" "<<i.second<<endl;
    int i = info.size()-1;
    int count = 1;
    bags[count].push_back(i);
    //int limit = info[0].second;
    while (i>0) {
        //push i to count bags
        if (info[i].second >= info[i-1].second) {
            count++;
        } else {
            info[i-1].second = info[i].second;
        }
        i--;
        bags[count].push_back(i);
    }
    vector<int> bag_size;
    for (int i=1; i<= count; i++) bag_size.push_back(bags[i].size());
    sort(bag_size.begin(), bag_size.end());
    cout<<count<<" "<<bag_size[bag_size.size()-1]<<" "<<bag_size[0]<<endl;
    return 0;
}

#include<bits/stdc++.h>

using namespace std;

bool myfunction (vector<int> i,vector<int> j) { return (i[0]<j[0]); }
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n;
    cin>>n;
    vector<vector<int>>p(n,vector<int>(2));
    for(int i=0; i<n; i++) {
        cin>>p[i][0]>>p[i][1];
    }
    //sort (p.begin(), p.end(), myfunction);
    int cur_v = p[n-1][1];
    int grp = 1;
    int max_grp, min_grp,count;
    max_grp = 1;
    min_grp = INT_MAX;
    count =1;
    for(int i= n-2; i>=0;i--) {
        if (p[i][1] <= cur_v){
            grp++;
            if(count>max_grp){
                max_grp = count;
            }
            if(count<min_grp){
                min_grp = count;
            }
            count=1;
            cur_v = p[i][1];
        }else{
            count++;
        }
    }
    if(count>max_grp){
        max_grp = count;
    }
    if(count<min_grp){
        min_grp = count;
    }
    cout<<grp<<" "<<max_grp<<" "<<min_grp<<endl;
    return 0;
}

//https://www.hackerrank.com/contests/spct2024batch-2-pretest-2/challenges/minimum-initial-money-to-buy-all-houses
#include <bits/stdc++.h>
using namespace std;

int n;
vector<pair<int,int>> price;
bool cmp(pair<int,int>&a, pair<int,int>&b) {
    //if (a.second -  == b.second) return (a.first < b.first);
    return ((a.second - a.first) > (b.second-b.first));
}
int main() {
    cin>>n;
    price.resize(n);
    for (int i=0; i<n;i++) {
        cin>>price[i].first;
        //cin>>price[i].second;
    };
    for (int i=0; i<n;i++) {
        //cin>>price[i].first;
        cin>>price[i].second;
    };
    sort(price.begin(),price.end(),cmp);
    //for (auto i:price) cout<<i.first<<" "<<i.second<<endl;
    int rest = 0;
    int i = 0;
    int need = rest;
    while (i<n){
        //ans -= price[i-1].first;
        
        if (rest < price[i].second) {
            need += price[i].second - rest;
            rest = price[i].second;
        } else {
            
        }
        rest -= price[i].first;
        //cout<<"Buy "<<(i)<<" need "<<need<<" rest "<<rest<<endl;
        i++;
    }
    cout<<need;
    return 0;
}
// https://www.hackerrank.com/contests/spct2024batch-2-pretest-2/challenges/two-pluses-1
#include <bits/stdc++.h>
using namespace std;
int n,m;
vector<vector<char>> mt;
vector<pair<int,int>> point;
vector<pair<int,int>> list_p;
int max_area = 0;
#define area(a) (a*4+1)
int leng(int x,int y){
    int c = 1;
    while (true){
        if((c>x)||(c>y)||((c+x) == n)||((c+y)==m)) {
            c--;
            break;
        };
        if((mt[x+c][y]!='P')||(mt[x-c][y]!='P')||(mt[x][y-c]!='P')||(mt[x][y+c]!='P')){
            c--;
            break;
        }
        c++;
    }
    return c;
}

void calculate(int idx1, int l1, int idx2, int l2){
    int x1 = point[idx1].first;
    int y1 = point[idx1].second;
    int x2 = point[idx2].first;
    int y2 = point[idx2].second;
    //max_area = max(max_area,1);
    for(int d1=l1; d1>=0; d1--){
        for (int d2=l2;d2>=0; d2--){
            if ((x1==x2)&&(abs(y1-y2)<=(d1+d2))) continue; // overlap same row
            if ((y1==y2)&&(abs(x1-x2)<=(d1+d2))) continue; // overlap same column
            int xa1=x1-d1;
            int xa2=x2-d2;
            int xb1=x1+d1;
            int xb2=x2+d2;
            int ya1=y1-d1;
            int ya2=y2-d2;
            int yb1=y1+d1;
            int yb2=y2+d2;
            if (((((x1-xa2)*(x1-xb2)) <= 0)&&(((y2-ya1)*(y2-yb1))<=0))
               || ((((x2-xa1)*(x2-xb1)) <= 0)&&(((y1-ya2)*(y1-yb2))<=0))) continue;
            int tmp_area = area(d1)*area(d2);
            if (max_area < tmp_area) {
                //cout<<"Update "<<x1<<" "<<y1<<" "<<d1<<";"<<x2<<" "<<y2<<" "<<d2<<endl;
                max_area = tmp_area;
            }
            break;
        }
    }
};
int main() {
    cin>>n>>m;
    mt.resize(n, vector<char>(m));
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++) {
            cin>>mt[i][j];
            if(mt[i][j] == 'P') point.push_back({i,j});
        };
    for(int i=0; i<point.size(); i++) {
        int d = leng(point[i].first, point[i].second);
        list_p.push_back({d,i});
    }
    sort(list_p.begin(), list_p.end(), greater<>());
    for(int i=0; i<list_p.size(); i++){
        int l1 = list_p[i].first;
        int idx1 = list_p[i].second;
        //cout<<point[idx1].first<<" "<<point[idx1].second<<" "<<list_p[i].first<<endl;
        for(int j=i+1; j<list_p.size(); j++){
            int l2 = list_p[j].first;
            int idx2 = list_p[j].second;
            calculate(idx1,l1, idx2,l2);
        }
    }
    cout<<max_area;
    return 0;
}

