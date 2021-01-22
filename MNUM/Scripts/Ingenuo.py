import math 

start = math.exp(-1)

for i in range(1, 26):
    start = start * i -1
    print(start)