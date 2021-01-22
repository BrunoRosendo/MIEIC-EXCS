import math
import sys

epsilon = 10**-4

def f(x):
    return x-2*math.log(x)-5

def fp(x):
    return 1-2/x

def g(x):
    return 2*math.log(x)+5

def gp(x):
    return 2/x

def g2(x):
    return math.e**((x-5)/2)

def g2p(x):
    return (1/2)*math.e**((x-5)/2)

def Bissection(f, a, b):
    while True:
        med = (a+b)/2
        if f(med)*f(a) < 0:
            b = med
        else:
            a = med
        rel = abs((b-a)/a)
        if rel <= epsilon:
            break
    return med


def Corda(f, a, b):
    while True:
        med = (f(b)*a - f(a)*b)/(f(b)-f(a))
        if f(med)*f(a) < 0:
            b = med
        else:
            a = med
        rel = abs((b-a)/a)
        if rel <= epsilon:
            break
    return med

def Newton(f, fp, x0):
    while True:
        if (fp(x0)==0 or x0 == 0):
            print("Condicao necessaria nao encontrada")
            quit()
        med = x0 - f(x0)/fp(x0)
        rel = abs((med - x0)/x0)
        x0 = med
        if rel <= epsilon:
            break
    return med

def Peano(g, gp, x0):
    while True:
        if abs(gp(x0)) >= 1:
            print("Condicao necessaria nao encontrada")
            quit()
        med = g(x0)
        rel = abs((med-x0)/x0)
        x0 = med
        if rel <= epsilon:
            break
    return med

print("Bissection:\n")
print("First zero: ", Bissection(f, 0.03, 1), "\nSecond Zero: ", Bissection(f, 9, 10))
print("Corda:\n")
print("First Zero: ", Corda(f, 0.03, 0.1), "\nSecond Zero: ", Corda(f, 9, 10))
print("Newton: \nFirst Zero: ", Newton(f, fp, 0.03), "\nSecond Zero: ", Newton(f, fp, 10))
#Why doesn't 1 or 2 work??
print("Peano:\nFirst Zero: ", Peano(g2, g2p, 0.03), "\nSecond Zero: ", Peano(g, gp, 9.5))

