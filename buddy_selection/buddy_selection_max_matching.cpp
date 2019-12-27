// STL includes
#include <iostream>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;

bool maximum_matching(const graph &G) {
    int n = boost::num_vertices(G);
    std::vector<vertex_desc> mate_map(n);  // exterior property map
    const vertex_desc NULL_VERTEX = boost::graph_traits<graph>::null_vertex();

    boost::edmonds_maximum_cardinality_matching(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
    int matching_size = boost::matching_size(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));

    int counter = 0;
    for (int i = 0; i < n; ++i) {
        // mate_map[i] != NULL_VERTEX: the vertex is matched
        // i < mate_map[i]: visit each edge in the matching only once
        if (mate_map[i] != NULL_VERTEX && i < mate_map[i]) {
            //std::cout << i << " " << mate_map[i] << "\n";
            counter++;
        }
    }
    if (counter == n/2) 
        return true;

    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false); // Always.
    int t; std::cin >> t;
    while (t--) {
        int n, c, f;
        std::cin >> n >> c >> f;
        std::vector<std::vector<std::string> > car;
        for (int i = 0; i < n ;i++) {
            car.push_back(std::vector<std::string>());
            for (int j = 0; j < c; j++) {
                std::string s;
                std::cin >> s;
                car[i].push_back(s);
                //std::cout << car[i][j] << " ";
            }
            //std::cout << "\n";
        }
        for (int i = 0; i < n; i++)
            std::sort(car[i].begin(), car[i].end());

        int **common_carac = new int*[n];
        for (int i = 0; i < n; i++)
            common_carac[i] = new int[n];
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i < j) {
                    std::vector<std::string> a = car[i];
                    std::vector<std::string> b = car[j];
                    /*std::sort(a.begin(), a.end());
                    std::sort(b.begin(), b.end());*/
                    int common = 0;
                    int it1 = 0;
                    int it2 = 0;
                    while (it1 < a.size() && it2 < b.size()) {
                        if (a[it1].compare(b[it2]) == 0) {
                            common++;
                            it1++; it2++;
                        } else if (a[it1].compare(b[it2]) < 0) {
                            it1++;
                        } else {
                            it2++;
                        }
                    }
                    common_carac[i][j] = common;
                    common_carac[j][i] = common;
                } else if (i == j) {
                    common_carac[i][j] = 0;
                }
            }
        }

        /*for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                std::cout << common_carac[i][j] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";*/

        graph G(n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i < j) {
                    if (common_carac[i][j] >= f + 1) {
                        boost::add_edge(i, j, G);
                        //boost::add_edge(j, i, G);
                    }
                }
            }
        }
        
        bool res = maximum_matching(G);
        if (res == true) {
            std::cout << "not optimal\n";
        } else {
            std::cout << "optimal\n";
        }
    }
    return 0;
}