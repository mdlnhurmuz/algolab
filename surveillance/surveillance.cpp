// Algolab BGL Tutorial 2 (Max flow, by taubnert@ethz.ch)
// Flow example demonstrating how to use push_relabel_max_flow using a custom edge adder
// to manage the interior graph properties required for flow algorithms
#include <iostream>

// BGL include
#include <boost/graph/adjacency_list.hpp>

// BGL flow include *NEW*
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;

// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;



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

void testcase() {
    int n, m, k, l;
    cin >> n >> m >> k >> l;

    vector<int> police(k); // 0 1 4 4
    for (int i = 0; i < k; i++) {
        cin >> police[i];
    }

    vector<int> photo(l); // 2 2 4
    for (int i = 0; i < l; i++) {
        cin >> photo[i];
    }

    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int x, y ; cin >> x >> y;
        edges.push_back({x, y});
    }


    const int N = n * 2 + 2;
    graph G(N);
    edge_adder adder(G);

    const int v_source = 0;
    const int v_target = N - 1;


    // Source to first nodes
    for (int i = 0; i < police.size(); i++) {
        adder.add_edge(v_source, police[i] + 1, 1);
        //cout << "Adaug de la 0 la " << police[i] + 1 << "\n";
    }

    // Last nodes to sink
    for (int i = 0; i < police.size(); i++) {
        adder.add_edge(police[i] + n + 1, v_target, 1);
        //cout << "Adaug de la " << police[i] + n + 1 << " la sink \n";
    }

    // Nodes to nodes
    for (int i = 0; i < m; i++) {
        int x = edges[i].first;
        int y = edges[i].second;

        adder.add_edge(x + 1, y + 1, INT_MAX);
        adder.add_edge(x + n + 1, y + n + 1, 1);
    }

    // From no picture to picture
    for (int i = 0; i < photo.size(); i++) {
        int x = photo[i] + 1;
        int other_x = x + n;
        adder.add_edge(x, other_x , 1);

        //cout << "Adaug de la " << x << " la  " << other_x << "\n";
    }

    long flow = boost::push_relabel_max_flow(G, v_source, v_target);
    std::cout << flow << "\n";


}

int main() {
    ios_base::sync_with_stdio(false);

    int t; cin >> t;
    while (t--) {
        testcase();
    }

  return 0;
}