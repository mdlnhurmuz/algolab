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
    while (cin >> n) {
        if (n == 0) break;
        for (int i = 0; i < n; i++) {
            long a, b; cin >> a >> b;
            K::Point_2 point(a, b);
            P.push_back(point);
        }

        Min_circle mc(P.begin(), P.end(), true);
        Traits::Circle c = mc.circle();
        K::Point_2 center_point = c.center();
        
        bool set_value = false;
        K::FT max_distance_to_center;

        // Compute max distance to center for all points N given.
        for (int i = 0; i < n; i++) {
            if (!set_value) {
                max_distance_to_center = CGAL::squared_distance(center_point, P[i]);
                set_value = true;
            } else {
                K::FT curr = CGAL::squared_distance(center_point, P[i]);
                if (curr > max_distance_to_center) {
                    max_distance_to_center = curr;
                }
            }
        }
        
        // For all the points at the distance of max_distance_to_center, try and erase that point 
        // and compute the minimum radius in each case.
        set_value = false;
        K::FT min_radius;
        for (int i = 0; i < n; i++) {
            K::FT curr = CGAL::squared_distance(center_point, P[i]);
            if (curr == max_distance_to_center) {
                std::vector<K::Point_2> P_copy(P.begin(), P.end());
                P_copy.erase(P_copy.begin() + i);

                Min_circle mc1(P_copy.begin(), P_copy.end(), true);
                Traits::Circle c1 = mc1.circle();
                auto d = CGAL::sqrt(c1.squared_radius());

                if (!set_value) {
                    set_value = true;
                    min_radius = d;
                } else {
                    if (min_radius > d) {
                        min_radius = d;
                    }
                }
                P_copy.clear();
            }
        }

        std::cout.precision(0);
        std::cout << fixed;
        std::cout << ceil_to_double(min_radius) << "\n";
        P.clear();
    }
}