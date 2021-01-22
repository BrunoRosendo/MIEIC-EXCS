# Functions to solve EDOs with 3 variables

def Euler(yp, zp, x0, xf, y0, z0, h, xlist = [], ylist = [], zlist = []):
    nEuler = 0
    y = y0
    z = z0
    while (round(x0, 2) < xf):
        nEuler += 1
        xlist.append(x0)
        ylist.append(y)
        zlist.append(z)
        ya = y
        y = y + yp(x0, y, z) * h
        z = z + zp(x0, ya, z)*h
        x0 += h
    print("Euler iterations: ", nEuler)
    return (y, z)

def RK2(yp, zp, x0, xf, y0, z0, h, xlist = [], ylist = [], zlist = []):
    nRK2 = 0
    y = y0
    z = z0
    while (round(x0, 2) < xf):
        nRK2 += 1
        xlist.append(x0)
        ylist.append(y)
        zlist.append(z)
        ya = y
        y = y + h*yp(x0 + h/2, y + (h/2)*yp(x0, y, z), z + (h/2)*zp(x0, y, z))
        z = z + h*zp(x0 + h/2, ya + (h/2)*yp(x0, ya, z), z + (h/2)*zp(x0, ya, z))
        x0 += h
    print("RK2 iterations: ", nRK2)
    return (y, z)

def RK4(yp, zp, x, xf, y, z, h, xlist = [], ylist = [], zlist = []):
    nRK4 = 0
    while round(x, 2) < xf:
        nRK4 += 1
        xlist.append(x)
        ylist.append(y)
        zlist.append(z)
        yd1 = h*yp(x, y, z)
        zd1 = h*zp(x, y, z)
        yd2 = h*yp(x + h/2, y + yd1/2, z + zd1/2)
        zd2 = h*zp(x + h/2, y + yd1/2, z + zd1/2)
        yd3 = h*yp(x + h/2, y + yd2/2, z + zd2/2)
        zd3 = h*zp(x + h/2, y + yd2/2, z + zd2/2)
        yd4 = h*yp(x + h, y + yd3, z + zd3)
        zd4 = h*zp(x + h, y + yd3, z + zd3)

        y = y + yd1/6 + yd2/3 + yd3/3 + yd4/6
        z = z + zd1/6 + zd2/3 + zd3/3 + zd4/6
        x += h
    print("RK4 iterations: ", nRK4)
    return (y, z)