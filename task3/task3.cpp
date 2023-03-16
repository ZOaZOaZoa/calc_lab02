#include <math.h>
#include <iostream>
#include <iomanip>
#include <conio.h>

#include "../task1/func.h"

const int BEGIN = -3;
const int END = 3;
const size_t COUNT = 30;
std::string f_title = "f(x)";
std::string f_prime_title = "f'(x)";

double f(double x)
{
    return 1.1*pow(x, 3) - 1.9*pow(x, 2) - 2.4*x + 1;
}

double f_prime(double x)
{
    return 3.3*pow(x, 2) - 3.8*x - 2.4;
}

int main()
{
    double x0, x_prime_min, x_prime_max, eps;

    plot_graph(f, BEGIN, END, COUNT, &f_title);
    plot_graph(f_prime, BEGIN, END, COUNT, &f_prime_title);

    std::cerr << "Enter x0: ";
    std::cin >> x0;
    std::cerr << "Enter x value with min derivative value on segment of localisation: ";
    std::cin >> x_prime_min;
    std::cerr << "Enter x value with max derivative value on segment of localisation: ";
    std::cin >> x_prime_max;
    std::cerr << "Enter eps: ";
    std::cin >> eps;
    
    std::cerr << "-------------------------------\n";

    bool converged;
    double res = simple_iteration(f, f_prime, x0, x_prime_min, x_prime_max, eps, &converged, true);
    std::cout << "Result: " << std::setprecision(15) << res << '\n';
    std::cout << "Converged: " << converged << '\n';

    getch();

    return 0;
}