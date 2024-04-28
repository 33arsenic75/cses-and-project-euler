def abundantnumber(n):
    sum = 0
    for i in range(1, n//2 + 1):
        if(n % i == 0):
            sum += i
    return sum > n

N = 28123


dic = {}
for i in range(1, N+1):
    dic[i] = abundantnumber(i)

sum = 0
for n in range(1, N+1):
    for i in range(1, n//2 + 1):
        if(dic[i] and dic[n-i]):
            break
    else:
        sum += n
print(sum)
