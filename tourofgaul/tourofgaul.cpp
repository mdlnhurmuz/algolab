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

// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator


using namespace std;

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
    int n, m; cin >> n >> m;

    vector<int> capac;
    int max_capac = 0;
    for (int i = 0; i < n -1; i++) {
        int el; cin >> el;
        capac.push_back(el);
        max_capac = max(max_capac, el);
    }

    const int N = n + 2;
    const int v_source = 0;
    const int v_target = N - 1;

    graph G(N);
    edge_adder adder(G);
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto rc_map = boost::get(boost::edge_residual_capacity, G);

    const int MAGIC = 1500;
    
    const int BOMBOANE = 1000;

    // nodes to nodes
    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        // Trec cand nu fac joburi (stau) (din cele care ar putea face joburi)
        adder.add_edge(i + 1, i + 2, capac[i], MAGIC); 
        // Un fel de job care e de nerefuzat si captureaza acele unitati care sunt obligate sa stea tura asta
        adder.add_edge(i + 1, i + 2, max_capac - capac[i], MAGIC - BOMBOANE); // astea ar tb sa treaca totusi pt ca mai tarziu pot face joburi
        count += max_capac - capac[i];
    }

    // items 
    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        adder.add_edge(a + 1, b + 1, 1, (b - a) * MAGIC - c);
    }

    adder.add_edge(v_source, 1, max_capac, 0);
    adder.add_edge(N - 2, v_target, max_capac, 0);

     // Option 2: Min Cost Max Flow with successive_shortest_path_nonnegative_weights  
    boost::successive_shortest_path_nonnegative_weights(G, v_source, v_target);
    int cost2 = boost::find_flow_cost(G);
    
    // Iterate over all edges leaving the source to sum up the flow values.
    int s_flow = 0;
    out_edge_it e, eend;
    for(boost::tie(e, eend) = boost::out_edges(boost::vertex(v_source,G), G); e != eend; ++e) {
        s_flow += c_map[*e] - rc_map[*e];     
    }
   
    cout << -(cost2 - (n-1) * s_flow * MAGIC + count * BOMBOANE) << "\n";
}


int main() {
    ios::sync_with_stdio(false);

    int t; cin >> t;

    while (t--) {
        testcase();
    }

    return 0;
}