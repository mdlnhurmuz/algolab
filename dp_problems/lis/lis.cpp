#include <iostream>
#include <iomanip>
#include <bits/stdc++.h>
using namespace std;

void testcase() {
    int n;
    vector<int> v;
    vector<int> length_to_element; // Length = index + 1;

    cin >> n;
    for (int i = 0 ; i < n; i++) {
        int el; cin >> el;
        v.push_back(el);
    }

    length_to_element.push_back(v[0]);
    for (int i = 1 ; i < n; i++) {
        int current = v[i];

        // Search the greatest element smaller than the current element. Save its position. 
        int pos = 0;
        int pas = pow(2, 30);

        while (pas > 0) {
            if (pos + pas < length_to_element.size() && length_to_element[pos + pas] < current) {
                pos += pas;
            }
            pas /= 2;
        }

        if (pos == length_to_element.size() - 1) {
            if (current > length_to_element[length_to_element.size() - 1]) {
                length_to_element.push_back(current);
            }
        }
        if (length_to_element[pos + 1] > current) {
            length_to_element[pos + 1] = current;
        }
        
    }

    cout << "Result : ";
    for (int i = 0; i < length_to_element.size(); i++) {
        cout << length_to_element[i] << " ";
    }
    cout << endl;
}

int main() {
    std::ios_base::sync_with_stdio(false); // Always.

    int t; std::cin >> t; // Read the number of testcases.
    for (int i = 0; i < t; ++i) {
        testcase();
    }
}