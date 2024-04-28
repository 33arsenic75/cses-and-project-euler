def findlargestdig(k):
    n = 1
    while True:
        if 10 * n * (9 ** k) < 10 ** n:
            return n
        n += 1

def digsum(n, k):
    sum = 0
    for c in str(n):
        sum += int(c) ** k
    return sum

N = 5
sum = 0
to_stop = findlargestdig(N)
for i in range(2, 10 ** to_stop+1):
    if i == digsum(i, N):
        print(i)
        sum += i

print(sum)

