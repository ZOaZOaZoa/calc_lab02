#include "func.h"

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
    command << "start cmd.exe @cmd /k python " << plot_program << ' ' << begin << " " << end << " ";
    
    std::vector<double> vals(pts_count);
    auto x = linspace(begin, end, pts_count);

    for(int i = 0; i < x.size(); i++)
    {
        vals[i] = func(x[i]);
        command << vals[i] << ' ';
    }

    //Calculated ordinates are exported to python script to plot
    #undef _WIN32_WINNT
    #define _WIN32_WINNT 0x0500
    HWND hwnd = GetConsoleWindow();

    system(command.str().c_str());
    Sleep(2000);
    SetForegroundWindow(hwnd);
}

void newton(double x0, double eps)
{
    std::stringstream command;
    command << "python " << newton_program << ' ' << x0 << ' ' << eps;
    system(command.str().c_str());
}