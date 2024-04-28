def sum(n):
    if (n == 1):
        return 1
    return 4*n*n - 6*(n-1) + sum(n-2)

N = 1001
print(sum(N))