def sumdig(n):
    ans = 0
    while(n>0):
        ans+=(n%10)
        n//=10
    return ans

for i in range(1000,1001):
    temp = pow(2,i)
    print(i,sumdig(temp))