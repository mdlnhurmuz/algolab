#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;


using namespace std;

void testcase(int n) {
    // read points
    std::vector<K::Point_2> pts;
    pts.reserve(n);
    for (std::size_t i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        pts.push_back(K::Point_2(x, y));
    }
    // construct triangulation
    Triangulation t;
    t.insert(pts.begin(), pts.end());

    int m; cin >> m;
    for (int i = 0 ; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        K::Point_2 q(x, y);

        auto handle = t.nearest_vertex(q);
        auto distance = squared_distance(handle->point(), q);
        std::cout.precision(0);
        std::cout << fixed;
        cout << distance << "\n";
    }
}

int main() {

    int n;
    while (true) {
        cin >> n;
        if (n == 0)
            break;

        testcase(n);

    }
}
