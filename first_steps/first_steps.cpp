// STL includes
#include <iostream>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

int kruskal(const weighted_graph &G, const weight_map &weights) {
  std::vector<edge_desc> mst;    // vector to store MST edges (not a property map!)
  int sum = 0;

  boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));

  for (std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it) {
    // std::cout << boost::source(*it, G) << " " << boost::target(*it, G) << "\n";
    sum += weights[*it];
  }

  return sum;
}

int dijkstra_dist(const weighted_graph &G, int s) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  int max = 0;
  for (int i = 0; i < n; i++) 
    max = std::max(max, dist_map[i]);

  return max;
}

int main() {
    int t; std::cin >> t;
    while (t--) {
        int n; std::cin >> n;
        int m; std::cin >> m;
        weighted_graph G(n);
        weight_map weights = boost::get(boost::edge_weight, G);
        edge_desc e;
        while (m--) {
            int a, b, c; std::cin >> a >> b >> c;
            e = boost::add_edge(a, b, G).first; weights[e]=c;
        }
        std::cout << kruskal(G, weights) << " " <<  dijkstra_dist(G, 0) << "\n";
    }
    return 0;
}