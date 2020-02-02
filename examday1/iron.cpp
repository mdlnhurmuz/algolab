#include <iostream>
#include <bits/stdc++.h>

using namespace std;

// Get the maximum number of integers that sum up to K.
int get_max_islands(vector<int>& v, int k) {
    vector<int> sums;

    int sum = 0;
    for (int i = 0; i < v.size(); i++) {
        sum += v[i];
        sums.push_back(sum);
    }

    map<int, int> m; // sum to position
    m[0] = -1;
    int max_islands = -1;
    for (int i = 0; i < sums.size(); i++) {
        int eu = sums[i];
        int cevadinainte = eu - k;
        if (m.find(cevadinainte) != m.end()) {
            int pos = m[cevadinainte];
            max_islands = max(max_islands, i - pos);
            //cout << "i si pos "  << i << " : " << pos << "\n";
        }
        m[eu] = i;
    }

    return max_islands;
}

void testcase() {
    int n, k, b;
    cin >> n >> k >> b;

    vector<int> v;
    vector<vector<int>> paths(b, vector<int>());
    vector<int> men;

    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        men.push_back(a);
        cout << "adaug pt men " << men[i] << "\n";
    }

    for (int i = 0; i < b; i++) {
        int l; cin >> l;
        for (int j = 0; j < l; j++) {
            int el; cin >> el;
            paths[i].push_back(el);
        }
    }

     for (int i = 0; i < b; i++) {
        for (int j = 0; j < paths[i].size(); j++) {
            cout << paths[i][j] << "\n";
        }
    }

    if (b == 2) {
        for (int i = paths[1].size() - 1; i > 0; i--) {
            v.push_back(men[paths[1][i]]);
        }
        for (int i = 0; i < paths[0].size(); i++) {
            v.push_back(men[paths[0][i]]);
        }
        for (int i = 0; i < v.size(); i++) {
            cout << v[i] << " ";
        }
        cout << "\n";

        cout << get_max_islands(v, k) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;

    while (t--) {
        testcase();
    }
}