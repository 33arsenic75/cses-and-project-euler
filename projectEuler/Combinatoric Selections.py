def ncr(n,r):
    ans = 1
    for i in range(n-r+1,n+1):
        ans *= i    
    for i in range(1,r+1):
        ans //= i
    return ans


N = 100
B = 1000000
dic = {}

for n in range(1,N+1):
    dic[n] = 0
    for r in range(0,n//2):
        if ncr(n,r) > B:
            dic[n] = n + 1 - 2*r
            break

print(sum(dic.values()))