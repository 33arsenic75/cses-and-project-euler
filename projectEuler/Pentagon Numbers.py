import sys
def ispent(n):
    return ((1+(1+24*n)**0.5)/6).is_integer()

def pent(n):
    return n*(3*n-1)//2

for i in range(1, 10000):
    for j in range(i+1, 10000):
        if ispent(pent(j) - pent(i)) and ispent(pent(j) + pent(i)):
            print(pent(j)-pent(i))
            sys.exit()