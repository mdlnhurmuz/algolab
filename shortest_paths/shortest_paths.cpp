// STL includes
#include <iostream>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

int dijkstra_dist(const weighted_graph &G, int s, int t) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map[t];
}

int main() {
    int n; std::cin >> n;
    int m; std::cin >> m;
    int q; std::cin >> q;

    for (int i = 0; i < n; i++) {
        int a, b;
        std::cin >> a >> b;
    }

    weighted_graph G(n);
    weight_map weights = boost::get(boost::edge_weight, G);
    edge_desc e;
    while (m--) {
        int a, b, c; std::cin >> a >> b >> c;
        e = boost::add_edge(a, b, G).first; weights[e]=c;
    }

    while (q--) {
        int s, t; std::cin >> s >> t;
        int res = dijkstra_dist(G, s, t);
        if (res == INT_MAX) std::cout << "unreachable\n";
        else std::cout << res << "\n";
    }

    return 0;
}