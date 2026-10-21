# Problem: 1000-digit Fibonacci Number
# File: 1000digitFibonacciNumber.py
# Created: 2024-04-15
# Author: abhinav
# Link:
# Topic: Big Integers
#

from math import sqrt
import math
N = 1000
a = (1 + sqrt(5))/2
b = (1 - sqrt(5))/2
i = 1
logc = math.log10(5)/2 + N - 1
loga = math.log10(a)
ans = logc/loga
print(ans)
