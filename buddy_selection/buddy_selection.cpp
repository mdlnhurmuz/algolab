// STL includes
#include <iostream>
#include <vector>

// BGL include
#include <boost/graph/adjacency_list.hpp>

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

using namespace std;

void testcase() {
    int n ; cin >> n;
    int c, f; cin >> c >> f;

    vector<vector<string>> carac(n, vector<string>(c));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < c; j++) {
            string s; cin >> s;
            carac[i][j] = s;
        }
    }

    for (int i = 0; i < carac.size(); i++) {
        std::sort(carac[i].begin(), carac[i].end());
    }

    vector<vector<int>> nr_carac(n, vector<int>(n));
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n;j++) {
            vector<string>& s1 = carac[i];
            vector<string>& s2 = carac[j];

            int l = 0;
            int k = 0;
            int common = 0;
            while (l < s1.size() && k < s2.size()) {
                if (s1[l].compare(s2[k]) < 0) {
                    l++;
                } else if (s1[l].compare(s2[k]) > 0) {
                    k++;
                } else {
                    common++;
                    l++;
                    k++;
                }
            }

            nr_carac[i][j] = common;
            nr_carac[j][i] = common;
            //cout << "De la i " << i << " la j " << j << " pun " << common << "\n";
        }
    }

    graph G(n*2 + 2);
    edge_adder adder(G);
    const vertex_desc v_source = 0;
    const vertex_desc v_target = n*2 + 1;

    for (int i = 0; i < n; i++) {
        adder.add_edge(v_source, i + 1, 1);
    }

    for (int i = 0; i < n; i++) {
        adder.add_edge(i + 1 + n, v_target, 1);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (nr_carac[i][j] > f) {
                adder.add_edge(i + 1, j + n + 1, 1);
                //adder.add_edge(v_source, j + n + 1, f+1);
                //adder.add_edge(i + 1, v_target, f+1);
            }
        }
    }

    long flow = boost::push_relabel_max_flow(G, v_source, v_target);

    if (flow < n) {
        cout << "optimal\n";
    } else {
        cout << "not optimal\n";
    }
    //std::cout << "eq " << (flow == n/2) << "\n";
    //cout << f << "\n";
    
}


int main() {
    std::ios_base::sync_with_stdio(false); // Always.
    int t; std::cin >> t;
    while (t--) {
        testcase();
    }
    return 0;
}