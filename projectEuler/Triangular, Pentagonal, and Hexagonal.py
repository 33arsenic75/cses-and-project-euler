# Problem: Triangular, Pentagonal, and Hexagonal
# File: Triangular, Pentagonal, and Hexagonal.py
# Created: 2024-04-28
# Author: abhinav
# Link:
# Topic: Math, Brute Force
#

import math

def ispen(a):
    if (math.sqrt(1+24*a))**2 == 24*a+1:
        return (math.sqrt(1+24*a)+1)%6 == 0
    return False

def ishex(a):
    if (math.sqrt(1+8*a))**2 == 8*a+1:
        return (math.sqrt(1+8*a)+1)%4 == 0
    return False

def tri(n):
    return n*(n+1)/2    

i = 286
while(True):
    if ispen(tri(i)) and ishex(tri(i)):
        print(tri(i))
        break
    i += 1
