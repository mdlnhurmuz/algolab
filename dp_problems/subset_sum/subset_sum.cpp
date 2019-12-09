#include <iostream>
#include <iomanip>
#include <bits/stdc++.h>
using namespace std;

void testcase() {
    int n; int w;
    vector<int> v;

    cin >> n; cin >> w;
    for (int i = 0; i < n; i++) {
        int el; cin >> el;
        v.push_back(el);
    }

    vector<vector<bool>> dp(n + 1, vector<bool>(w + 1, false));

    for (int i = 0; i < n + 1; i++) {
        dp[i][0] = true;
    }

    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < w + 1; j++) {
            if (v[i-1] > j) {
                dp[i][j] = dp[i-1][j];
            }
            else {
                dp[i][j] = dp[i-1][j] || dp[i - 1][j - v[i-1]];
            }
        }
    }

    auto res =  dp[n][w] == true ? "YES" : "NO";
    cout << "Could I sum up to " << w << " from the numbers given? " << res << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false); // Always.

    int t; std::cin >> t; // Read the number of testcases.
    for (int i = 0; i < t; ++i) {
        testcase();
    }
}