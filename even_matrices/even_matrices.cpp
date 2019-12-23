#include <iostream>
#include <iomanip>
#include <bits/stdc++.h>
using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false); // Always.

    int t; std::cin >> t; // Read the number of testcases.
    int **mat;
    int **sum;
    int n, el;
    int final_sol;

    while (t--) {
        std::cin >> n;
        final_sol = 0;
        mat = new int*[n + 1];
        sum = new int*[n + 1];
        for (int i = 0 ; i <= n; i++) {
            mat[i] = new int[n + 1];
            sum[i] = new int[n + 1];
        }

        for (int i = 1; i <= n ; i++) {
            for (int j = 1; j <= n; j++) {
                std::cin >> el;
                mat[i][j] = el;
            }
        }

        for (int i = 1; i <=n; i++) {
            for (int j = 1; j <= n; j++) {
                sum[i][j] = sum[i-1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + mat[i][j];
            }
        }

       for (int i = 1; i <= n; i++) {
           for (int j = i; j <= n; j++) {
               std::vector<int> vect;
               for (int k = 1; k <= n; k++) {
                   int curr = sum[k][j] - sum[k][i - 1] - sum[k - 1][j] + sum[k - 1][i - 1];
                   vect.push_back(curr);
               }

                std::vector<int> sums;
                sums.push_back(0);
                int e = 0, o = 0, sol = 0;
                for (int i = 0; i < vect.size(); i++) {
                    sums.push_back(sums[i] + vect[i]);

                    if (sums[i + 1] % 2 == 0)
                        sol += e + 1;
                    else
                        sol += o;

                    if (sums[i + 1] % 2 == 0) e += 1;
                    else o += 1;
                }
                final_sol += sol;
           }
       }

    std::cout << final_sol << "\n";



    }
}