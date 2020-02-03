#include <iostream>
#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> dp;
 // dp[a][b] - smallest cost to load a objects of A and b objects of B
 // from bottom to top
 // answer dp[n][n]


void testcase() {
    int n; cin >> n;

    vector<int> a;
    vector<int> b; 

    for (int i = 0; i < n ; i++) {
        int el; cin >> el;
        a.push_back(el);
    }

    for (int i = 0; i < n ; i++) {
        int el; cin >> el;
        b.push_back(el);
    }
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    vector<int> sums_a;
    vector<int> sums_b;

    int sa = 0;
    for (int i = 0; i < a.size(); i++) {
        sa += a[i];
        sums_a.push_back(sa);
    }
    int sb = 0;
    for (int i = 0; i < b.size(); i++) {
        sb += b[i];
        sums_b.push_back(sb);
    }

    dp = vector<vector<int>>(n+1, vector<int>(n+1, 0x3f3f3f3f));
    dp[0][0] = 0;
    

    for (int na = 1; na <= n; na++) {
        for (int nb = 1; nb <= n; nb++) {
            for (int i = 0; i < na; i++) {
                for (int j = 0; j < nb; j++) {

                    int sum_a = sums_a[na-1] - sums_a[i] + a[i];
                    int sum_b = sums_b[nb-1] - sums_b[j] + b[j];
                    /*for (int k = i; k < na; k++) {
                        sum_a += a[k];
                    }
                    for (int k = j; k < nb; k++) {
                        sum_b += b[k];
                    }*/

                    int ka = na - i;
                    int kb = nb - j;
                    int sa = sum_a - ka;
                    int sb = sum_b - kb;

                    dp[na][nb] = min(dp[na][nb], sa * sb + dp[i][j]);
                }
            }
        }
    }

    /*for (int i = 0; i <=n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << dp[i][j] << " ";
        }
        cout << "\n";
    }*/
    cout << dp[n][n] << "\n";
    
}

int main () {
    int t; cin >> t;

    while (t--) {
        testcase();
    }
}