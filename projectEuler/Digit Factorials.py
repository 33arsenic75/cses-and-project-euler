def fac(n):
    return 1 if n == 0 else n * fac(n - 1)

def limit():
    temp = fac(9)
    n = 1
    while(temp*n >= 10**(n - 1)):
        n += 1
    return n

fc = {i:fac(i) for i in range(10)}
lim = limit()

ans = 0
for i in range(10,10**lim):
    if i == sum(fc[int(j)] for j in str(i)):
        ans+=i
        print(i)