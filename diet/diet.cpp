// example: how to solve a simple explicit LP
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpq ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

int floor_to_double(const CGAL::Quotient<ET>& x)
{
  double a = std::floor(CGAL::to_double(x));
  return a;
} 


void testcase(int n, int m) {
  Program lp(CGAL::SMALLER, true, 0, false, 0);

  vector<pair<int, int>> nutrients_bounds;
  vector<int> prices;
  vector<vector<int>> amounts(m, vector<int>(n));

  for (int i = 0; i < n; i++) {
    int min, max; cin >> min >> max;
    nutrients_bounds.push_back(make_pair(min, max));
  }

  // m x n amounts 
  for (int i = 0; i < m; i++) {
    int pj; cin >> pj;
    prices.push_back(pj);
    for (int j = 0; j < n; j++) {
      int cj; cin >> cj;
      amounts[i][j] = cj;
    }
  }

  // Put contraints.
  for (int i = 0; i < n; i++) { // column
    for (int j = 0; j < m; j++) { // line
      lp.set_a(j, i, -amounts[j][i]);
      lp.set_a(j, i + n, amounts[j][i]);
    }
  }
  for (int i = 0; i < n; i++) {
    lp.set_b(i, -nutrients_bounds[i].first);
    lp.set_b(i + n, nutrients_bounds[i].second);
  }


  // Objective function;
  for (int i = 0; i < m; i++) {
    lp.set_c(i, prices[i]);
  }


  // solve the program, using ET as the exact type
  Solution s = CGAL::solve_linear_program(lp, ET());
  
  if (s.status() == CGAL::QP_INFEASIBLE) {
    cout << "No such diet.\n";
  }
  else 
    cout << setprecision(0) << fixed << floor_to_double(s.objective_value()) << endl;
}

int main(){
  int n, m;
  cin >> n >> m;
  while (true) {
    if (n == 0 && m == 0) break;

    testcase(n, m);

    cin >> n >> m;
  }
}
