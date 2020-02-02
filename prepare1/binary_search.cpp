#include <iostream>
#include <vector>

using namespace std;

int binary_search(vector<int>& v, int l, int r, int target) {
    while (l <= r) {
        int m = l + (r- l)/ 2;

        if (v[m] == target) {
            return m;
        } else if (v[m] < target) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return -1;
}

int main() {
    vector<int> v;
    v.push_back(-1);
    v.push_back(2);
    v.push_back(4);
    v.push_back(8);

    int target = 4;
    cout << "Found target at " << binary_search(v, 0, v.size()- 1, target) << "\n";
}