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

bool f(   int c, int b, int a, int k, int flow,  vector<pair<pair<int, int>, pair<int, int>> >& edges, int value  ) {
    graph G(c+1);
    edge_adder adder(G);

    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto rc_map = boost::get(boost::edge_residual_capacity, G);

    adder.add_edge(0, k+1, value, 0);
    for (int i = 0; i < edges.size(); i++) {
        auto first = edges[i].first;
        auto second = edges[i].second;
        adder.add_edge(first.first + 1, first.second + 1, second.second, second.first);
    }

    boost::successive_shortest_path_nonnegative_weights(G, 0, a+1);
    int cost = boost::find_flow_cost(G);
    if (cost <= b) {
        return 1;
    } else {
        return 0;
    }   
}


void testcase() {
    int c, g, b, k, a;
    cin >> c >> g >> b >> k >> a;

    graph G(c);
    edge_adder adder(G);
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto rc_map = boost::get(boost::edge_residual_capacity, G);

    vector<pair<pair<int, int>, pair<int, int>> > edges;

    for (int i = 0; i < g; i++) {
        int x, y, d, e; cin >> x >> y >> d >> e;
        edges.push_back(make_pair(make_pair(x, y), make_pair(d, e)));
        adder.add_edge(x, y, e, d);
    }

    int flow = boost::push_relabel_max_flow(G, k, a);
    
    int i = 0;
    for (int bit = pow(2,30); bit >= 1; bit /= 2) {
        int test = i+bit;
        if (test <= flow && f(c,b,a,k,flow,edges,test)) i = test;
    }
    cout << i << '\n';

    
}


int main() {
    ios_base::sync_with_stdio(false);

    int t; cin >> t;
    while (t--) {
        testcase();
    }

    return 0;
}