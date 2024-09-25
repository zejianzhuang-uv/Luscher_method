#include <iostream>
#include <fstream>
#include <gsl/gsl_roots.h>
#include <gsl/gsl_errno.h>
#include <cmath>
#include <bisection.cpp>
using namespace std;




double energy_level(double ka, double n){
    return ka * sin(ka * n / 2.) - 5. * cos(ka) * cos(ka * (n / 2. - 1.) );
}

struct my_f_params {double n;};
double find_energy_levels(double ka, void * p) {
    struct my_f_params * params = (struct my_f_params *)p;
    double n = (params -> n);
    return energy_level(ka, n);
}

int main(){
    // struct my_f_params params = {5e0};
    vector<double> rv;
    gsl_function F;
    F.function = &find_energy_levels;
    // F.params = &params;
    double init_x[2] = {0e0, 10e0};
    // rv  = find_roots(F, init_x, 0.01, 10);
    // for (double r : rv)
    // {
    //     cout << r << endl;
    // };
    ofstream ff("./energy_level.dat");
    ff.precision(17);
    double n0 = 2e0;
    while (n0 <= 10e0)
    {
        struct my_f_params params = {n0};
        F.params = &params;
        rv = find_roots(F, init_x, 0.01, 10);

        for (size_t i = 0; i < rv.size(); ++i) {
        ff << rv[i];
        if (i != rv.size() - 1) { // 如果不是最后一个元素，输出逗号
            ff << ",";
        };}
        ff << endl;
        n0 += 0.01;
    }
    ff.close();
}


