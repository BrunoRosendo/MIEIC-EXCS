def Newton(f, fp, x0):
    while True:
        if (fp(x0)==0 or x0 == 0):
            print("Condicao necessaria nao encontrada")
            quit()
        med = x0 - f(x0)/fp(x0)
        rel = abs(f(med) - f(x0))
        x0 = med
        if rel <= epsilon:
            break
    return med

def f(x):
    return 1 + 5.5*x -4*x**2 + 0.5*x**3

def fp(x):
    return 5.5 -8*x +1.5*x**2

epsilon = 10**-5
a = 4.52
b = 4.54

print(Newton(f, fp, a))
print(Newton(f, fp, b))

# Sao encontrados dois zeros diferentes