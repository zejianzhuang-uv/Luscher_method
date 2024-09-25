#include <iostream>
#include <fstream>
#include <gsl/gsl_roots.h>
#include <gsl/gsl_errno.h>
#include <cmath>
#include <bisection.cpp>
using namespace std;

double energy_level(double ka, double n)
{
    return ka * sin(ka * n / 2.) - 5. * cos(ka) * cos(ka * (n / 2. - 1.));
}

struct my_f_params
{
    double n;
};
double find_energy_levels(double ka, void *p)
{
    struct my_f_params *params = (struct my_f_params *)p;
    double n = (params->n);
    return energy_level(ka, n);
}

int main()
{
    // struct my_f_params params = {5e0};
    vector<double> rv;
    int pole_num = 10;
    gsl_function F;
    F.function = &find_energy_levels;
    // F.params = &params;
    double init_x[2] = {0e0, 10e0};

    ofstream ff("./energy_level.csv");
    ff.precision(17);
    for (int i = 0; i < pole_num; i++)
    {
        ff << "x" << i+1;
        if (i != pole_num - 1)
        {
            ff << ",";
        }
        else
        {
            ff << "\n";
        }
    }

    double n0 = 2e0;
    while (n0 <= 10e0)
    {
        struct my_f_params params = {n0};
        F.params = &params;
        rv = find_roots(F, init_x, 0.01, pole_num);

        for (int i = 0; i < pole_num; ++i)
        {   
            if (i < rv.size())
            {
                ff << rv[i];
                if (i != pole_num - 1)
                {
                    ff << ",";
                }
                else
                {
                    ff << "\n";
                }
            }
            else
            {
                ff << "NaN";
                if (i != pole_num - 1)
                {
                    ff << ",";
                }
                else
                {
                    ff << "\n";
                }
            }
            
        }
        n0 += 0.01;
    }
    ff.close();
}
