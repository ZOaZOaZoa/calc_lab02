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

    //Used to bring main console window to front by SetForegroundWindow()
    #undef _WIN32_WINNT
    #define _WIN32_WINNT 0x0500
    HWND hwnd = GetConsoleWindow();

    //Calculated ordinates are exported to python script to plot
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

double bisection(double f(double), double left, double right, double eps, bool& converged, size_t* steps, size_t max_iter)
{
    converged = false;
    if( f(left)*f(right)>0)
    {
        return 0;
    }

    //Negator is for function always having -+ way changing sign
    int negator;
    if(f(left) > 0)
    {
        negator = -1;
    }
    else
    {
        negator = 1;
    }

    std::vector<double> x(max_iter);
    x[0] = (left+right)/2;

    size_t n = 1;
    bool end_cond = false;
    do
    {
        
        //negator*f(x[n-1]) < 0 ? left = x[n-1] : right = x[n-1];
        if(negator*f(x[n-1]) < 0)
        {
            left = x[n-1];
        }
        else
        {
            right = x[n-1];
        }
        x[n] = (left+right)/2;

        if( abs(x[n]-x[n-1]) < 1e-14)
        {
            n++;
            break;
        }

        //std::cout << "step: " << n << " x: " << x[n] << '\n';

        end_cond = (right-left)<2*eps;

    } while ( !end_cond && ++n < max_iter);

    if(end_cond)
    {
        converged = true;
    }

    *steps = n-1;
    return x[n-1];
}