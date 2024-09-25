// Zejian Zhuang, Melissa
// Finding roots using bisection rewriten by C++





//#include <iostream>
#include <vector>
#include <gsl/gsl_roots.h>
#include <gsl/gsl_errno.h>
using namespace std;






double bisection(gsl_function F, double init_x[2]) {
    double EPS = 1e-7;
    double x_lower = init_x[0];
    double x_upper = init_x[1];
    const gsl_root_fsolver_type *T = gsl_root_fsolver_bisection;
    gsl_root_fsolver *  solver = gsl_root_fsolver_alloc(T);
    gsl_root_fsolver_set(solver, &F, x_lower, x_upper);
    int iter = 0, max_iter = 100;
    while (iter <=max_iter)
    {
        x_lower = gsl_root_fsolver_x_lower(solver);
        x_upper = gsl_root_fsolver_x_upper(solver);
        // int gsl_ebadfunc = gsl_root_fsolver_iterate(solver);

        if (gsl_root_fsolver_iterate(solver) == GSL_EBADFUNC) {
            //the iteration encountered a singular point where the function or its derivative evaluated to Inf or NaN
            break;
        }

        if (gsl_root_test_interval(x_lower, x_upper, EPS, EPS) == GSL_SUCCESS)
        {
            break;
        }
        iter++;
    }
    double r = gsl_root_fsolver_root(solver);
    gsl_root_fsolver_free(solver);
    return r;
}

vector<double> find_roots(gsl_function F, double init_x[2], double step, int pole_num) {
    double x0 = init_x[0];
    double xf = init_x[1];
    vector<double> sol_vec;

    for (double x = x0 + step; x <= xf; x += step) {
        double f_x0 = GSL_FN_EVAL(&F, x0);
        double f_x = GSL_FN_EVAL(&F, x);

        if (f_x0 * f_x < 0) {
            // Root exists in [x0, x], so use bisection
            double range[2] = {x0, x};
            double sol = bisection(F, range);

            if ( abs(GSL_FN_EVAL(&F, sol)) < 1) {
                sol_vec.push_back(sol);

                if (sol_vec.size() == static_cast<size_t>(pole_num)) {
                    break;
                }

                x0 = x; // Move to the next range
            } else {
                x0 = x; // Move to the next range even if no root is found
            }
        } else {
            // If the function does not change sign, continue to the next step
            continue;
        }
    }
    return sol_vec;
}
