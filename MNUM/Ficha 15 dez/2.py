
def g1(x, y):
    return -x**2 + x + 0.75

def g2(x, y):
    return (x**2 - y)/(5*y) # errado na ficha

def g1dx(x, y):
    return -2*x + 1

def g1dy(x, y):
    return 0

def g2dx(x, y):
    return (2/5)*x

def g2dy(x, y):
    return -1/5

x = y = 1.2
i = 0

if abs(g1dx(x, y) + g2dx(x, y)) >= 1 or abs(g1dy(x, y) + g2dy(x, y)) >= 1:
        print("Criterio de convergencia nao encontrado")

while True:
    i += 1
    xguess = g2(x, y)
    yguess = g1(x, y)
    x = xguess
    y = yguess
    if i == 6:
        print("Result=", (x, y))
        break