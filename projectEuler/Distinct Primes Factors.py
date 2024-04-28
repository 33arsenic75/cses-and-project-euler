def prm(N):
    prime = [2]
    for i in range(3, N+1, 2):
        for j in prime:
            if i % j == 0:
                break
            if j*j > i:
                prime.append(i)
                break
    return prime


def numfactor(n, primes):
    factors = set()
    for p in primes:
        if p*p > n:
            break
        while n % p == 0:
            factors.add(p)
            n //= p
    if n > 1:
        factors.add(n)
    return len(factors)

p = prm(1000)
i = 1
while True:
    if numfactor(i, p) == 4:
        if numfactor(i+1, p) == 4:
            if numfactor(i+2, p) == 4:
                if numfactor(i+3, p) == 4:
                    print(i)
                    break
                else:
                    i+=4
            else:
                i+=3
        else:
            i+=2   
    else:                
        i+=1