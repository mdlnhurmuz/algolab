#include <iostream>
#include <bits/stdc++.h>

using namespace std;

bool backtrack(vector<int>& elements, int i, int k) {
    for (int s = 0; s < 1<<elements.size(); ++s) {
        long sum = 0;
        for (int j = 0; j < elements.size(); j++) {
            if (s & 1 <<j) {
                sum += elements[j];
            }
        }
        if (sum % k == i % k && sum != 0) return true;
    }
    return false;
}

void backtrack2(vector<int>& elements, set<long>& subset_sums) {
    for (int s = 0; s < 1<<elements.size(); ++s) {
        long sum = 0;
        for (int j = 0; j < elements.size(); j++) {
            if (s & 1 <<j) {
                sum += elements[j];
            }
        }
        subset_sums.insert(sum);
    }
}

void testcase() {
    int n, i, k;
    cin >> n >> i >> k;

    vector<int> elements;
    for (int i = 0; i < n; i++) {
        int el;
        cin >> el;
        elements.push_back(el);
    }


    set<int> s1;
    set<int> s2;
    for (int i = 0; i < elements.size(); i++) {
        if (i <= n/2) { 
            s1.insert(elements[i]);
        } else {
            s2.insert(elements[i]);
        }
    }

    vector<int> sl1;
    for (auto it : s1) {
        sl1.push_back(it);
    }
    vector<int> sl2;
    for (auto it : s2) {
        sl2.push_back(it);
    }


    set<long> l1;
    set<long> l2;

    backtrack2(sl1, l1);
    backtrack2(sl2, l2);

    int ii = i;

    set<long> l2_modulo_k;
    map<int, vector<long>> map_modulo_to_k2;
    for (auto it : l2) {
        l2_modulo_k.insert(it%k);
        map_modulo_to_k2[it%k].push_back(it);
    }

    long target = ii % k;

    for (auto it : l1) {
        long k1 = it % k;
        int caut = (7*k + target - k1) % k;

        vector<long>& k2s = map_modulo_to_k2[caut];
        bool good = true;
        for (auto k2 : k2s) {
            if (l2_modulo_k.find(caut) != l2_modulo_k.end() && (it+k2 != 0) && (k1 + k2)%k == target)  {
                cout << "yes\n";
                return;
            }
        }
    }
    cout << "no\n";
}




int main() {
    ios_base::sync_with_stdio(false);

    int t; cin >> t;
    while (t--) {
        testcase();
    }

}