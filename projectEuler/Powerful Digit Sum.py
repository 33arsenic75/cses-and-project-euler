# Problem: Powerful Digit Sum
# File: Powerful Digit Sum.py
# Created: 2024-04-29
# Author: abhinav
# Link:
# Topic: Big Integers, Digit Manipulation
#

def digitsum(a,b):
    return sum([int(i) for i in str(a**b)])

print(max([digitsum(a,b) for a in range(1,100) for b in range(1,100)]))