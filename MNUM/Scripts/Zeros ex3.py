def f(x):
    return x**2  - x - 1.2

def fp(x):
    return 2*x - 1

def g(x):
    return 1 + 1.2/x

def gp(x):
    return -1.2/(x**2)

epsilon = 10**-3
x0=4
n=0

while True:
    if (fp(x0)==0):
        print("Condicao necessaria nao encontrada")
        quit()
    med = x0 - f(x0)/fp(x0)
    rel = abs((med - x0)/x0)
    x0 = med
    n += 1
    if rel <= epsilon:
        break

print("Newton:" , n)

n = 0
x0 = 4

while True:
    if abs(gp(x0)) >= 1:
        print("Condicao necessaria nao encontrada")
        quit()
    med = g(x0)
    rel = abs((med-x0)/x0)
    x0 = med
    n += 1
    if rel <= epsilon:
        break

print("Peano: ", n)