from scipy.optimize import root
import math
import sys

def f(x):
    return math.tan(x) ** 2 - 28/9*math.tan(x) - math.sqrt(3)

def g(x):
    return math.tan(x) ** 2 - 2*math.tan(x) + 1

if len(sys.argv) < 3:
    print('Not enought arguments')
    exit()

try:
    x0 = float(sys.argv[1])
    funcLabel = sys.argv[2]
    if funcLabel == 'f':
        Q = root(f, x0)
    elif funcLabel == 'g':
        Q = root(g, x0)
    else:
        print('Wrong function label passed as 2 argument')
        exit()

    result = Q.x[0]

    print("Python root result: {:0.10f}\nf(x) = {:0.10f}".format(result, f(result)))

except ValueError:
    print('Not a numeric value passed as 1st argument\n')
    exit()