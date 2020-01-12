#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

#include <boost/pending/disjoint_sets.hpp>

#include <algorithm>
#include <iostream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

// we want to store an index with each vertex
typedef CGAL::Triangulation_vertex_base_with_info_2<int,K>   Vb;
typedef CGAL::Triangulation_data_structure_2<Vb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>              Triangulation;

typedef Triangulation::Edge_iterator  Edge_iterator;
typedef Triangulation::Face_handle Face_handle;
typedef Triangulation::Vertex_handle Vertex_handle;

typedef boost::disjoint_sets_with_storage<> DS;

using namespace std;

void testcase() {
    int n, m;
    K::FT p;
    cin >> n >> m >> p;

    // read jammers
    std::vector<pair<K::Point_2, int>> pts;
    pts.reserve(n);
    for (std::size_t i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        pts.push_back(make_pair(K::Point_2(x, y), i));
    }

    // read missions
    vector<pair<K::Point_2, K::Point_2>> missions;
    missions.reserve(m);
    for (std::size_t i = 0; i < m; ++i) {
        int x, y, z, t;
        std::cin >> x >> y >> z >> t;
        missions.push_back(make_pair(K::Point_2(x, y), K::Point_2(z, t)));
    }


    vector<pair<K::FT, pair<int, int>>> edges;

    Triangulation t;
    t.insert(pts.begin(), pts.end());

    // output all edges; Look into the lecture edge representation
    for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
        auto f = e->first;
        auto u = f->vertex((e->second + 1) % 3);
        auto v = f->vertex((e->second + 2) % 3);
        K::FT l = squared_distance(u->point(), v->point());
        // Info gets int
        edges.push_back(make_pair(l, make_pair(u->info(), v->info())));
    }

    std::sort(edges.begin(), edges.end()); // REALLY IMPORTANT!!!
    // So that at every step, we only have to add a single edge to the graph.

    DS ds(n);
    for (auto it = edges.begin(); it != edges.end(); it++) {
        if (it->first > p) break;
        // UNION SET METHOD for DS
        ds.union_set(it->second.first, it->second.second);
    }

    DS ds_a(n);
    DS ds_b(n);
    auto it1 = edges.begin();
    auto it2 = edges.begin();

    K::FT a = 0;
    K::FT b = 0;
    for (int i = 0; i < m; i++) {
        bool result = true;

        auto s = missions[i].first;
        auto d = missions[i].second;

        auto sp = t.nearest_vertex(s); // sp vertex handle sp->point
        auto tp = t.nearest_vertex(d);

        K::FT needed = max(CGAL::squared_distance(s, sp->point()),
        CGAL::squared_distance(d, tp->point()));

        if (needed * 4 > p) {
            result = false;
        }
        else {
            // Is there a connected component between sp and tp?
            // FIND SET METHOD for DS
            if (ds.find_set(sp->info()) != ds.find_set(tp->info())) {
                result = false;
            }
        }

        if (result) {
            cout << "y";
        } else {
            cout << "n";
        }

        if (result) {
            // Compute b
            // Go over edges and add all edges of length <= b to and then continue to
            // add edges (increasing b accordingly) until sp and tp in the same component of ds_b
            while (it2 != edges.end() && ds_b.find_set(sp->info()) != ds_b.find_set(tp->info())) {
                ds_b.union_set(it2->second.first, it2->second.second);
                b = std::max(it2->first, b);
                it2++;
            }
            b = max(b, needed*4); // b = max(b, distance(s, sp), distance(d, tp))
        }

        // Compute a 
        while (it1 != edges.end() && ds_a.find_set(sp->info()) != ds_a.find_set(tp->info())) {
                ds_a.union_set(it1->second.first, it1->second.second);
                a = std::max(it1->first, a);
                it1++;
        }
        a = max(a, needed*4); 

    }
    cout << "\n";
    std::cout << std::fixed << std::setprecision(0) << a << '\n' << b << '\n';

}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        testcase();
    }
}
