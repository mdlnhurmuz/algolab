// STL includes
#include <iostream>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

using namespace std;

void kruskal(const weighted_graph &G) {
  std::vector<edge_desc> mst;    // vector to store MST edges (not a property map!)

  boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));

  for (std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it) {
    std::cout << boost::source(*it, G) << " " << boost::target(*it, G) << "\n";
  }
}

int dijkstra_dist(const weighted_graph &G, int s, int t) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map[t];
}

vector<pair<int,int>> prim(vector<vector<int>>& G, map<pair<int, int>, int>& costs, int source, int n) {
    vector<bool> selected(n, false);
    int no_edges = 0;
    selected[source] = true;
    //cout << "Source " << source << " " << selected[source] << "\n";
    vector<pair<int,int>> res;

    int x, y;
    while (no_edges < n - 1) {
        int min = INT_MAX;
        x = 0;
        y = 0;
        for (int i = 0; i < n; i++) {
            if (selected[i]) {
                for (int j = 0 ; j < G[i].size(); j++) {
                    if (!selected[G[i][j]]) {
                        int cost = costs[make_pair(i, G[i][j])];
                        if (min > cost) {
                            min = cost;
                            x = i;
                            y = G[i][j];
                            //cout << " Am pus muchia " << i << " cu " << j << "\n";
                        }
                    }
                }
            }
        }
        //cout << x << " - " << y << "\n";
        selected[y] = true;
        no_edges++;
        res.push_back(make_pair(x, y));
    }

    return res;
}

void testcase() {
    int n, e, s, a, b; cin >> n >> e >> s >> a >> b;
    vector<vector<vector<int>>> graphs(s);
    vector<map<pair<int, int>, int>> costs(s);
    for (int i = 0; i < s; i++) {
        graphs[i] = vector<vector<int>>(n);
    }

    for (int j = 0; j < e; j++) {
        int t1, t2; cin >> t1 >> t2; 
        for (int i = 0; i < s; i++) {
            int cost; cin >> cost;
            vector<vector<int>>& g = graphs[i];
            map<pair<int,int>, int>& c = costs[i];
            g[t2].push_back(t1);
            g[t1].push_back(t2);
            c[make_pair(t1, t2)] = cost;
            c[make_pair(t2, t1)] = cost;
            //cout << "[" << i << "]" << "Am adaugat muchia " << t1 << " cu " << t2 << " cost " << cost <<"\n";
        }
    }

    vector<int> hives;
    for (int i = 0; i < s; i++) {
        int h; cin >> h;
        hives.push_back(h);
    }


    vector<vector<pair<int, int>>> results;
    for (int i = 0; i < s; i++) {
        //cout << "Graph " << i << " pt hive " << hives[i] << "\n";
        auto res = prim(graphs[i], costs[i], hives[i], n);
        results.push_back(res);
    }

    weighted_graph G(n);
    weight_map weights = boost::get(boost::edge_weight, G);

    for (int i = 0; i < results.size(); i++) {
        for (int j = 0; j < results[i].size(); j++) {
            int x = results[i][j].first;
            int y = results[i][j].second;
            edge_desc e;
            e = boost::add_edge(x, y, G).first; 
            if (weights[e] != 0) {
                weights[e]=min(weights[e], costs[i][make_pair(x,y)]);
            } else {
                weights[e]=costs[i][make_pair(x,y)];
            }
        }
    }

    cout << dijkstra_dist(G, a, b)  << "\n";

}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t; cin >> t;
    while (t--) {
        testcase();
    }

  return 0;
}
