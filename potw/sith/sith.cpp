#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

int q(vector<int>& t, int x) {
    int R = x;
    while (R != t[R]) {
        R = t[R];
    }

    int aux;
    while (x != R) {
        aux = t[x];
        t[x] = R;
        x = aux;
    }

    return R;
}


void testcase() {
    int n;
    long long r;

    cin >> n >> r;

    vector<pair<int, int>> v;


    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        v.push_back({a, b});
    }
    
    vector<int> parents;
    int count = n;
    for (int i = 0; i < count; i++) {
        parents.push_back(i);
    }

    vector<int> sizes;
    for (int i = 0; i < count; i++) {
        sizes.push_back(1);
    }

    for (int i = n-1; i >= 0; i--) {
        for (int j = i+1; j < v.size(); j++) {
            int a = v[i].first;
            int b = v[i].second;

            int c = v[j].first;
            int d = v[j].second;

            long long dist = pow(c -a, 2) + pow(d - b, 2);
            if (dist <= r * r) {
                int qa = q(parents, i);
                int qb = q(parents, j);

                if (qa != qb) {
                        //cout << "Unesc " << x << " cu " << y << "\n";
                        int keep = sizes[qb];
                        parents[qb] = qa;
                        sizes[qa] += keep;
                        //cout << "k dupa unire este " << k << "\n";
                    
                }
            }
        }

        int mx = 0;
        for (int j = i; j < n; j++) {
            mx = max(mx, sizes[q(parents, i)]);
        }
        if (i <= mx) {
            cout << i << "\n";
            break;
        }
    }

}


int main () {
    ios_base::sync_with_stdio(false);

    int t; cin >> t;
    while (t--) {
        testcase();
    }
}