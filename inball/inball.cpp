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

void testcase(int n, int d) {
    // create an LP with Ax <= b, lower bound 0 and no upper bounds
    Program lp (CGAL::SMALLER, false, 0, false, 0); 

    vector<vector<int>> ais(n, vector<int>());
    vector<int> bis;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            int el; cin >> el;
            ais[i].push_back(el);
        }
        int el; cin >> el;
        bis.push_back(el);
    }

    vector<double> norms;
    double s;
    for (int i = 0 ; i < n; i++) {
        s = 0;
        for (int j = 0; j < ais[i].size(); j++) {
            s += ais[i][j] * ais[i][j];
        }
        norms.push_back(sqrt(s));
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            lp.set_a(j, count, ais[i][j]);
        }
        lp.set_a(d, count, norms[i]);
        lp.set_b(count, bis[i]);
        count++;
    }

    lp.set_c(d, -1); // minimize r
    lp.set_l(d, true, 0); // radius must be positive

    Solution sol = CGAL::solve_linear_program(lp, ET());
    if (sol.is_infeasible()) {
        cout << "none\n";
    } else if (sol.is_unbounded()) {
        cout << "inf\n";
    } else cout << - (sol.objective_value().numerator()/ sol.objective_value().denominator()) << "\n";

}

int main() {

    std::ios_base::sync_with_stdio(false);
    while(true) {
        int n, d; cin >> n >> d;
        if (n == 0) break;
        testcase(n, d);
    }
}
