import sys
def isprime(n):
    if n == 2:
        return True
    if n%2 == 0:
        return False
    for i in range(3, int(n**0.5)+1, 2):
        if n%i == 0:
            return False
    return True


N = 1000000
prm = [2]
sum = 2
i = 3
while sum <= N:
    for j in prm:
        if i%j == 0:
            break
        elif j*j > i:
            prm.append(i)
            sum += i
            break
    i+=2

sum = 0
sm = []
for i in prm:
    sum+=i
    sm.append(sum)

n = len(sm)

i = 0
j = n - 1

while i < j:
    if sm[j] - sm[i] > N:
        j -= 1
    elif isprime(sm[j] - sm[i]):
        print(sm[j] - sm[i])
        sys.exit()
    else:
        i += 1