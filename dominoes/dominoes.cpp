// STL includes
#include <iostream>
#include <vector>

using namespace std;


void testcase() {
    int n; cin >> n;
    vector<int> heights;
    vector<int> visited;
    for (int i = 0; i < n; i++) {
        int el; cin >> el;
        heights.push_back(el);
        visited.push_back(0);
    }

    int count = 0;

    visited[0] = 1;
    int j = 1; // The first one is visited.
    for (int i = 0; i < n; i++) {
        if (visited[i] == 1) {
            while (j < i + heights[i] && j < n) {
                visited[j] = 1;
                j += 1;
            }
        }
    }

    for (int i = 0; i < visited.size(); i++) {
        if (visited[i] == 1) {
            count++;
        }
    }
    cout << count << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) {
        testcase();
    }

    return 0;
}
