#include <math.h>
#include <iostream>
#include <iomanip>

#include "../task1/func.h"

double f(double x);
double g(double x);

const size_t COUNT = 30;
const size_t MAX_STEPS = 1000;
std::string py_prog = "pyfiles/root.py";
double (*func)(double) = g;
const char funcLabel_PY = 'g';

double f(double x)
{
    return pow(tan(x), 2)-28.0/9*tan(x)-sqrt(3);
}

double g(double x)
{
    return pow(tan(x), 2)-2*tan(x)+1;
}

int main()
{
    double a, b, eps, root, python_root;

    std::cerr << "Enter a: ";
    std::cin >> a;
    std::cerr << "Enter b: ";
    std::cin >> b;

    plot_graph(func, a, b, COUNT);

    std::cerr << "Enter eps: ";
    std::cin >> eps;

    bool converged;
    size_t steps;

    root = bisection(func, a, b, eps, converged, &steps, MAX_STEPS);

    std::cout << "Method converged: " << converged << '\n';
    std::cout << "Result: x = " << std::setprecision(15) << root << ", steps = " << steps << '\n';

    double x0;
    std::cerr << "Enter x0 for python root(): ";
    std:: cin >> x0;

    std::stringstream command;
    command << "python " << py_prog << ' ' << x0 << ' ' << funcLabel_PY;
    system(command.str().c_str());

    return 0;
}