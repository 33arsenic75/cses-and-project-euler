# Problem: Highly Divisible Triangular Number
# File: HighlyDivisibleTriangularNumber.py
# Created: 2024-04-15
# Author: abhinav
# Link:
# Topic: Number Theory
#

mem={}
def factor(n):
    if n in mem:
        return mem[n]
    else:
        i = 1
        ans = 0
        while(i*i < n):
            if(n%i==0):
                ans+=2
            i+=1
        if(i*i == n):
            ans+=1
    mem[n]=ans
    return ans

idx = 10000
while(True):
    if(factor(idx*(idx+1)/2)>=500):
        print(idx*(idx+1)/2)
        break
    idx+=1

# for key in mem:
#     print(key,mem[key])
