#include <bits/stdc++.h>
using namespace std;
bool compare_vector(vector<int> a, vector<int> b)
{
    if (a[0] == b[0])return (a[1] > b[1]);
    return (a[0] > b[0]);
}
void multiset_struct() //auto sort
{
    multiset<vector<int>, bool (*)(vector<int>,vector<int>)> set_vector(&compare_vector);
    vector<int> v1 = {1,2,3};
    vector<int> v2 = {2,2,3};
    vector<int> v3 = {1,1,3};
    set_vector.insert(v1);
    set_vector.insert(v2);
    set_vector.insert(v3);
    for (auto i:set_vector) {
        for (auto j:i) cout<<j;
        cout<<endl;
    }
    cout<<"Change value of first element"<<endl;
    (*(set_vector.begin()))[0]++;
    for (auto i:set_vector) {
        for (auto j:i) cout<<j;
        cout<<endl;
    }
}
void vector_struct()
{
    vector<vector<int>> v_vector;
    vector<int> v1 = {1,2,3};
    vector<int> v2 = {2,2,3};
    vector<int> v3 = {1,1,3};
    vector<int> v4 = {1,2,2};
    v_vector.push_back(v1);
    v_vector.push_back(v2);
    v_vector.insert(v_vector.begin(),v3); //push_front
    for (auto i:v_vector) {
        for (auto j:i) cout<<j<<" ";
        cout<<endl;
    }
    cout<<"after sort"<<endl;
    sort(v_vector.begin(), v_vector.end(), compare_vector);
    for (auto i:v_vector) {
        for (auto j:i) cout<<j<<" ";
        cout<<endl;
    }
    // Reverse the vector
    cout<<"after reverse"<<endl;
    reverse(v_vector.begin(), v_vector.end());
    for (auto i:v_vector) {
        for (auto j:i) cout<<j<<" ";
        cout<<endl;
    }
   vector<vector<int>>::iterator idx = upper_bound(v_vector.begin(), v_vector.end(), v4, 
                                    [](vector<int> a, vector<int> b) {
                                        if (a[0] == b[0])return (a[1] > b[1]);
                                        return (a[0] > b[0]);
                                    });
   //cout<<*idx<<endl;
   for (auto j:*idx) cout<<j<<" ";
        cout<<endl;
}
void vector_set() {
    vector<vector<set<char>>> sodo;
    sodo.resize(9, vector<set<char>>(9, set<char>({'1','2','3','4','5','6','7','8','9'})));
    
    // set<char> u({'1','2','3'});
    // for (auto j:u) cout<<j<<" ";

    // //for (auto i:sodo) i.resize(9, set<char>({'1','2','3'}));
    // for (auto i:sodo) i.resize(9);
    // for (auto i:sodo){  
    //     for (auto j:i) j = u;
    // }
    // cout<<sodo.size();
    // cout<<sodo[0].size();
    for (auto k:sodo[8]){
        //cout<<k.size();
        for (auto j:k) cout<<j<<" ";
        cout<<endl;
    }
        
}
bool isValid(vector<vector<char>>& board, int row, int col, char c) {
    // check row
    for (int i=0; i<9; i++) {
        if ((i != row) && (board [i][col] == c)) return false;
    }
    // check colum
    for (int i=0; i<9; i++) {
        if ((i != col) && (board [row][i] == c)) return false;
    }
    // check 3*3
    int r_mov = row%3;
    int c_mov = col%3;        
    for (int i=(row-r_mov); i<(row-r_mov+3); i++) {
        for (int j=(col-c_mov); j<(col-c_mov+3); j++){
            if (((i != row)||(j!= col))&& (board[i][j] == c)) return false;                    
        }
    }
    return true;
}
bool solveBt(vector<vector<char>>& board) {
        for (int i=0; i<9; i++)
        for (int j=0; j<9; j++) {
            if (board[i][j] == '.') {
                for (auto k:{'1','2','3','4','5','6','7','8','9'})
                    {
                        board[i][j] = k;
                        if (isValid(board,i,j,k)) {
                        if (solveBt(board)) return true;
                        } ;
                    }
                    board[i][j] = '.';
                    return false;
            }
        }
    return true;
}
void solveSudoku(vector<vector<char>>& board) { 
    vector<vector<set<char>>> sodo;
    sodo.resize(9, vector<set<char>>(9, set<char>({'1','2','3','4','5','6','7','8','9'})));
    // sodo[i][k].clear();
    // sodo[i][k].erase(board[i][j]);
    solveBt(board);
}
int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    //vector_struct();
    //vector_set();
    multiset_struct();
    return 0;
}
