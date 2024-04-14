N = 1000000

mem = {1:1}
def solve(n):
    if n in mem:
        return mem[n]
    elif n%2 == 0:
        mem[n] = 1 + solve(n/2)
    else:
        mem[n] =  1 + solve(3*n+1)
    return mem[n]
    
for i in range(1,N+1):
    solve(i)

max_pair = max(mem.items(), key=lambda x: x[1])
print(max_pair)