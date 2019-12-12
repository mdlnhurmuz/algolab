// STL includes
#include <iostream>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

using namespace std;


vector<int> dijkstra_dist(const weighted_graph &G, int s) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map;
}

int dijkstra_path(const weighted_graph &G, int s, int t, std::vector<vertex_desc> &path) {
  int n = boost::num_vertices(G);
  std::vector<int>         dist_map(n);
  std::vector<vertex_desc> pred_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G)))
    .predecessor_map(boost::make_iterator_property_map(
      pred_map.begin(), boost::get(boost::vertex_index, G))));

  int cur = t;
  path.clear(); path.push_back(cur);
  while (s != cur) {
    cur = pred_map[cur];
    path.push_back(cur);
  }
  std::reverse(path.begin(), path.end());
  return dist_map[t];
}

int getIndex(int i, int j) {
    if (i == 0 && j == 0) return 0;
    return i * (i + 1)/2 + j;
}

void testcase() {
    int k; cin >> k;

    vector<vector<int>> balls(k, vector<int>());
    map<int, int> index_to_value;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < i + 1; j++) {
            int el; cin >> el;
            balls[i].push_back(el);
            index_to_value[getIndex(i, j)] = el;
        }
    }

    vector<set<int>> graph(k * (k + 1)/2, set<int>());
    for (int i = 0; i < k - 1; i++) {
        for (int j = 0; j <  balls[i].size(); j++) {
            int curr = getIndex(i, j);
            int currst = getIndex(i + 1, j);
            int currdr = getIndex(i + 1, j + 1);
            graph[curr].insert(currst);
            graph[curr].insert(currdr);
            graph[currst].insert(curr);
            graph[currdr].insert(curr);

            if (j >= 1) {
                int st = getIndex(i, j - 1);
                graph[curr].insert(st);
                graph[st].insert(curr);
            }

            if (j + 1 < balls[i].size()) {
                int dr = getIndex(i, j + 1);
                graph[curr].insert(dr);
                graph[dr].insert(curr);
            }
        }
    }

    int i = k - 1;
    for (int j = 0; j < balls[i].size(); j++) {
        int curr = getIndex(i, j);
        if (j >= 1) {
            int st = getIndex(i, j - 1);
            graph[curr].insert(st);
            graph[st].insert(curr);
        }

        if (j + 1 < balls[i].size()) {
            int dr = getIndex(i, j + 1);
            graph[curr].insert(dr);
            graph[dr].insert(curr);
        }
    }

    weighted_graph G(k * (k + 1)/2);
    weight_map weights = boost::get(boost::edge_weight, G);

    edge_desc e;

    int s1 = getIndex(0, 0);
    int s2 = getIndex(k - 1, 0);
    int s3 = getIndex(k -1, k - 1);

    for (int i = 0; i < graph.size(); i++) {
        for (auto it = graph[i].begin(); it != graph[i].end(); it++) {
            e = boost::add_edge(*it, i, G).first; weights[e] = index_to_value[i];
        }
    }

    vector<int> v1 = dijkstra_dist(G, s1);
    vector<int> v2 = dijkstra_dist(G, s2);
    vector<int> v3 = dijkstra_dist(G, s3);

    int minx = INT_MAX;
    for (int i = 0; i < v1.size(); i++) {
        minx = min(minx, v1[i] + v2[i] + v3[i] - 2 * index_to_value[i]);
    } 
    cout << minx << "\n";

}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) {
        testcase();
    }

    return 0;
}
