# Problem: Power Digit Sum
# File: PowerDigitSum.py
# Created: 2024-04-15
# Author: abhinav
# Link:
# Topic: Big Integers, Digit Manipulation
#

def sumdig(n):
    ans = 0
    while(n>0):
        ans+=(n%10)
        n//=10
    return ans

for i in range(1000,1001):
    temp = pow(2,i)
    print(i,sumdig(temp))