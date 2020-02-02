#include <iostream>
#include <vector>

using namespace std;

int n = 3;
int m = 2;
vector<int> v;

void dostuff(vector<int>& v) {
    for (auto it : v) {
        cout << it << " ";
    }
    cout << "\n";
}

void back(int i) {
    if (i > n) {
        dostuff(v);
        return;
    }
    for (int j = 0; j <= m -1; j++) {
        v.push_back(j);
        back(i + 1);
        v.pop_back();
    }
}

int main() {
    back(1);
}