#include <iostream>
#include <vector>

using namespace std;

// DP[l1][l2] = energia minimala de la l1 la l2
// DP[a][a] = 0; // no energy needed to cut one elem

void testcase() {
    int n; cin >> n;
    vector<int> v(n);
    vector<int> s(n);

    int sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        sum += v[i];
        s[i] = sum;
    }
    // s[a] contine v[a]

    vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
    for (int i = 0; i < n; i++) {
        dp[i][i] = 0;
    }

    // DP[a][b] 
    for (int l = 1; l < n; l++) {
        for (int a = 0; a < n - l ; a++) {
            int b = a + l;
            cout << "Sunt la intervalul " << a << " cu " << b << "\n";
            for (int c = a; c < b; c++) {
                cout << "Sum from a to b is " << s[b] - s[a] << "\n";
                dp[a][b] = min(dp[a][b], dp[a][c] + dp[c + 1][b] + s[b] - s[a] + v[a]);
                cout << "c " << c << "\n";
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << dp[i][j] << " ";
        }
        cout << "\n";
    }

    cout << dp[0][n-1] << "\n";
}

int main () {
    int t; cin >> t;
    while (t--) {
        testcase();
    }
}