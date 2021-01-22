import math

def g1(x, y):
    return ((x*y+5*x-1)/2)**0.5

def g2(x, y):
    return (x+3*math.log(x))**0.5

def g1x(x, y):
    return (0.35*(y+5))/(x*y+5*x-1)**0.5

def g1y(x, y):
    return (0.35*x)/(x*y+5*x-1)**0.5

def g2x(x, y):
    return (0.5*(3/x+1))/(3*math.log(x)+x)**0.5

def g2y(x, y):
    return 0

x0 = 4
y0 = 4



if abs(g1x(x0, y0)) + abs(g2x(x0, y0)) >= 1 or abs(g1y(x0, y0)) + abs(g2y(x0, y0)) >= 1:
    print("Criterio de convergencia nao encontrado\n")
    quit()


while True:
    xa = x0
    ya = y0
    x0 = g1(x0, y0)
    y0 = g2(xa, y0)
    precx = abs(x0 - xa)
    precy = abs(y0-ya)
    if precx < 0.01 and precy < 0.01:
        print("x: ", x0, " y: ", y0)
        break
