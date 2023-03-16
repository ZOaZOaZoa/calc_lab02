#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

#include <vector>
#include <string>
#include <sstream>
#include <windows.h>
#include <iostream>
#include <iomanip>


const std::string plot_program = "pyfiles/plotter.py";
const std::string newton_program = "pyfiles/newtoncheck.py";

std::vector<double> linspace(double start, double end, size_t count);
void plot_graph(double func(double), double begin, double end, size_t pts_count, std::string* title=nullptr);
void newton(double x0, double eps);
double bisection(double f(double), double left, double right, double eps, bool& converged, size_t* steps, size_t max_iter=100);
double simple_iteration(double f(double), double f_prime(double), double x0, double x_prime_min, double x_prime_max, double eps, 
                            bool* converged = nullptr, bool prompt = false, size_t max_iter = 100);


#endif // FUNC_H_INCLUDED