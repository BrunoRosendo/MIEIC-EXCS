
def f1(x2, x3):
    return (27 - 2*x2 + x3) / 10

def f2(x1, x3):
    return (-3*x1 + 2*x3 + 61.5)/6

def f3(x1, x2):
    return (-21.5 - x1 - x2)/5

def GaussJacobi(f1, f2, f3, x1, x2, x3):
    i = 0
    while True:
        i += 1
        x1a = x1
        x2a = x2
        x1 = f1(x2, x3)
        x2 = f2(x1a, x3)
        x3 = f3(x1a, x2a)
        if i == 3:
            return (x1, x2, x3)

def GaussSeidel(f1, f2, f3, x1, x2, x3):
    i = 0
    while True:
        i += 1
        x1 = f1(x2, x3)
        x2 = f2(x1, x3)
        x3 = f3(x1, x2)
        if i == 3:
            return (x1, x2, x3)

print("Jacobi: ", GaussJacobi(f1, f2, f3, 0, 0, 0))
print("Seidel: ", GaussSeidel(f1, f2, f3, 0, 0, 0))