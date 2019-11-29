// ALGOLAB BGL Tutorial 3
// Flow example demonstrating
// - breadth first search (BFS) on the residual graph

// Compile and run with one of the following:
// g++ -std=c++11 -O2 bgl_residual_bfs.cpp -o bgl_residual_bfs ./bgl_residual_bfs
// g++ -std=c++11 -O2 -I path/to/boost_1_58_0 bgl_residual_bfs.cpp -o bgl_residual_bfs; ./bgl_residual_bfs

// Includes
// ========
// STL includes
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>
using namespace std;

// BGL graph definitions
// =====================
// Graph Type with nested interior edge properties for Flow Algorithms
typedef	boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
	boost::property<boost::edge_capacity_t, long,
		boost::property<boost::edge_residual_capacity_t, long,
			boost::property<boost::edge_reverse_t, traits::edge_descriptor> > > >	graph;
// Interior Property Maps
typedef	boost::graph_traits<graph>::edge_descriptor			edge_desc;
typedef	boost::graph_traits<graph>::out_edge_iterator			out_edge_it;

// Custom Edge Adder Class, that holds the references
// to the graph, capacity map and reverse edge map
// ===================================================
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};


void testcase() {
    int f, l;
    cin >> f >> l;
    // build graph
	const int N = f;
	graph G(N);
	edge_adder adder(G);
	auto rc_map = boost::get(boost::edge_residual_capacity, G);

	int src = 0;
	int sink = 0;

    // add edges between g's and s's
    for (int i = 0; i < l ; i++) {
        int a, b, c; cin >> a >> b >> c;
        adder.add_edge(a, b, c);
    }

    int good_src = -1;
    int good_sink = -1;
    int total_cost = INT_MAX;

    src = 0;
    for (int i = 1; i < f; i++) {
        sink = i;
	    int flow = boost::push_relabel_max_flow(G, src, sink);
        if (flow < total_cost) {
            total_cost = flow;
            good_sink = sink;
            good_src = src;
        }
    }

    sink = 0;
    for (int i = 1; i < f; i++) {
        src = i;
	    int flow = boost::push_relabel_max_flow(G, src, sink);
        if (flow < total_cost) {
            total_cost = flow;
            good_src = src;
            good_sink = sink;
        }
    }

    cout << total_cost << "\n";

    // Find a min cut via maxflow
	int flow = boost::push_relabel_max_flow(G, good_src, good_sink);

	// BFS to find vertex set S
    src = good_src;
	std::vector<int> vis(N, false); // visited flags
	std::queue<int> Q; // BFS queue (from std:: not boost::)
	vis[src] = true; // Mark the source as visited
	Q.push(src);
	while (!Q.empty()) {
		const int u = Q.front();
		Q.pop();
		out_edge_it ebeg, eend;
		for (boost::tie(ebeg, eend) = boost::out_edges(u, G); ebeg != eend; ++ebeg) {
			const int v = boost::target(*ebeg, G);
			// Only follow edges with spare capacity
			if (rc_map[*ebeg] == 0 || vis[v]) continue;
			vis[v] = true;
			Q.push(v);
		}
	}

    vector<int> sol;
    for (int i = 0; i < N; i++) {
        if (vis[i]) sol.push_back(i);
    }
    cout << sol.size() << " ";
    for (int i = 0; i < sol.size(); i++) {
        cout << sol[i] << " ";
    }
    cout << "\n";
}

// Main
int main() {
    std::ios_base::sync_with_stdio(false); // Always.
    
    int t; cin >> t;
    while (t--) {
        testcase();
    }

	return 0;
}
