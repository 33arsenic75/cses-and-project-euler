def prm(N):
    primes = [2]
    for i in range(3,N+1,2):
        is_prime = True
        for p in primes:
            if i%p == 0:
                is_prime = False
                break
        if is_prime:
            primes.append(i)
    return primes

def is_prime(n):
    if n < 2:
        return False
    for i in range(2,int(n**0.5)+1):
        if n%i == 0:
            return False
    return True

def quad_primes(a,b):
    n = 0
    while(is_prime(n**2 + a*n + b)):
        n+=1
    return n

N = 1000
primes = prm(N)
max_primes = 0
max_a = 0
max_b = 0
for i in primes:
    for j in range(-N,N+1):
        temp = quad_primes(j,i)
        if temp > max_primes:
            max_primes = temp
            max_a = j
            max_b = i

print(max_a, max_b, max_primes, max_a*max_b)
