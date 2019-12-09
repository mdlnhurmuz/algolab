#include <iostream>
#include <iomanip>
#include <bits/stdc++.h>
using namespace std;

void testcase() {
    int n; int w; // N - number of coins, W - amount to form with the coins
    vector<int> coins;

    cin >> n; cin >> w;
    for (int i = 0 ; i < n; i++) {
        int el; cin >> el;
        coins.push_back(el);
    }

    vector<vector<int>> dp(n + 1, vector<int>(w + 1));

    for (int i = 0; i < n + 1; i++) {
        dp[i][0] = 0;
    }

    for (int j = 0; j < w + 1; j++) {
        dp[0][j] = j;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < w + 1; j++) {
            if (coins[i-1] > j) {
                dp[i][j] = dp[i-1][j];
            } else {
                dp[i][j] = min(dp[i-1][j], 1 + dp[i][j - coins[i-1]]);
            }
        }
    }


    cout << "Final answer " << dp[n][w] << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false); // Always.

    int t; std::cin >> t; // Read the number of testcases.
    for (int i = 0; i < t; ++i) {
        testcase();
    }
}