#include <math.h>
#include <iostream>
#include <iomanip>
#include <conio.h>

#include "../task1/func.h"

const size_t COUNT = 30;
const size_t MAX_STEPS = 1000;
std::string py_prog = "pyfiles/root.py";


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

    double (*func)(double);
    char funcLabel_PY;
    char ans;
    std::cerr << "What func to use? f or g: ";
    std::cin >> ans;

    //Choose function to analys
    if(ans == 'f')
    {
        func = f;
        funcLabel_PY = 'f';
    }
    else if (ans == 'g')
    {
        func = g;
        funcLabel_PY = 'g';
    }
    else
    {
        std::cerr << "Wrong input\n";
        return 0;
    }

    //Input segment of localisation to work with
    std::cerr << "Enter a: ";
    std::cin >> a;
    std::cerr << "Enter b: ";
    std::cin >> b;

    plot_graph(func, a, b, COUNT);

    std::cerr << "Enter eps: ";
    std::cin >> eps;

    //In converged will be saved info about convergance of method
    bool converged;
    size_t steps;

    root = bisection(func, a, b, eps, converged, &steps, MAX_STEPS);

    std::cout << "Method converged: " << converged << '\n';
    std::cout << "Result: x = " << std::setprecision(15) << root << ", steps = " << steps << '\n';

    //Input for python method
    double x0;
    std::cerr << "Enter x0 for python root(): ";
    std:: cin >> x0;

    //Call a python root()
    std::stringstream command;
    command << "python " << py_prog << ' ' << x0 << ' ' << funcLabel_PY;
    system(command.str().c_str());

    getch();

    return 0;
}