#include<algorithm>
#include<iostream>
#include<bits/stdc++.h>

using namespace std;

// Metoda care ofera reprezentantul lui x.
// t - vectorul de parinti
// initial t[i] = i pentru orice i
// i face parte din componenta cu indicele i
// unirea lui i cu j : t[i] = j => tatal lui i este j
// UNION: t[q[i]] = q[j] (tatal reprezentantului lui i va deveni tatal reprezentantului lui j)
// => se unesc doi arbori 
// se unesc cand q[i] != q[j]
// Nu se returneaza R imediat, ci se face si compresia drumurilor 
// Cu compresie => O(logN), without O(N)
int q(vector<int>& t, int x) {
    int R, y;
    for (R=x;R!=t[R];R=t[R]);
    for (;x!=R;y=t[x],t[x]=R,x=y);
    return R;
}

int main() {
    vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8};
    vector<pair<int, int>> to_unify;
    to_unify.push_back(make_pair(0, 2));
    to_unify.push_back(make_pair(3, 2));
    to_unify.push_back(make_pair(5, 4));
    to_unify.push_back(make_pair(4, 2));
    to_unify.push_back(make_pair(8, 7));

    // Initialize parents t
    vector<int> t;
    for (int i = 0; i < v.size(); i++) {
        t.push_back(v[i]);
    }

    // Make union queries
    for (int i = 0; i < to_unify.size(); i++) {
        int a = to_unify[i].first;
        int b = to_unify[i].second;
        auto pa = q(t, a);
        auto pb = q(t, b);
        if (pa != pb) {
            t[pa] = pb;
        }
    }

    for (int i = 0; i < v.size(); i++) {
        cout << "Elementul " << v[i] << " este in componenta " << t[q(t, i)] << "\n";
    }

}