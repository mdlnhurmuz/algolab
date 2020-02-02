#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int q(vector<int>& t, int x) {
    int R = x;
    while (R != t[R]) {
        R = t[R];
    }

    int aux = x;
    while (t[x] != R) {
        aux = t[x];
        t[x] = R;
        x = aux;
    }

    return R;
}


void testcase() {
    int n, i;
    cin >> n >> i;

    vector<pair<int, pair<int, int>>> channels;
    for (int j = 1; j <= n-1; j++) {
        for (int k = 1; k <= n - j; k++) {
            int el; cin >> el;
            channels.push_back({el, {j, j + k}});
        }
    }
    sort(channels.begin(), channels.end());

    vector<int> t(n +1);
    for (int i = 1; i <= n; i++) {
        t[i] = i;
    }


    vector<vector<pair<int, int>>> graph(n+1);
    vector<pair<int, pair<int, int>>> not_used;

    int cost = 0;
    for (int i = 0; i < channels.size(); i++) {
        int dist = channels[i].first;
        int a = channels[i].second.first;
        int b = channels[i].second.second;

        int qa = q(t, a);
        int qb = q(t, b);

        if (qa != qb) {
            t[qa] = qb;
            //cout << a << " : " << b << "\n";
            cost += dist;

            graph[a].push_back(make_pair(b, dist));
            graph[b].push_back(make_pair(a, dist));

        } else {
            not_used.push_back(channels[i]);
        }
    }
    //cout << "cost " << cost << "\n";
    
    vector<vector<int>> sol(n+1, vector<int>(n+1, 0));


    for (int i = 1; i <= n; i++) {
        queue<int> q;
        vector<bool> visited(n, false);
        q.push(i);
        visited[i] = true;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (auto it : graph[x]) {
                if (!visited[it.first]) {
                    visited[it.first] = true;
                    q.push(it.first);
                    sol[i][it.first] = max(sol[i][x], it.second);
                }
            }
        }
    }

    /*for (int i = 1; i <= n; i++) {
        for (int j = 1; j <=n; j++) {
            cout << sol[i][j] << " ";
        }
        cout << "\n";
    }*/

    int sol_min_second_cost = INT_MAX;
    for (int i = 0; i < not_used.size(); i++) {
        int dist = not_used[i].first;
        int a = not_used[i].second.first;
        int b = not_used[i].second.second;

        int between = sol[a][b];
        int possible_sol = cost - between + dist;
        if (possible_sol < sol_min_second_cost) {
            sol_min_second_cost = possible_sol;
        }
    }

    cout << sol_min_second_cost << "\n";


    


}


int main() {
    ios::sync_with_stdio(false);

    int t; cin >> t;
    while (t--) {
        testcase();
    }
}