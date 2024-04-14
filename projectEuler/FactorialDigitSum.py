def fac(n):
    if n < 2:
        return 1
    return n * fac(n-1)

def sumdig(n):
    ans = 0
    while(n>1):
        ans+=(n%10)
        n//=10
    return ans

print(sumdig(fac(100)))