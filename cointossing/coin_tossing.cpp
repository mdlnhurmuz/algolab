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
    int n, m; cin >> n >> m;
    graph G(n + m);
    edge_adder adder(G);
    // Add special vertices source and sink
    const vertex_desc v_source = boost::add_vertex(G);
    const vertex_desc v_target = boost::add_vertex(G);

    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        if (c == 1) {
            adder.add_edge(i, m + a, 1);
            //cout << " am pus muchia " << i << " cu " << m + a << " cu valoarea " << 1  << "\n";
        } else if (c == 2) {
            adder.add_edge(i, m + b, 1);
        } else  {
            adder.add_edge(i, m + a, 1);
            adder.add_edge(v_source, m + a, 0);
            adder.add_edge(i, v_target, 0);
            adder.add_edge(i, m + b, 1);
            adder.add_edge(v_source, m + b, 0);
            adder.add_edge(i, v_target, 0);
        }
    }

    // Add special vertices source and sink
    for (int i = 0; i < m; i++) {
        //cout << " am pus muchia " << v_source << " cu " << i << " cu valoarea " << 1  << "\n";
        adder.add_edge(v_source, i, 1);
    }
    vector<int> finals;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        int el; cin >> el;
        sum += el;
        finals.push_back(el);
        //cout << " am pus muchia " << i + m << " cu " << v_target << " cu valoarea " << el  << "\n";
        adder.add_edge(i + m, v_target, el);
    }

    // Calculate flow from source to sink
    // The flow algorithm uses the interior properties (managed in the edge adder)
    // - edge_capacity, edge_reverse (read access),
    // - edge_residual_capacity (read and write access).
    long flow = boost::push_relabel_max_flow(G, v_source, v_target);
    //std::cout << "The total flow is " << flow << "\n";

    // Retrieve the capacity map and reverse capacity map
    const auto c_map = boost::get(boost::edge_capacity, G);
    const auto rc_map = boost::get(boost::edge_residual_capacity, G);

    // Iterate over all the edges to print the flow along them
    auto edge_iters = boost::edges(G);
    int i = 0;
    bool correct = true;
    for (auto edge_it = edge_iters.first; edge_it != edge_iters.second; ++edge_it) {
        const edge_desc edge = *edge_it;
        const long flow_through_edge = c_map[edge] - rc_map[edge];
        auto t = boost::target(edge, G);
        auto s = boost::source(edge, G);
        if (t == n + m + 1 && s >= m && s < n+m) {
            /*std::cout << "edge from " << boost::source(edge, G) << " to " << boost::target(edge, G)
                    << " runs " << flow_through_edge
                    << " units of flow (negative for reverse direction). \n";*/
            if (flow_through_edge != finals[i]) {
                correct = false;
                break;
            } else {
                i++;
            }
        }
    }


    if (correct == false || m != flow) {
        cout << "no\n";
    } else {
        cout << "yes\n";
    }
}

int main() {

    int t; cin >> t;
    while (t--) {
        make_it_flow();
    }
    return 0;
}