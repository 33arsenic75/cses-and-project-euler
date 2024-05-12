prm = [2]
N = 10**7
for i in range(3, N, 2):
    for j in prm:
        if j*j > i:
            prm.append(i)
            break
        elif i%j == 0:
            break


def is_permutation(a, b):
    return sorted(str(a)) == sorted(str(b))

def tot(n):
    if n == 1:
        return 1
    for i in prm:
        if n%i == 0:
            n = (n/i)*(i-1)
        elif(i>n):
            break
    return int(n)


dic = {}
ans = 10*7
for i in range(2,N):
    x = tot(i)
    if is_permutation(i, x):
        ans = min(ans, i/x)
print(ans)
# print(min(dic, key=dic.get))

            