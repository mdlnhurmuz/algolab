#include <iostream>
#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;


using namespace std;

int q(vector<int>& t, int x) {
    int R = x;
    while (R != t[R]) {
        R = t[R];
    }

    int aux;
    while (x != R) {
        aux = t[x];
        t[x] = R;
        x = aux;
    }

    return R;
}

void testcase() {
    int n, m;
    K::FT r;
    cin >> n >> m >> r;

    vector<K::Point_2> stations;
    for (int i = 0; i < n; i++) {
        long a, b; cin >> a >> b;
        stations.push_back(K::Point_2(a, b));
    }

    // construct triangulation
    Triangulation t;
    t.insert(stations.begin(), stations.end());

    map<K::Point_2, int> map_points_to_index;
    vector<pair<pair<int, int>, K::FT>> graph;
    int count = 0;

    // output all edges
    for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
        auto segment = t.segment(e);
        auto s = segment.source();
        auto t = segment.target();

        K::FT d = CGAL::squared_distance(s, t);

        if (map_points_to_index.find(s) == map_points_to_index.end()) {
            map_points_to_index[s] = count;
            count++;
        } 
        if (map_points_to_index.find(t) == map_points_to_index.end()) {
            map_points_to_index[t] = count;
            count++;
        }

        graph.push_back({{map_points_to_index[s], map_points_to_index[t]}, d});
    }

    vector<int> parents;
    for (int i = 0; i < count; i++) {
        parents.push_back(i);
    }

    for (int i = 0; i < graph.size(); i++) {
        auto x = graph[i].first.first;
        auto y = graph[i].first.second;

        auto d = graph[i].second;

        if (d <= r * r) {
            auto qx = q(parents, x);
            auto qy = q(parents, y);

            if (qx != qy) {
                parents[qx] = qy;
            }
        }
    }

    /*for (int i = 0; i < parents.size(); i++) {
        cout << q(parents, i) << " ";
    }
    cout << "\n";*/

    for (int i = 0; i < m; i++) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        K::Point_2 point1(a, b);
        K::Point_2 point2(c, d);

        auto distance_between = CGAL::squared_distance(point1, point2);
        if (distance_between <= r * r) {
            cout << "y";
            continue;
        }

        auto nearest1 = t.nearest_vertex(point1)->point();
        auto nearest2 = t.nearest_vertex(point2)->point();

        if (CGAL::squared_distance(nearest1, point1) > r * r ||
        CGAL::squared_distance(nearest2, point2) > r * r) {
            cout << "n";
            continue;
        }

        int x = map_points_to_index[nearest1];
        int y = map_points_to_index[nearest2];

        if (q(parents, x) != q(parents, y)) {
            cout << "n";
        } else {
            cout << "y";
        }
    }


    cout << "\n";

}

int main() {
    int t;
    cin >> t;

    while (t--) {
        testcase();
    }
}