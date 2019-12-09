// example: how to solve a simple explicit LP
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef CGAL::Quadratic_program_solution<ET> Solution;
using namespace std;


double ceil_to_double(const CGAL::Quotient<ET>& x)
{
    double a = std::ceil(CGAL::to_double(x));
    while (a < x) a += 1;
    while (a-1 >= x) a -= 1;
    return a;
}   

double floor_to_double(const CGAL::Quotient<ET>& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
} 

void testcase() {
    double n, m, h, w;
    cin >> n >> m >> h >> w;

    std::vector<pair<double, double>> free;
    std::vector<pair<double, double>> busy;

    for (int i = 0; i < n; i++) {
        double x, y; cin >> x >> y;
        free.push_back(make_pair(x, y));
    }

    for (int i = 0; i < m; i++) {
        double x, y; cin >> x >> y;
        busy.push_back(make_pair(x, y));
    }
    // Done reading.

    // create an LP with Ax <= b
    Program lp (CGAL::SMALLER, true, 1, false, 0); 

    int count = 0;
    // NEW WITH NEW 
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            auto pair1 = free[i];
            auto pair2 = free[j];

            double dx = 2 * abs(pair1.first - pair2.first);
            double dy = 2 * abs(pair1.second - pair2.second);
            if (dx * h < dy * w) {
                lp.set_a(i, count, h);
                lp.set_a(j, count, h);
                lp.set_b(count, 2 * abs(pair1.second - pair2.second));

                count++;
            } else {
                lp.set_a(i, count, w);
                lp.set_a(j, count, w);
                lp.set_b(count, 2 * abs(pair1.first - pair2.first));

                count ++;
            }
        }
    }


    // NEW WITH OLD
    for (int i = 0; i < n; i++) {
        double min_dist_x = INT_MAX;
        double min_dist_y = INT_MAX;
        for (int j = 0; j < m; j++) {
            auto pair1 = free[i];
            auto pair2 = busy[j];

            double dx = 2 * abs(pair1.first - pair2.first);
            double dy = 2 * abs(pair1.second - pair2.second);
            if (dx * h < dy * w) {
                min_dist_y = min(min_dist_y, dy);
            } else {
                min_dist_x = min(min_dist_x, dx);
            }
        }
        
        lp.set_a(i, count, h);
        lp.set_b(count, min_dist_y - h);

        count++;
        
        lp.set_a(i, count, w);
        lp.set_b(count, min_dist_x - w);

        count ++;
    }
    
    for (int i = 0; i < n; i++) {
        lp.set_c(i, - 2 * (w + h));
        //lp.set_l(i, true, 1);
    }

    // solve the program, using ET as the exact type
    Solution s = CGAL::solve_linear_program(lp, ET());

    cout << setprecision(0) << fixed << ceil_to_double(-s.objective_value()) << endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) {
        testcase();
    }

    return 0;
}
