#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/intersections.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;

using namespace std;

void testcase(int n) {
    long x, y, a, b; cin >> x >> y >> a >> b;
    P ss(x, y), dd(a, b);
    K::Ray_2 ray(ss, dd);

    bool intersects = false;
    for (int i = 0; i < n; i++) {
        long r, s, t, u; cin >> r >> s >> t >> u;
        P start(r, s), end(t, u);
        K::Line_2 segm(start, end);

        auto or1 = CGAL::orientation(ss, dd, start);
        auto or2 = CGAL::orientation(ss, dd, end);

        if (or1 * or2 <= 0) {
            if (CGAL::do_intersect(ray, segm)) {
               intersects = true;
            }
        }
    }

    if (!intersects)
        cout << "no\n";
    else
    {
        cout << "yes\n";
    }
    
}

int main() {
    std::ios_base::sync_with_stdio(false);
    while (true) {
        long n; cin >> n;
        if (n == 0) break;
        testcase(n);
    }
}
