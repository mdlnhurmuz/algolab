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

void testcase() {
    int h, t; cin >> h >> t;

    vector<vector<int>> hv(h, vector<int>(3));
    vector<vector<int>> tv(t, vector<int>(3));

    // create an LP with Ax <= b, lower bound 0 and no upper bounds
    Program lp (CGAL::SMALLER, false, 0, false, 0); 
    int count = 0;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < 3; j++) {
            lp.set_a(j, count, +hv[i][j]);
        }
        lp.set_b(count, 0);
        count++;
    }

    for (int i = 0; i < t; i++) {
        for (int j = 0; j < 3; j++) {
            lp.set_a(j, count, -tv[i][j]);
        }
        lp.set_b(count, 0);
        count++;
    }
    
    Solution sol = CGAL::solve_linear_program(lp, ET());
    if (!sol.is_infeasible()) {
        cout << "yes\n";
    }
}

int main() {

    std::ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) {
        testcase();
    }
}
