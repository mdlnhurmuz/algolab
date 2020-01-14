#include<algorithm>
#include<iostream>
#include<bits/stdc++.h>

using namespace std;

int main() {
    vector<int> v{ 1, 3, 5, 7, 8, 10, 20 };

    // Looking for the smallest number bigger than 9. => 10
    int K = 9;
    long long i = -1;
    long long step = (1LL << 60);
    while (step) {
        if (i + step < v.size() && v[i + step] < K) {
            i += step;
        }
        step >>= 1;
    }
    cout << v[i + 1] << "\n";

    // Looking for the biggest number smaller than 5. => 3
    K = 5;
    i = -1;
    step = (1LL << 60);
    while (step) {
        if (i + step < v.size() && v[i + step] < K) {
            i += step;
        }
        step >>= 1;
    }
    cout << v[i] << "\n";

    // Attention - Looking for the leftmost i with prop P <=> looking for 
    // rightmost i which does NOT have prop P := i => output i + 1

    vector<bool> tf{false, false, false, true, true, true, true};
    // Look for the rightmost i with prop P
    // Let's say rightmost false value position.
    i = -1;
    step = (1LL << 60);
    while (step) {
        if (i + step < tf.size() && tf[i + step] != true) {
            i += step;
        }
        step >>= 1;
    }
    cout << "Rightmost false position: " << i << "\n";

    // Look for the leftmost i with prop P
    // Let's say leftmost true value position.
    i = -1;
    step = (1LL << 60);
    while (step) {
        if (i + step < tf.size() && tf[i + step] != true) {
            i += step;
        }
        step >>= 1;
    }
    cout << "Leftmost true position: " << i + 1 << "\n";

}