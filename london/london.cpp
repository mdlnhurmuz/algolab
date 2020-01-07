#include <iostream>
using namespace std;
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property, boost::property<boost::edge_capacity_t, long, boost::property<boost::edge_residual_capacity_t, long, boost::property<boost::edge_reverse_t, traits::edge_descriptor> > > > graph;
typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

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
    int h, w; cin >> h >> w;

    string s;
    cin >> s;
    map<int, int> freq_s;
    for (int i = 0; i < s.length(); i++) {
        freq_s[s.at(i) - 'A']++;
    }
    int actual_length = s.length();

    vector<char> front(h * w);
    vector<char> back(h * w);
    for (int i = 0; i < h * w; i++) {
            char c; cin >> c;
            front[i] = c;
    }

    vector<vector<char>> back_cp(h, vector<char>(w));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            char c; cin >> c;
            back_cp[i][j] = c;
        }
    }
    int counter = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            char c = back_cp[i][w - j - 1];
            back[counter] = c;
            counter++;
        }
    }
    // Now front[i] - back[i] are corresponding.

    map<pair<char, char>, int> pairs;
    for (int i = 0; i < h * w; i++) {
        char c1 = front[i];
        char c2 = back[i];
        int l1 = freq_s[c1 - 'A'];
        int l2 = freq_s[c2 - 'A'];
        pair<char, char> p = make_pair(c1, c2);
        pairs[p] += 1;
    }

    graph G(pairs.size() + 26);
    edge_adder adder(G);
    // Add special vertices source and sink
    const vertex_desc v_source = boost::add_vertex(G);
    const vertex_desc v_target = boost::add_vertex(G);

    // Add edges from source.
    int i = 0;
    for (auto p : pairs) {
        adder.add_edge(v_source, i, p.second);
        i++;
    }
    // Add edges from letters to target.
    for (int i = pairs.size(); i < pairs.size() + 26; i++) {
        int letter = i - pairs.size();
        if (freq_s[letter] != 0)
            adder.add_edge(i, v_target, freq_s[letter]);
    }
    i = 0;
    for (auto key_value : pairs) {
            char l1 = key_value.first.first;
            char l2 = key_value.first.second;
            int occurences = key_value.second;
            int pos_node = i;
            i++;
            int lett1 = pairs.size() + l1 - 'A';
            int lett2 = pairs.size() + l2 - 'A';
            adder.add_edge(pos_node, lett1 , occurences);
            adder.add_edge(v_source, lett1, 0);
            adder.add_edge(pos_node, v_target, 0);

            adder.add_edge(pos_node, lett2 , occurences);
            adder.add_edge(v_source, lett2, 0);
            adder.add_edge(pos_node, v_target, 0);
    }

    long flow = boost::push_relabel_max_flow(G, v_source, v_target);
    if (flow >= actual_length) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}
int main() {

    std::ios_base::sync_with_stdio(false); // Always.
    int t; cin >> t;
    while (t--) {
        make_it_flow();
    }
    return 0;
}
