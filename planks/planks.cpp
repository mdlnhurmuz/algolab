// STL includes
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function a combination of given elements such that its sum is K.
void combination(int l, long sum, long K, vector<int>&local, vector<int>& A, bool& found) {
    // If a combination is found
    if (sum == K) {
        found = true;
        return ; // DO NOT FORGET
    }

    // For all other combinations
    for (int i = l; i <(int) A.size(); i++) {
        if (sum + A[i] > K) continue;

        // Take element into the combination
        local.push_back(A[i]);

        // Recursive call
        combination(i + 1, sum + A[i], K, local, A, found);

        if (found) {
            return; // DO NOT FORGET. IF WE FOUND SOMETHING, JUST RETURN FROM EVERY OTHER POSSIBILITY.
        }

        // Remove element from the combination
        local.pop_back();
    }
}


void testcase() {
    int n;
    cin >> n;

    vector<int> v;
    int sum = 0;

    for (int i = 0; i < n; i++) {
        int el; cin >> el;
        v.push_back(el);
        sum += el;
    }

    if (sum % 4 == 1) {
        cout << "0\n";
        return;
    }

    long sum4 = sum/4;

    int times = 4;
    while (times--) {
        // To store combination
        vector<int> local;
        long sum_achieved = 0;
        bool found = false;
        combination(0, sum_achieved, sum4, local, v, found);

        for (int i = 0; i < local.size(); i++) {
            auto it = std::find(v.begin(), v.end(), local[i]);
            if (it != v.end())
                v.erase(it);
            else {
                //cout << "What";
            }
        }
    }
    
    if (v.size() == 0) {
        cout << "1\n";
    } else {
        cout << "0\n";
    }

}


int main() {
    std::ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) {
        testcase();
    }

    return 0;
}
