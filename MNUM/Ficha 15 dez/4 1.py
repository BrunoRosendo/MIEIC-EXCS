anal = 0.79124
print("Anal Integral: ", anal)

f = [2, 1.721, 1.482, 1.275, 1.098, 0.945, 0.813]
h = 0.1
soma = 0

for i in range(len(f)):
    soma += f[i]
    if (i != 0 and i != len(f) - 1):
        soma += f[i]

trap = (h/2) * soma
errTrap = abs((anal-trap)/trap)

print("Trapezio: ", trap, " Erro: ", errTrap)


somaSimpson = f[0] + f[len(f) - 1]

for i in range(1, len(f) - 1):
    if (i % 2 == 0):
        somaSimpson += 2*f[i]
    else:
        somaSimpson += 4*f[i]


simp = (h/3) * somaSimpson
errSimp = abs((anal - simp)/simp)

print("Simpson: ", simp, "Erro: ", errSimp)

