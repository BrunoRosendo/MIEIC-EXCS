import math

g = 10
c = 15
epsilon = 0.0001
t = 9


def v(m):
    return (g*m/c)*(1- math.e**(-(c/m)*t)) - 35

def a(m):
    return (g/c)*(1-math.e**(-c*t/m)) - (g*t/m)*math.e**(-c*t/m)

def Bissection(f, a, b):
    i = 0
    while True:
        i += 1
        m = (a + b) / 2
        if f(a) * f(m) < 0:
            b = m
        else:
            a = m
        err = abs(b - a)
        if err <= epsilon:
            break
    return (m, i)

def Newton(f, fp, x):
    i = 0
    while True:
        i += 1
        if (fp(x) == 0):
            print("Condiçao necessaria nao encontrada")
            return -1
        nextx = x - f(x)/fp(x)
        if abs(nextx - x) < epsilon:
            return (nextx, i)
        x = nextx
        

print("a) ")
res = Bissection(v, 10, 100)
print("X=", res[0], "\nIter=", res[1])
resN = Newton(v, a, 1)
print("b)")
print("X=", resN[0], "\nIter=", resN[1])