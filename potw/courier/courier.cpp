// Algolab BGL Tutorial 2 (Max flow, by taubnert@ethz.ch)
// Flow example demonstrating how to use push_relabel_max_flow using a custom edge adder
// to manage the interior graph properties required for flow algorithms
#include <iostream>
using namespace std;
// BGL include
#include <boost/graph/adjacency_list.hpp>

// BGL flow include *NEW*
#include <boost/graph/push_relabel_max_flow.hpp>

// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property, boost::property<boost::edge_capacity_t, long, boost::property<boost::edge_residual_capacity_t, long, boost::property<boost::edge_reverse_t, traits::edge_descriptor> > > > graph;

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

void make_it_flow() {
    int z, j; cin >> z >> j;

    graph G(z + j);
    edge_adder adder(G);

    int z_offset = 0;
    int j_offset = z;
    const vertex_desc v_source = boost::add_vertex(G);
    const vertex_desc v_target = boost::add_vertex(G);

    for (int i = 0; i < z; i++) {
        int c; cin >> c;
        adder.add_edge(z_offset + i, v_target, c);
    }

    int sum_rewards = 0;
    for (int i = 0; i < j; i++) {
        int r; cin >> r;
        sum_rewards += r;
        adder.add_edge(v_source, j_offset + i, r);
    }

    for (int i = 0; i < j; i++) {
        int no; cin >> no;
        for (int j = 0; j < no; j++) {
            int zone; cin >> zone;
            adder.add_edge(j_offset + i, z_offset + zone, numeric_limits<int>::max());
        }
    }

    long flow = boost::push_relabel_max_flow(G, v_source, v_target);

    std::cout << (sum_rewards - flow) << "\n";

}

int main() {

    std::ios_base::sync_with_stdio(false); // Always.
    int t; cin >> t;
    while (t--) {
        make_it_flow();
    }
    return 0;
}