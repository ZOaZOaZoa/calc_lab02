#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

#include <vector>
#include <string>
#include <sstream>

const std::string plot_program = "pyfiles/plotter.py";
const std::string newton_program = "pyfiles/newtoncheck.py";

std::vector<double> linspace(double start, double end, size_t count);
void plot_graph(double func(double), double begin, double end, size_t pts_count);
void newton(double x0, double eps);


#endif // FUNC_H_INCLUDED