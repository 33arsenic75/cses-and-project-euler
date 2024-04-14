N = 10000

def sumdiv(n):
    ans = 0
    for i in range(1,n):
        if(n%i==0):
            ans+=i
    mem[n] = ans
global mem
mem = {}
for i in range(1,N+1):
    sumdiv(i)

sum = 0
for i in range(1,N+1):
    for j in range(i+1,N+1):
        if(mem[i]==j and mem[j]==i):
            sum +=i+j

print(sum)