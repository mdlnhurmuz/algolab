// STL includes
#include <iostream>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

// BGL flow include *NEW*
#include <boost/graph/push_relabel_max_flow.hpp>

// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

using namespace std;


// Custom edge adder class, highly recommended
class edge_adder {
  graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

vector<int> dijkstra_dist(const weighted_graph &G, int s) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map;
}


void testcase() {
    int n, m, s, f; cin >> n >> m >> s >> f;
    
    vector<pair<pair<int, int>, int>> widths;
    vector<pair<pair<int, int>, int>> lengths;
    for (int i = 0; i < m; i++) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        widths.push_back(make_pair(make_pair(a, b), c));
        lengths.push_back(make_pair(make_pair(a, b), d));
    }

    weighted_graph G1(n);
    weight_map weights1 = boost::get(boost::edge_weight, G1);
    edge_desc e;

    for (int i = 0; i < m; i++) {
        auto points = lengths[i].first;
        auto length = lengths[i].second;
        e = boost::add_edge(points.first, points.second, G1).first; weights1[e]=length;
        e = boost::add_edge(points.second, points.first, G1).first; weights1[e]=length;
    }

    vector<int> dist_from_source = dijkstra_dist(G1, s);  
    vector<int> dist_from_finish = dijkstra_dist(G1, f);

    graph G(n);
    edge_adder adder(G);
    // Add special vertices source and sink
    const vertex_desc v_source = s;
    const vertex_desc v_target = f;

    auto dist_min = dist_from_source[f];

    for (int i = 0; i < m; i++) {
        auto points = lengths[i].first;
        auto l = lengths[i].second;
        auto x = points.first;
        auto y = points.second;
        auto curr_dist = dist_from_source[x] + l + dist_from_finish[y];
        auto curr_dist1 = dist_from_finish[x] + l + dist_from_source[y];
        if (curr_dist == dist_min) {
            adder.add_edge(x, y, widths[i].second);
        } else if (curr_dist1 == dist_min) {
            adder.add_edge(y, x, widths[i].second);
        }
    }

    long flow = boost::push_relabel_max_flow(G, v_source, v_target);
    std::cout << flow << "\n";
}

int main() {
    int t; cin >> t;
    while (t--) {
        testcase();
    }

    return 0;
}