import numpy as np
from math import cos, sin
import matplotlib.pyplot as plt

g = 1
l = 1

def Euler_method(theta0, vel0, dt, n):
    # Init arrays
    theta = np.zeros(n+1)
    vel = np.zeros(n+1)
    
    # Starting values
    theta[0] = theta0
    vel[0] = vel0
    
    #calculate theta and velocity
    for i in range(0, n):
        theta[i + 1] = theta[i] + dt * vel[i]
        vel[i + 1] = vel[i] + dt * (-g/l*sin(theta[i]))
                                       
    return theta, vel
