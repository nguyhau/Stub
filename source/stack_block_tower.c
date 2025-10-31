#include <bits/stdc++.h>

using namespace std;

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
        /* calculate current number of 'A' and 'B' */
        // if (s[i] == 'A') {
        //     number_of_firsts++;
        // } else if (s[i] == 'B') {
        //     number_of_seconds++;
        // }

        /* ignore if number of 'A' is not the same as number of 'B' */
        // if (number_of_firsts != number_of_seconds) {
        //     continue;
        // }
        if (temp.size() == numb_alpha) {
            int n = al_count[temp[0]];
            bool next = false;
            for(int j=1; j< temp.size(); j++) {
                if (al_count[temp[j]] != n) {
                    next = true;
                    break;
                }
                //cout<<" "<< temp[j]<<" "<<al_count[temp[j]];
            }
            if (next) continue;
            else {
                // for(int j=0; j< temp.size(); j++) {
                //     cout<<" "<< temp[j]<<" "<<al_count[temp[j]];
                // }
                // cout<<std::endl;
                temp.clear();
                al_count.clear();
                result++;
                //result = max(result, 1 + find_maximum_towers(i + 1));
            }
        }       
        
    }

    return result;
}

int main(int argc, char **argv)
{
    cin >> s;
    //s = "ABAABBABAB";

    cout << find_maximum_towers(0) << endl;

    return 0;
}