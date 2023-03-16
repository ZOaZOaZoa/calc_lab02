import sys
import numpy as np
import matplotlib.pyplot as plt

try:
    input = [float(sys.argv[i]) for i in range(4,len(sys.argv))]
    begin = float(sys.argv[1])
    end = float(sys.argv[2])
    tit = sys.argv[3]
    
    x = np.linspace(begin, end, len(input))

    plt.grid(True)
    plt.plot(x, input, color='blue')
    if tit != '_':
        plt.title(tit)
    plt.show()
except ValueError:
    print('Not a numeric value passed into the program\n')