#include <iostream>
#include <vector>

// Union: t[q[i]] = q[j]

using namespace std;

int q(vector<int>&t, int x) {
    int R = x;
    while (R != t[R]) {
        R = t[R];
    }

    int aux;
    // Leg toti stramosii direct la reprezentant.
    while (x != R) { 
        aux = t[x];
        t[x] = R;
        x = aux;
    }

    return R;
}

bool f(pair<pair<int, int>, int>& a, pair<pair<int, int>, int>& b) {
    return a.second < b.second;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<pair<pair<int, int>, int>> g(m);

    for (int i = 0; i < m; i++) {
        int x, y, z; cin >> x >> y >> z;
        g[i] = {{x, y}, z};
    }

    sort(g.begin(), g.end(), f);

    for (int i = 0; i < m; i++) {
        cout << "De la  " << g[i].first.first << " la " << g[i].first.second << " cu cost " << g[i].second << "\n";
    }

    vector<int> t(n);
    for (int i = 0; i < n; i++) {
        t[i] = i;
    }

    int cost = 0;
    
    vector<int> a(n); // number of nodes in component a[i]
    for (int i = 0; i < n; i++) {
        a[i] = 1;
    }

    int maxai = 1;
    for (int i = 0; i < m; i++) {
        int x = g[i].first.first;
        int y = g[i].first.second;
        int c = g[i].second;

        if (q(t, x) != q(t, y)) {
            a[q(t, y)] += a[q(t, x)];
            t[q(t, x)] = q(t, y);
            cost += c;

            if (a[q(t, y)] > maxai) {
                maxai = a[q(t, y)];
            }
        }

        cout << "La momentul i " << i << " avem o componenta cu max " << maxai << "\n"; 


    }

    for (int i = 0; i < t.size(); i++) {
        cout << q(t, i) << " \n"; 
    }
    cout << "Cost " << cost << "\n";


}
