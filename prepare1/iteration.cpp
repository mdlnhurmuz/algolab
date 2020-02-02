#include <iostream>
#include <vector>

using namespace std;

// m^n 

int n = 3;
int m = 2;
vector<int> v;

// For example for m = 2, n = 3, it outputs:
// 0 0 0
// 0 0 1
// 0 1 0
// 0 1 1
// 1 0 0
// 1 0 1
// 1 1 0
// 1 1 1

void dostuff(vector<int>& p) {
    for (auto it : p) {
        cout << it << " ";
    }
    cout << "\n";
}

void back(int i) {
   if (i > n) {
       dostuff(v);
       return;
   }
   for (int j = 0; j <= m - 1; j++) {
       v.push_back(j);
       back(i + 1);
       v.pop_back();
   }
}


int main() {
    back(1);
}