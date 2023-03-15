import matplotlib as plt
import numpy as np
from scipy.optimize import newton
import sys

def f(x):
    return 1.1*x**3-1.9*x**2-2.4*x+1
def df(x):
    return 3.3*x**2-3.8*x-2.4

if len(sys.argv) < 3:
    print('Not enough arguments. Excpected: x0, eps\n')
    sys.exit()

try:
    x0 = float(sys.argv[1])
    eps = float(sys.argv[2])
    res1 = newton(f, x0, tol=eps, full_output=True)
    res2 = newton(f, x0, tol=eps, full_output=True, fprime=df)

    print("Метод секущих:\n", res1)
    print("Метод Ньютона:\n", res2)
except ValueError:
    print('Not a numeric value passed into the program\n')
    