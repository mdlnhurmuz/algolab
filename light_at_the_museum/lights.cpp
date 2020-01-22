#include <bits/stdc++.h>
#include <iostream>

using namespace std;

void testcase() {
    int n, m; cin >> n >> m;

    if (m == 1) {
        int mij = n/2;

        int target; cin >> target;

        vector<int> a(n), b(n);

        for (int i = 0; i < n; i++) {
            int x, y; cin >> x >> y;
            a[i] = x;
            b[i] = y;
        }

        map<int, int> mapp;

        for (int e = 0; e < (1 << mij); e++) {
            int zeroes = 0;
            int sum = 0;
            for (int k = 0; k < mij; k++) {
                if (e & (1 << k)) {
                    // k
                    //cout << 1 << ' ';
                    sum += b[k];
                } else {
                    //cout << 0 << ' ';
                    zeroes++;
                    sum += a[k];
                }
            }
            //cout << '\n';
            mapp[sum] = max(zeroes + 1, mapp[sum]);
            //cout << "Sum " << sum << " has " << zeroes  + 1 << "\n";
            
        }


        int sol = INT_MIN;
        for (int e = 0; e < (1 << (n - mij)); e++) {
            int value = 0;
            int zeroes = 0;
            for (int k = 0; k < (n - mij); k++) {
                if (e & (1 << k)) {
                    // mij + k 
                    //cout << 1 << ' ';
                    value += b[mij + k];
                } else {
                    //cout << 0 << ' ';
                    value += a[mij + k];
                    zeroes += 1;
                }
            }
            int needed = target - value;
            if (mapp[needed] != 0) {
                sol = max(sol, zeroes + (mapp[needed] - 1));
            }
            //cout << '\n';
            //cout << "Sum " << value << " has " << zeroes + 1 << "\n";
        }

        if (sol != INT_MIN) {
            cout << n - sol << "\n";
        } else {
            cout << "impossible\n";
        }





    }

}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--) {
        testcase();
    }
}