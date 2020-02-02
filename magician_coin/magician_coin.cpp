#include <iostream>
#include <bits/stdc++.h>

using namespace std;

vector<vector<double>> dp;

double best(int i, int c, int n, int m, vector<double>& p) {

    if (i >= n) {
        if (c >= m) {
            return 1;
        } else {
            return 0;
        }
    }

    if (c >= m) {
        return 1;
    }

    if (dp[i][c] != -1) {
        return dp[i][c];
    }

    double ans = 0;

    for (int b = 0; b <= c; b++) {
        double win  = best(i+1, c + b, n, m, p);
        double lose = best(i+1, c - b, n, m, p);
        ans = max(ans, win * p[i] + lose * (1-p[i]));
    }

    dp[i][c] = ans;
    return ans;
}


void testcase() {
    int n, k, m;
    cin >> n >> k >> m;

    vector<double> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

    dp = vector<vector<double>>(n+1, vector<double>(m, -1));

    cout.precision(5);
    cout << fixed << best(0, k, n, m, p) << '\n';

}

int main () {
    ios_base::sync_with_stdio(false);

    int t; cin >> t;
    while (t--) {
        testcase();
    }
}

/*


la momentul t
d[t][c] = probabilitatea de a castiga avand 
c credite la momentul t

a castiga == a avea cel putin m la final


d[n+1][m] = 1

0 <= bet <= c
d[t][c] = max {bet} ( d[t+1][c - bet] * (1 - p[t]) + d[t+1][c + bet] * p[t] )

d[1][k]

*/