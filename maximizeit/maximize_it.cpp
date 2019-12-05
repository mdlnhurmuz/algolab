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
using namespace std;


double ceil_to_double(const CGAL::Quotient<ET>& x)
{
    double a = std::ceil(CGAL::to_double(x));
    while (a <= x) a += 1;
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


void getMin(double a, double b) {
    // create an LP with Ax <= b, lower bound 0 and no upper bounds
    Program lp (CGAL::SMALLER, false, 0, true, 0); 

    // set the coefficients of A and b
    const int X = 0; 
    const int Y = 1;
    const int Z = 2;
    // x, y, z <= 0 DONE
    // x + y >= -4
    lp.set_a(X, 0, -1); lp.set_a(Y, 0, -1); lp.set_b(0, 4);
    // 4x + 2y + z >= -ab
    lp.set_a(X, 1, -4); lp.set_a(Y, 1, -2); lp.set_a(Z, 1, -1); lp.set_b(1, a * b);
    // -x + y >= - 1
    lp.set_a(X, 2, 1); lp.set_a(Y, 2, -1); lp.set_b(2, 1);

    lp.set_c(X, a);
    lp.set_c(Y, b);
    lp.set_c(Z, 1);

    // solve the program, using ET as the exact type
    Solution s = CGAL::solve_linear_program(lp, ET());
    //assert(s.solves_linear_program(lp));

    // output solution
    if (s.is_unbounded()) {
        cout << "unbounded\n";
    } else if (s.is_infeasible()) {
        cout << "no\n";
    }
    else  
    if (s.objective_value() < 0)
        cout << setprecision(0) << fixed << (-floor_to_double(-s.objective_value())) << endl;
    else 
        cout << setprecision(0) << fixed << (floor_to_double(s.objective_value())) << endl;
}

void getMax(double a, double b) {
    // create an LP with Ax <= b, lower bound 0 and no upper bounds
    Program lp (CGAL::SMALLER, true, 0, false, 0); 

    // set the coefficients of A and b
    const int X = 0; 
    const int Y = 1;
    // x, y >= 0 DONE
    // x + y <= 4
    lp.set_a(X, 0, 1); lp.set_a(Y, 0, 1); lp.set_b(0, 4);
    // 4x + 2y <= ab
    lp.set_a(X, 1, 4); lp.set_a(Y, 1, 2); lp.set_b(1, a * b);
    // -x + y <= 1
    lp.set_a(X, 2, -1); lp.set_a(Y, 2, 1); lp.set_b(2, 1);

    lp.set_c(X, a);
    lp.set_c(Y, -b);
    lp.set_c0(0);

    // solve the program, using ET as the exact type
    Solution s = CGAL::solve_linear_program(lp, ET());
    //assert(s.solves_linear_program(lp));

    // output solution
    if (s.is_unbounded()) {
        cout << "unbounded\n";
    } else if (s.is_infeasible()) {
        cout << "no\n";
    }
    else  
    cout << setprecision(0) << fixed << floor_to_double(-s.objective_value()) << endl;
}

int main() {
    while (true) {
        double p, a, b;
        cin >> p;
        if (p == 0) break;
        cin >> a >> b;
        if (p == 1) {
            getMax(a, b);
        } 
        if (p == 2) {
            getMin(a, b);
        }
    }
}
