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
    int n, s; cin >> n >> s;

    vector<int> powers;
    for (int i = 0; i < s; i++) {
        int el; cin >> el;
        powers.push_back(el);
    }

    vector<pair<pair<int,int>, pair<pair<int, int>, int>>> edges;
    set<int> distinct_times;
    for (int i = 0; i < n; i++) {
        int s, t, d, a, p;
        cin >> s >> t >> d >> a >> p;
        edges.push_back({{s, t}, {{d, a}, p}});

        distinct_times.insert(d);
        distinct_times.insert(a);
    }


    const int N = 2 + s * distinct_times.size();
    const int v_source = 0;
    const int v_target = N - 1;

    const int MAGIC = 150;

    // Create graph, edge adder class and propery maps
    graph G(N);
    edge_adder adder(G);  
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto rc_map = boost::get(boost::edge_residual_capacity, G);

    map<int, int> m; // time to index in set
    int count = 0;
    for (auto it : distinct_times) {
        m[it] = count;
        //cout << "Am in map pentru " << it << " numarul " << count << "\n";
        count++;
    }

    for (int i = 0; i < powers.size(); i++) {
        adder.add_edge(v_source, i + 1, powers[i], 0);
        //cout << " ^^ Adaug edge de la " << v_source << " la " << i + 1 <<  " cu puterea " << powers[i] << "\n";
    }

    for (int i = 0; i < distinct_times.size()-1; i++) {
        for (int j = 0; j < s; j++) {
            adder.add_edge(i * s + j + 1, (i + 1)* s + j + 1, INT_MAX, MAGIC);
            //cout << "!!! Adaug de la " << i * s + j + 1 << " catre " << (i + 1)* s + j + 1 << "\n";
        }
    }

    for (int i = 0; i < edges.size(); i++) {
        int ss = edges[i].first.first;
        int t = edges[i].first.second;
        int d = edges[i].second.first.first;
        int a = edges[i].second.first.second;
        int p = edges[i].second.second;
        int number_d = m[d]; // 0, 1, 2, 3
        int number_a = m[a]; // 0, 1, 2, 3

        int from = number_d * s + ss; // 1
        int to = number_a * s + t; // 7
        int k_magic = (number_a - number_d);

        int cost = -p;
        adder.add_edge(from, to, 1, cost + k_magic * MAGIC);
        //cout << " -- Adaug de la " << from << " catre " << to << " costul " << k_magic * MAGIC + cost << "\n";
    }

    for (int i = 0; i < powers.size(); i++) {
        adder.add_edge(distinct_times.size() * s - (s - 1) + i, v_target, INT_MAX, 0);
        //cout << " ** Adaug de la " << distinct_times.size() * s - 1 + i << " catre " << v_target << "\n";
    }
    

    

    // Option 2: Min Cost Max Flow with successive_shortest_path_nonnegative_weights  
    boost::successive_shortest_path_nonnegative_weights(G, v_source, v_target);
    long cost2 = boost::find_flow_cost(G);
    int s_flow = 0;
    out_edge_it e, eend;
    for(boost::tie(e, eend) = boost::out_edges(boost::vertex(v_source,G), G); e != eend; ++e) {
        s_flow += c_map[*e] - rc_map[*e];     
    }


    //cout << cost2 << "\n";
    cout <<  - long(cost2  - 1LL * (distinct_times.size() - 1) * MAGIC * s_flow) << "\n";

}



int main() {
    ios_base::sync_with_stdio(false);

    int t; cin >> t;
    while (t--) {
        testcase();
    }    

    return 0;
}