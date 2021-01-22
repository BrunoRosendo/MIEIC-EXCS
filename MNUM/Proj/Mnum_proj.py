import math
import matplotlib.pyplot as plt
import numpy as np
from zerosMNUM import Bissection, Corda, Newton, Peano
from edo import Euler, RK2, RK4
import datetime
import os, psutil

process = psutil.Process(os.getpid())
print("MEMÓRIA: ", process.memory_info().rss)
print()
start_time = datetime.datetime.now()

#Farmaco = Amoxicilina

#given variables
ket = 0.2 # h^-1
tmax = 1.5 # h
dose = 125 # mg per 12 hours
duration = 15*24 # h
vap = 3800 # ml

#calculated/researched variables
meiaVida = 61.3 / 60 #h
maxi = 21.7391304 # integrate((maxi/tmax)*t, t, 0, tmax) + integrate(maxi*%e**(-ket*(t-tmax)), t, 1.5, inf) = dose
decl = maxi / tmax # linear slope

def kaFunction(ka):
    return ka*math.e**(-ka*tmax) - ket*math.e**(-ket*tmax)

def kaDerivate(ka):
    return math.e**(-ka*tmax) - ka*tmax*math.e**(-ka*tmax)

def kaXFunction(ka):
    return ket*math.e**(-ket*tmax)/(math.e**(-ka*tmax))

def kaXDerivate(ka):
    return ket*tmax*math.e**(ka*tmax-ket*tmax)
    

kaBissection = round(Bissection(kaFunction, 0, 0.5, 0.00001), 3)
kaCorda = Corda(kaFunction, 0, 0.5, 0.00001)
kaNewton = round(Newton(kaFunction, kaDerivate, 0, 0.00001), 3)
kaPeano = round(Peano(kaXFunction, kaXDerivate, 0, 0.00001), 3)

print("Ka from bissection: ", kaBissection, "\n")
print("Ka from Corda: ", kaCorda, "\n")
print("Ka from Newton: ", kaNewton, "\n")
print("Ka from peano: ", kaPeano, "\n")

# We can conclude that ka = 0.2

ka = kaNewton




# mg/hour
def D(t):
    if t > duration or t < 0:
        return 0
    
    result = 0
    while (t >= 0):
        if t <= tmax:
            result += decl * t
        else:
            result += maxi * (math.e**(-ket*(t - tmax)))
        t -= 12
    return result
    
    
def dmidt(t, mi, mp):
    return D(t) - ka*mi

def dmpdt(t, mi, mp):
    return ka*mi - ket*mp


# Plot the mi(t) and mp(t) functions and calculate the Qc, for Euler

timecords = []
micords = []
mpcords = []

solEuler = Euler(dmidt, dmpdt, 0, duration + 48, 0, 0, 0.1, timecords, micords, mpcords)

plt.ylabel("mi / mg")
plt.xlabel("(EULER) time / h")
plt.plot(timecords, micords)
plt.show()
plt.ylabel("mp / mg")
plt.xlabel("(EULER) time / h")
plt.plot(timecords, mpcords)
plt.show()

solEulerp = Euler(dmidt, dmpdt, 0, duration + 48, 0, 0, 0.1/2)
solEulerpp = Euler(dmidt, dmpdt, 0, duration + 48, 0, 0, 0.1/4)
qcMiEuler = (solEulerp[0] - solEuler[0]) / (solEulerpp[0] - solEulerp[0])
qcMpEuler = (solEulerp[1] - solEuler[1]) / (solEulerpp[1] - solEulerp[1])
ErrMiEuler = (solEulerpp[0] - solEulerp[0])/(2-1)
ErrMpEuler = (solEulerpp[1] - solEulerp[1])/(2-1)


# Plot the mi(t) and mp(t) functions and calculate the Qc, for RK2

timecords = []
micords = []
mpcords = []

solRK2 = RK2(dmidt, dmpdt, 0, duration + 48, 0, 0, 0.1, timecords, micords, mpcords)

plt.ylabel("mi / mg")
plt.xlabel("(RK2) time / h")
plt.plot(timecords, micords)
plt.show()
plt.ylabel("mp / mg")
plt.xlabel("(RK2) time / h")
plt.plot(timecords, mpcords)
plt.show()


solRK2p = RK2(dmidt, dmpdt, 0, duration + 48, 0, 0, 0.1/2)
solRK2pp= RK2(dmidt, dmpdt, 0, duration + 48, 0, 0, 0.1/4)
qcMiRK2 = (solRK2p[0] - solRK2[0]) / (solRK2pp[0] - solRK2p[0])
qcMpRK2 = (solRK2p[1] - solRK2[1]) / (solRK2pp[1] - solRK2p[1])
ErrMiRK2 = (solRK2pp[0] - solRK2p[0])/(2-1)
ErrMpRK2 = (solRK2pp[1] - solRK2p[1])/(2-1)



# Plot the mi(t) and mp(t) functions and calculate the Qc, for RK4

timecords = []
micords = []
mpcords = []

solRK4 = RK4(dmidt, dmpdt, 0, duration + 48, 0, 0, 0.1, timecords, micords, mpcords)

plt.ylabel("mi / mg")
plt.xlabel("(RK4) time / h")
plt.plot(timecords, micords)
plt.show()
plt.ylabel("mp / mg")
plt.xlabel("(RK4) time / h")
plt.plot(timecords, mpcords)
plt.show()

solRK4p = RK4(dmidt, dmpdt, 0, duration + 48, 0, 0, 0.1/2)
solRK4pp = RK4(dmidt, dmpdt, 0, duration + 48, 0, 0, 0.1/4)
qcMiRK4 = (solRK4p[0] - solRK4[0]) / (solRK4pp[0] - solRK4p[0])
qcMpRK4 = (solRK4p[1] - solRK4[1]) / (solRK4pp[1] - solRK4p[1])
ErrMiRK4 = (solRK4pp[0] - solRK4p[0])/(2-1)
ErrMpRK4 = (solRK4pp[1] - solRK4p[1])/(2-1)


# From here, we print the values of the Qc's

print("Euler:\n", "QcMi=", qcMiEuler, "\nQcMp=", qcMpEuler)
print("Erro Mi: ", ErrMiEuler, "Erro Mp", ErrMpEuler, "\n")

print("RK2:\n", "QcMi=", qcMiRK2, "\nQcMp=", qcMpRK2)
print("Erro Mi: ", ErrMiRK2, "Erro Mp", ErrMpRK2, "\n")

print("RK4:\n", "QcMi=", qcMiRK4, "\nQcMp=", qcMpRK4)
print("Erro Mi: ", ErrMiRK4, "Erro Mp", ErrMpRK4, "\n")



# And then we can plot the D(t) graph

tcords = []
ycords = []

for t in np.linspace(0, duration, num=duration*200): # make sure we have enough values to plot
    y = D(t)
    tcords.append(t)
    ycords.append(y)

plt.xlabel("t / h")
plt.ylabel("massa absorvida / mg h-1")
plt.plot(tcords, ycords)
plt.show()


end_time = datetime.datetime.now()

print("Tempo de execução decorrido: ")
print(end_time - start_time)

process = psutil.Process(os.getpid())
print("MEMÓRIA: ", process.memory_info().rss)

#quit()