// STL includes
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool myfunc(pair<int,int>& a, pair<int, int>&b ) {
    return a.second < b.second;
}

void testcase() {
    int n; cin >> n;
    vector<pair<int, int>> v;
    for (int i = 0; i < n; i++) {
        int l, p; cin >> l >> p;
        v.push_back(make_pair(l, p));
    }

    sort(v.begin(), v.end(), myfunc);

    int last_prev = -INT_MAX;
    int last = v[0].second;

    int boats = 1;

    for (int i = 1; i < v.size(); i++) {
        int curr_last = max(last + v[i].first, v[i].second);
        int curr_last_prev = max(last_prev + v[i].first, v[i].second);

        // Capatul de la iteratia anterioara <= positia ultimului element 
        if (last <= v[i].second) {
            last_prev = last;
            last = curr_last;
            boats++;
        } else {
            last_prev = min(last, last_prev);
            last = min(last, curr_last_prev);
        }
    } 

    cout << boats << "\n";
}


int main() {
    std::ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) {
        testcase();
    }

    return 0;
}
