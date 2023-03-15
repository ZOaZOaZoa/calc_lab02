#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <conio.h>


#include "func.h"

const double BEGIN = -3;
const double END = 3;
const size_t COUNT = 30;


double f(double x)
{
    return 1.1*pow(x, 3) - 1.9*pow(x, 2) - 2.4*x + 1;
}


int main()
{
    //Calling python script to draw a plot
    
    plot_graph(f, BEGIN, END, COUNT);

    std::cerr << "Enter x0: ";
    double x0;
    std::cin >> x0;
    std::cerr << "Enter eps: ";
    double eps;
    std::cin >> eps;

    newton(x0, eps);

    getch();


    return 0;
}