#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

bool ff(pair<int, int>& a, pair<int, int>& b) {
    return abs(a.first - a.second) > abs(b.first - b.second);
}

bool fff(pair<int, int>& a, pair<int, int>& b) {
    return  a.first < b.first;
}


int f(vector<int>& v, int target, int mm) {
    vector<int> sums;

    int sum = 0;
    for (int i = 0; i < v.size(); i++) {
        sum += v[i];
        sums.push_back(sum);
    }

    map<int, int> m;
    m[0] = -1;
    vector<pair<int, int> > sols;
    int max_difference = 0;
    for (int i = 0; i < sums.size(); i++) {
        int eu = sums[i];
        int needed = eu - target;
        //cout << "Needed " << needed << " eu " << eu << " target " << target << "\n";
        if (m.find(needed) != m.end()) {
            //cout << m[needed] + 1 << " and " << i << "\n";
            sols.push_back(make_pair(m[needed] + 1, i));
           // max_difference = max(max_difference, i - (m[needed+1] + 1) + 1);

           int help = i - (m[needed] + 1) + 1;
           max_difference = max(max_difference, help);
        }
        m[eu] = i;
    }

    if (1 == mm) {
        return max_difference;
    }

    //sort(sols.begin(), sols.end(), fff);

    int n = v.size();
    vector<int> d(n, 0);
    for (int i = 0; i < sols.size(); i++) {
        int a = sols[i].first;
        int b = sols[i].second;
        d[a] = max(d[a], b - a + 1);
    }
    /*for (int i = 0; i < n; i++) {
        cout << d[i] << " ";
    }
    cout << "\n";*/

    vector<int> d_prim(n, 0);
    int maxxx = 0;
    for (int i = n - 2; i >= 0; i--) {
        d_prim[i] = max(maxxx, d[i+1]);
        maxxx = max(maxxx, d_prim[i]);
    }
    /*for (int i = 0; i < n; i++){
        cout << d_prim[i] << " ";
    }
    cout << "\n";*/

    int max_length = -1;
    for (int i = 0; i < sols.size(); i++) {
        int a = sols[i].first;
        int b = sols[i].second;
        int diff = b - a + 1;
        //cout << "a " << a << " b " << b << "\n";
        //cout << "diff " << diff << "\n";
        int length_second_max = d_prim[b];
        //cout << "length " << length_second_max << "\n";
        if (length_second_max != 0)
            max_length = max(max_length, diff + length_second_max);
        //cout << "MAX LENGTH " << max_length << "\n";
    }

    return max_length;


}

void testcase() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> v;
    for (int i = 0; i < n; i++) {
        int el; cin >> el;
        v.push_back(el);
    }

    int sol = f(v, k, m);
    if (sol == -1) {
        cout << "fail\n";
    } else {
        cout << sol << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);

    int t; cin >> t;
    while (t--) {
        testcase();
    }
}