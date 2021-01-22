import math

anal = 0.79124

def f(x):
    return 2*math.e**(-1.5*x)

def Trap(f, x0, xf, h):
    soma = f(x0) + f(xf)
    while (round(x0, 5) < xf - h):
        x0 += h
        soma += 2*f(x0)
    soma = (h/2)*soma
    return soma

def Simpson(f, x0, xf, h):
    soma = f(x0) + f(xf)
    i = 0
    while (round(x0, 5) < xf - h):
        i += 1
        x0 += h
        if (i % 2 == 0):
            soma += 2*f(x0)
        else:
            soma += 4*f(x0)
    soma = (h/3)*soma
    return soma


trap = Trap(f, 0, 0.6, 0.15)
trapd = Trap(f, 0, 0.6, 0.15/2)
trapdd = Trap(f, 0, 0.6, 0.15/4)
qc = (trapd-trap)/(trapdd-trapd)
errtrap = (trapdd-trapd)/(4-1)

simp = Simpson(f, 0, 0.6, 0.15)
simpd = Simpson(f, 0, 0.6, 0.15/2)
simpdd = Simpson(f, 0, 0.6, 0.15/4)
qcsimp = (simpd-simp)/(simpdd-simpd)
errsimp = (simpdd-simpd)/(16-1)

print("Trapezio: ", trap, "Sp: ", trapd, "Spp: ", trapdd, "Qc: ", qc, "Erro: ", errtrap)
print()
print("Simpson: ", simp, "Sp: ", simpd, "Spp: ", simpdd, "Qc: ", qcsimp, "Erro: ", errsimp)