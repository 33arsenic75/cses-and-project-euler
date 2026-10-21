# Problem: Factorial Digit Sum
# File: FactorialDigitSum.py
# Created: 2024-04-15
# Author: abhinav
# Link:
# Topic: Big Integers, Digit Manipulation
#

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