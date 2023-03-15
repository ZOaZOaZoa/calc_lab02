#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>

const double BEGIN = -3;
const double END = 3;
const size_t COUNT = 30;
std::string plot_program = "../plotter.py";
std::string newton_program = "newtoncheck.py";

double f(double x)
{
    return 1.1*pow(x, 3) - 1.9*pow(x, 2) - 2.4*x + 1;
}

std::vector<double> linspace(double start, double end, size_t count)
{
    std::vector<double> res(count);
    double step = (end - start)/(count - 1);
    for(int i = 0; i < count; i++)
    {
        res[i] = start + i*step;
    }

    return res;
}

void plot_graph(double func(double), double begin, double end, size_t pts_count)
{
    std::stringstream command;
    command << "python " << plot_program << ' ' << begin << " " << end << " ";
    
    std::vector<double> vals(pts_count);
    auto x = linspace(begin, end, pts_count);

    for(int i = 0; i < x.size(); i++)
    {
        vals[i] = func(x[i]);
        command << vals[i] << ' ';
    }

    //Calculated ordinates are exported to python script to plot
    system(command.str().c_str());
}

int main()
{
    //Calling python script to draw a plot
    plot_graph(f, BEGIN, END, COUNT);

    std::cout << "Enter x0: ";
    double x0;
    std::cin >> x0;
    std::cout << "Enter eps: ";
    double eps;
    std::cin >> eps;

    
    std::stringstream command;
    command << "python " << newton_program << ' ' << x0 << ' ' << eps;
    system(command.str().c_str());


    return 0;
}