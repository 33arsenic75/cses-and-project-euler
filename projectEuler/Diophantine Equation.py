import sys
from math import sqrt

def obtenerFraccionContinua(A, x):
    a0 = int(sqrt(x))
    d = 1
    m = 0
    a = 0

    prim = True

    if a0*a0 != x:
        while (a != 2*a0):
            m = d*a - m;
            d = (x - m * m) / d;
            a = int((a0 + m) / d);
            if not prim:
                A.append(a)
            prim = False


def result(A, num, den, i, maximo):
    if (i >= maximo):
        return num*A[i] + 1, A[i]
    else:
        rnum, rden = result(A, den, A[i+1], i+1, maximo)
        num = num*rnum + rden
        den = rnum
        return num, den


def pell(d):
    A = []
    if d >= 0:
        a0 = int(sqrt(d))
        obtenerFraccionContinua(A, d)

    longCiclo = len(A)-1
    p=1
    q=0

    if longCiclo > 0:
        if longCiclo%2 == 0:
            p, q = result(A, A[0], A[1], 1, longCiclo-2)
        else:
            A += A[1:] +A[1:]
            p, q = result(A, A[0], A[1], 1, 2*longCiclo-1)

    return p,q

dic = {}
N = 1000
# N = 10
for i in range(1,N+1):
    if int(sqrt(i))**2 != i:
        dic[i] = pell(i)

print(max(dic, key=lambda x: dic[x][0]))
print(dic[661])