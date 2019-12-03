// ALGOLAB BGL Tutorial 3
// Code demonstrating 
// - MinCostMaxFlow with arbitrary edge costs using cycle_canceling
// - MinCostMaxFlow with non-negative edge costs using successive_shortest_path_nonnegative_weights

// Includes
// ========
#include <iostream>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
using namespace std;

// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator

// Custom edge adder class
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};


void testcase() {
    int n; cin >> n;

    // Create graph, edge adder class and propery maps
    graph G(n + 2);
    edge_adder adder(G);  
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto rc_map = boost::get(boost::edge_residual_capacity, G);
    const int v_source = 0;
    const int v_target = n + 1;

    int magic_add = 20;

    for (int i = 0; i < n; i++) {
        int a, c; cin >> a >> c;
        adder.add_edge(v_source, i + 1, a, c);
    }

    vector<int> no_students;
    for (int i = 0; i < n; i++) {
        int s, p; cin >> s >> p;
        no_students.push_back(s);
        adder.add_edge(i + 1, v_target, s, - p + magic_add);
    }

    for (int i = 0; i < n - 1; i++) {
        int v, e; cin >> v >> e;
        adder.add_edge(i + 1, i + 2, v, e);
    }

    // Min Cost Max Flow with successive_shortest_path_nonnegative_weights  
    boost::successive_shortest_path_nonnegative_weights(G, v_source, v_target);
    int cost2 = boost::find_flow_cost(G);
    // Iterate over all edges leaving the source to sum up the flow values.
    int s_flow = 0;
    int count = 0;
    bool possible = true;
    out_edge_it e, eend;
    for(boost::tie(e, eend) = boost::out_edges(boost::vertex(v_target,G), G); e != eend; ++e) {
        int flow_edge = rc_map[*e] - c_map[*e];
        s_flow += flow_edge;    
        if (no_students[count] > flow_edge) {
            possible = false;
        } 
        count++;
    }
    if (possible) {
        cout << "possible ";
    } else {
        cout << "impossible ";
    }
    std::cout << s_flow << " ";
    cout << - (cost2 - (s_flow * magic_add)) << "\n";

}

int main() {
    std::ios_base::sync_with_stdio(false); // Always.

    int t; cin >> t;
    while (t--) {
        testcase();
    }

    return 0;
}
