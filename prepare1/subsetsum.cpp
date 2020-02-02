#include <iostream>
#include <vector>

using namespace std;

vector<int> elements;
int n;

void subsetsum(int k) {
    for (int s = 0; s < 1<<n; ++s) { // Iterate through all subsets
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            if (s & 1<<i) {
                sum += elements[i]; // If i-th element in subset
            }
        }
        if (sum == k) {
            for (int i = 0; i < n; ++i) {
                if (s & 1<<i) {
                    cout << elements[i] << " ";
                }
            }
            cout << "\n";
        }
    }
}

int main() {
    elements.push_back(1);
    elements.push_back(4);
    elements.push_back(7);
    elements.push_back(-2);
    elements.push_back(2);
    elements.push_back(2);
    n = elements.size();

    subsetsum(5);

}