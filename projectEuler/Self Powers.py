# Problem: Self Powers
# File: Self Powers.py
# Created: 2024-04-28
# Author: abhinav
# Link:
# Topic: Modular Arithmetic
#

M = 10**10

dic = {i: pow(i,i,M) for i in range(1, 1000+1)}

print(sum(dic[i] for i in range(1, 1000+1)) % M)


# (10 + 1)^11 = 11C1* 10