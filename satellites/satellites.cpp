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
    int g, s, l;
    cin >> g >> s >> l;
    // build graph
	const int N = g + s + 2;
	graph G(N);
	edge_adder adder(G);
	auto rc_map = boost::get(boost::edge_residual_capacity, G);

	int src = 0;
	int sink = N - 1;

    // add edges between g's and s's
    for (int i = 0; i < l ; i++) {
        int a, b; cin >> a >> b;
        adder.add_edge(a + 1, b + g + 1, 1);
    }

    // add edges from source
    for (int i = 0; i < g; i++) {
        adder.add_edge(src, i + 1, 1);
    }

    // add edges to target
    for (int i = 0; i < s; i++) {
        adder.add_edge(g + 1 + i, sink, 1);
    }

    // Find a min cut via maxflow
	int flow = boost::push_relabel_max_flow(G, src, sink);

	// BFS to find vertex set S
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

    vector<int> gs;
    vector<int> ss;
	for (int i = 1; i < N; ++i) {
        if (i <= g) {
            if (!vis[i]) {
                gs.push_back(i-1);
            }
        }
		else {
            if (vis[i]) {
                ss.push_back(i-1-g);
            }
        }
	}
	cout << gs.size() << " " << ss.size() << "\n";
    for (int i = 0; i < gs.size(); i++) {
        cout << gs[i] << " ";
    }
    for (int i = 0; i < ss.size(); i++) {
        cout << ss[i] << " ";
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
