// STL includes
#include <iostream>
#include <vector>

using namespace std;

// Calculate partial sums in one iteration
// E = # of Si that are even
// O = # of Si that are odd
// Result = comb E 2 + comb O 2  + E
// O(n)
void testcase() {
    int n; cin >> n;
    vector<int> v;
    vector<int> sums;
    int sum = 0;
    int even = 0;
    for (int i = 0; i < n; i++) {
        int el; cin >> el;
        v.push_back(el);
        sum += el;
        sums.push_back(el);
        if (sum % 2 == 0) {
            even += 1;
        } 
    }

    int odd = sums.size() - even;
    cout << even + (even - 1) * even / 2 + odd * (odd - 1) / 2  << "\n"; 
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) {
        testcase();
    }

    return 0;
}
