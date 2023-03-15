#include <math.h>
#include <iostream>
#include <iomanip>

#include "../task1/func.h"

const size_t COUNT = 30;
const size_t MAX_STEPS = 1000;

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

    plot_graph(f, a, b, COUNT);

    std::cerr << "Enter eps: ";
    std::cin >> eps;

    bool converged;
    size_t steps;

    root = bisection(f, a, b, eps, converged, &steps, MAX_STEPS);

    std::cout << "Method converged: " << converged << '\n';
    std::cout << "Result: x = " << std::setprecision(15) << root << ", steps = " << steps << '\n';

    return 0;
}