#include <iostream>
#include <bits/stdc++.h>

using namespace std;

vector<int> solution;

bool funct(int a, int b) {
    if (a <= b) {
        return 0;
    }
    return 1;
}

void dfs(int x, vector<vector<int>>& graph, vector<int>& viz, vector<int>& parents,
map<int, vector<pair<int,int>>>& map_index_to_queries, map<int, int>& map_index_to_age) {
    viz[x] = 1;
    //cout << "x este " << x << "\n";
    vector<pair<int,int>>& queries_x = map_index_to_queries[x];
    for (int i = 0; i < queries_x.size(); i++) {
        int b = queries_x[i].first;
        int ord = queries_x[i].second;
        int sol = -1;
        bool found = false;
        //cout << "------ caut pt varsta " << b << "\n";
        /*for (auto it2 : parents) {
            int varsta = map_index_to_age[it2]; // 10
            //cout << " gasesc varsta " << varsta << "\n";
            if (varsta <= b) {
                sol = it2;
                //cout << "updatez sol cu " << sol << "\n";
                break;
            }
        }*/
        //cout << "da\n";
        //cout << pow(2, 31) << "\n";
        //parents.push_back(x);

        /*for (int i = 0; i < parents.size(); i++) {
            cout << parents[i] << " ";
        }
        cout << "\n";*/

        for (int bit = pow(2, 30); bit >= 1; bit=bit/2) {
            //cout << "intru\n";
            int t = sol + bit;
            if (t < parents.size() && funct(map_index_to_age[parents[t]], b)) {
                sol = t;
                found = true;
                //cout << "DA\n";
            }
        }
        //cout << "parents de sol ::" << parents[sol] << "\n";
        //cout << "val age " << map_index_to_age[parents[sol]] << "\n";
        //cout << " b " << b << "\n";

        if (map_index_to_age[parents[sol]] > b && sol + 1 >= parents.size()) {
            //cout << "daaaaa\n";
            sol = x;
        }
        else sol = parents[sol + 1];
        
        //cerr << ord << ' ' << sol << ' ' << map_index_to_age[sol] << ' ' << b << '\n';
        solution[ord] = sol;
    }

    for (auto it : graph[x]) {
        if (viz[it] == -1) {
            // x tatal lui it

            parents.push_back(x);
            //cout << "Parintele lui " << it << " este " << x << "\n";
            dfs(it, graph, viz, parents, map_index_to_queries, map_index_to_age);
            parents.pop_back();
        }
    }
}

void testcase() {
    int n, q; cin >> n >> q;

    map<int, string> map_index_to_name;
    map<string, int> map_name_to_index;
    map<int, int> map_index_to_age;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        int age; cin >> age;
        
        map_index_to_name[i] = s;
        assert(map_name_to_index.find(s) == map_name_to_index.end());
        map_name_to_index[s] = i;
        map_index_to_age[i] = age;
    }

    vector<int> is_root(n, 1);

    // 0 to n - 1 index
    vector<vector<int>> graph(n, vector<int>());
    for (int i = 0; i < n - 1; i++) {
        string s, p;
        cin >> s >> p;
        int index_s = map_name_to_index[s];
        int index_p = map_name_to_index[p];

        graph[index_p].push_back(index_s);
        is_root[index_s] = 0;
    }

    int root = 0;
    for (int i = 0; i < n; i++) {
        if (is_root[i]) {
            root = i;
        }
    }

    for (int i = 0; i < n; i++) {
        if (!is_root[i]) {
            assert(i != root);
        }
    }

    for (int i = 0; i < n; i++) {
        //cout << "Node " << i << " : ";
        for (int j = 0; j < graph[i].size(); j++) {
          //  cout << graph[i][j] << " ";
        }
        //cout << "\n";
    }


    map<int, vector<pair<int,int>>> map_index_to_queries;
    for (int i = 0; i < q; i++) {
        string s;
        int b;
        cin >> s >> b;

        int index = map_name_to_index[s];        
        map_index_to_queries[index].push_back(make_pair(b, i));
    }


    vector<int> viz(n, -1);
    vector<int> parents;
    solution = vector<int>(q, 0);

    dfs(root, graph, viz, parents, map_index_to_queries, map_index_to_age);
    for (int i = 0; i < parents.size(); i++) {
        //cout << "parents " << parents[i] << "\n";
    }
   // cout << "\n";


    for (int i = 0; i < solution.size(); i++) {
        cout << map_index_to_name[solution[i]] << " ";
    }
    cout << "\n";

    solution.clear();

}

int main() {
    ios_base::sync_with_stdio(false);

    int t; cin >> t;

    while (t--) {
        testcase();
    }
}