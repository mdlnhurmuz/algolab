#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K>  Traits;
typedef CGAL::Min_circle_2<Traits>      Min_circle;

using namespace std;

double ceil_to_double(const K::FT& x)
{
  double a = std::ceil(CGAL::to_double(x));
  while (a <= x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}

int main() {
    ios_base::sync_with_stdio(false); // Always.

    int n;
    std::vector<K::Point_2> P;
    while (cin >> n && n != 0) {
        for (int i = 0; i < n; i++) {
            long a, b; cin >> a >> b;
            K::Point_2 point(a, b);
            P.push_back(point);
        }

        Min_circle mc(P.begin(), P.end(), true);
        Traits::Circle c = mc.circle();
        auto d = CGAL::sqrt(c.squared_radius());
        std::cout.precision(0);
        std::cout << fixed;
        std::cout << ceil_to_double(d) << "\n";
        P.clear();
    }
}