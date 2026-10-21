# Problem: Non-Abundant Sums
# File: Non-Abundant Sums.py
# Created: 2024-04-28
# Author: abhinav
# Link:
# Topic: Number Theory, Brute Force
#

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
