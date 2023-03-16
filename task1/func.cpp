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

void plot_graph(double func(double), double begin, double end, size_t pts_count, std::string* title)
{
    std::stringstream command;
    command << "start cmd.exe @cmd /k python " << plot_program << ' ' << begin << " " << end << " ";
    
    std::vector<double> vals(pts_count);
    auto x = linspace(begin, end, pts_count);

    if ( title != nullptr) 
    {
        command << " \"" << *title << "\" ";
    } 
    else
    {
        command << " _ ";
    }

    for(int i = 0; i < x.size(); i++)
    {
        vals[i] = func(x[i]);
        command << vals[i] << ' ';
    }

    //Calculated ordinates are exported to python script to plot
    system(command.str().c_str());
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
    double end_const = 2*eps;
    do
    {
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


        end_cond = (right-left)<end_const;

    } while ( !end_cond & ++n < max_iter);

    if(end_cond)
    {
        converged = true;
    }

    *steps = n-1;
    return x[n-1];
}

double simple_iteration(double f(double), double f_prime(double), double x0, double x_prime_min, double x_prime_max, double eps, bool* converged, bool prompt, size_t max_iter)
{

    double m, M, alpha, q;

    m = f_prime(x_prime_min);
    M = f_prime(x_prime_max);

    if (m*M<=0)
    {
        *converged = false;
        return 0;
    }

    //Negates function to work with positive derivative
    int negator = 1;
    if (m < 0)
    {
        negator = -1;
    }

    m *= negator;
    M *= negator;

    alpha = 2/(m+M);
    q = (M-m)/(m+M);

    if(prompt)
    {
        std::cout << "m = " << m << ", M = " << M << ", alpha = " << alpha << " q = " << q << '\n';
    }

    std::vector<double> x(max_iter);
    x[0] = x0;

    int n = 1;
    bool end_cond = false;
    double end_const = (1-q)/q * eps;
    if(prompt)
    {
        std::cout << "n\t" << std::setw(20) << "x_n" << std::setw(17) << "Estimated delta" << std::setw(15) << "decreased in\n";
    }
    do
    {
        x[n] = x[n-1] - alpha*negator*f(x[n-1]);

        if(prompt)
        {
            std::cout << n << '\t' << std::setw(20) << std::setprecision(15) << x[n];
        }
        if(prompt && n > 1)
        {
            double delta = q/(1-q)*abs(x[n] - x[n-1]);
            double decrease_coeff = abs(x[n] - x[n-1]) / abs(x[n-1] - x[n-2]);
            std::cout << std::setw(17) << std::scientific << std::setprecision(5) << delta;
            std::cout << std::setw(15) << std::fixed << std::setprecision(7) << decrease_coeff << '\n';
        }
        else
        {
            std::cout << '\n';
        }

        end_cond = abs(x[n] - x[n-1]) < end_const;
    } while (!end_cond & ++n < max_iter);
    
    if (end_cond)
    {
        *converged = true;
    }

    return x[n-1];
}