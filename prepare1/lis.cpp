#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;


// Length of the LIS
int main () {
    vector<int> a;
    a.push_back(2);
    a.push_back(1);
    a.push_back(5);
    a.push_back(9);
    a.push_back(6);
    a.push_back(4);
    // 2 1 5 9 6 4 

    multiset<int> s;
    multiset<int>::iterator it;

    for (int i = 0; i < a.size(); i++) {
        s.insert(a[i]);
        cout << "Inserez a[i] " << a[i] << "\n";

        cout << "Multisetul meu este acum: ";
        for (auto it : s) {
            cout << it << " ";
        }
        cout << "\n";

        it = s.upper_bound(a[i]); // an iterator pointing to the immediate next element which is greater than a[i]
        if (it != s.end()) {
            cout << "It este " << *it << "\n";
            s.erase(it);
            cout << "Sterg it " << *it << "\n";
        }
    }

    for (auto it : s) {
        cout << it << " ";
    }
    cout << "\n";
}