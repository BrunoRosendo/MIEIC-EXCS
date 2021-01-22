import math

def f1(x, y):
    return 2*x**2+x*y-5*x+1

def f2(x, y):
    return x+3*math.log(x)-y**2

def f1dx(x, y):
    return 4*x+y-5

def f1dy(x, y):
    return x

def f2dx(x, y):
    return 1+3/x

def f2dy(x, y):
    return -2*y

x0 = y0 = 4

while True:
    xa = x0
    ya = y0
    x0 = xa - (f1(xa, ya)*f2dy(xa, ya)-f2(xa, ya)*f1dy(xa, ya))/ (f1dx(xa, ya)*f2dy(xa, ya)-f2dx(xa, ya)*f1dy(xa, ya))
    y0 = ya - (f2(xa, ya)*f1dx(xa, ya)-f1(xa, ya)*f2dx(xa, ya)) / (f1dx(xa, ya)*f2dy(xa, ya)-f2dx(xa, ya)*f1dy(xa, ya))
    precx = abs(xa-x0)
    precy = abs(ya - y0)
    if precx < 0.01 and precy < 0.01:
        print(x0, ", ", y0)
        break