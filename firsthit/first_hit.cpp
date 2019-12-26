#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <stdexcept>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef std::result_of<K::Intersect_2(K::Ray_2,K::Segment_2)>::type IT;

using namespace std;

// round down to next double (as defined in the tutorial)
double floor_to_double(const K::FT& x) {
    double a = std::floor(CGAL::to_double(x));
    while (a > x) a -= 1;
    while (a+1 <= x) a += 1;
    return a;
}

// clip/set target of s to o
void shorten_segment(K::Segment_2& s, const IT& o) {
    if (const K::Point_2* p = boost::get<K::Point_2>(&*o))
        s = K::Segment_2(s.source(), *p);
    else if (const K::Segment_2* t = boost::get<K::Segment_2>(&*o))
        // select endpoint of *t closer to s.source()
        if (CGAL::collinear_are_ordered_along_line
            (s.source(), t->source(), t->target()))
            s = K::Segment_2(s.source(), t->source());
        else
            s = K::Segment_2(s.source(), t->target());
        else
            throw std::runtime_error("Strange␣segment␣intersection.");
}

void find_hit(std::size_t n) {
    // read input
    long x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    K::Ray_2 r(K::Point_2(x1, y1), K::Point_2(x2, y2));
    std::vector<K::Segment_2> segs;
    segs.reserve(n);
    for (int i = 0;  i < n ;i++) {
        std::cin >> x1 >> y1 >> x2 >> y2;
        segs.push_back(K::Segment_2(K::Point_2(x1, y1), K::Point_2(x2, y2)));
    }
    std::random_shuffle(segs.begin(), segs.end());

    K::Segment_2 rc(r.source(), r.point(1));

    // find some segment hit by r
    int i = 0;
    for (; i < n; i++) {
        if (CGAL::do_intersect(segs[i], r)) {
            shorten_segment(rc, CGAL::intersection(segs[i], r));
            break;
        }
    }
    if (i == n) {
        cout << "no\n"; return;
    }

    // check remaining segments against rc
    while (++i < n) {
        if (CGAL::do_intersect(segs[i], rc)) 
            shorten_segment(rc, CGAL::intersection(segs[i], r)); // not rc!
    }

    cout << floor_to_double(rc.target().x()) << " " <<  floor_to_double(rc.target().y()) << "\n";
    
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
    for (std::size_t n; cin >> n && n > 0;) {
        find_hit(n);
    }
}