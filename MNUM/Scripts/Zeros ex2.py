import math

def f(x):
    return 5.5*x**2 + 6.2*x - 2.1

epsilon = 10**-3

n1 = n2 = n3 = n4 = n5 = n6 = n7 = n8 = 0
a=-2
b=-1
while True:
    med = (a+b)/2
    if f(med)*f(a) < 0:
        b = med
    else:
        a = med
    rel = abs(b-a)
    if rel <= epsilon:
        break
    n1 += 1

a=-2
b=-1

while True:
    med = (a+b)/2
    if f(med)*f(a) < 0:
        b = med
    else:
        a = med
    rel = abs((b-a)/a)
    if rel <= epsilon:
        break
    n2 += 1
print(med)

a=-2
b=-1
bef = a
while True:
    med = (a+b)/2
    if f(med)*f(a) < 0:
        b = med
    else:
        a = med
    rel = abs(med - bef)
    if rel <= epsilon:
        break
    n3 += 1
    bef = med

print(med)
a=-2
b=-1
bef = a
while True:
    med = (a+b)/2
    if f(med)*f(a) < 0:
        b = med
    else:
        a = med
    rel = abs((med - bef)/med)
    if rel <= epsilon:
        break
    n4 += 1
    bef = med

print(med)
print("Metodo 1: ", n1, " ", n2, " ", n3, " ", n4, "\n")

a=-2
b=-1
#while True:
 #   med = (f(b)*a - f(a)*b)/(f(b)-f(a))
  #  if f(med)*f(a) < 0:
   #     b = med
    #else:
     #   a = med
    #rel = abs(b-a)
    #if rel <= epsilon:
  #      break
   # n5 += 1

print("not possible")

a=-2
b=-1
#while True:
 #   med = (f(b)*a - f(a)*b)/(f(b)-f(a))
  #  if f(med)*f(a) < 0:
   #     b = med
    #else:
  #      a = med
   # rel = abs((b-a)/a)
    #if rel <= epsilon:
   #     break
   # n6 += 1

print("not possible")

a=-2
b=-1
bef = a
while True:
    med = (f(b)*a - f(a)*b)/(f(b)-f(a))
    if f(med)*f(a) < 0:
        b = med
    else:
        a = med
    rel = abs(med - bef)
    if rel <= epsilon:
        break
    bef = med
    n7 += 1

print(med)

a=-2
b=-1
bef = a
while True:
    med = (f(b)*a - f(a)*b)/(f(b)-f(a))
    if f(med)*f(a) < 0:
        b = med
    else:
        a = med
    rel = abs((med - bef)/med)
    if rel <= epsilon:
        break
    bef = med
    n8 += 1

print(med)

print("Metodo 2: ", n5, " ", n6, " ", n7, " ", n8, "\n")