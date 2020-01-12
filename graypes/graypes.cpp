#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;

double ceil_to_double(K::FT const & x) {
    double a = std::ceil(CGAL::to_double(x));
    while (a < x) a += 1;
    while (a-1 >= x) a -= 1;
    return a;
}

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

    K::FT distance_min = std::numeric_limits<K::FT>::max();
    for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
        auto segm = t.segment(e);
        auto p1 = segm.source();
        auto p2 = segm.target();

        auto sq_distance = squared_distance(p1, p2);
        if (sq_distance < distance_min) {
            distance_min = sq_distance;
        }

    }

    auto sqrt_dist = sqrt(distance_min) * 50;
    std::cout.precision(0);
    std::cout << fixed;
    cout << ceil_to_double(sqrt_dist) << "\n";
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
