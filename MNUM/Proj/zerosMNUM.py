# Functions to calculate zeros

def Bissection(f, a, b, epsilon):
    nBissection = 0
    while True:
        nBissection += 1
        med = (a+b)/2
        count = f(med)*f(a)
        if count < 0:
            b = med
        else:
            a = med
        rel = abs(b-a)
        if rel <= epsilon:
            print("Bissection iterations: ", nBissection)
            break
    return med


def Corda(f, a, b, epsilon):
    nCorda = 0
    while True:
        nCorda += 1
        med = (f(b)*a - f(a)*b)/(f(b)-f(a))
        if f(med)*f(a) < 0:
            b = med
        else:
            a = med
        rel = abs(b-a)
        if rel <= epsilon:
            print("Corda Iterations: ", nCorda)
            break
    return med


def Newton(f, fp, x0, epsilon):
    nNewton = 0
    while True:
        nNewton += 1
        if (fp(x0)==0):
            print("Condicao necessaria nao encontrada para Newton")
            return 0
        med = x0 - f(x0)/fp(x0)
        rel = abs(med - x0)
        x0 = med
        if rel <= epsilon:
            print("Newton iterations: ", nNewton)
            break
    return med


def Peano(g, gp, x0, epsilon):
    nPeano = 0
    while True:
        nPeano += 1
        if abs(gp(x0)) >= 1:
            print("Condicao necessaria nao encontrada")
            return 0
        med = g(x0)
        rel = abs(med-x0)
        x0 = med
        if rel <= epsilon:
            print("Peano iterations: ", nPeano)
            break
    return med