import sys

class Fraction:
    def __init__(self, numerator, denominator):
        self.numerator = numerator
        self.denominator = denominator
        
    def __str__(self):
        return f"{self.numerator}/{self.denominator}"
    
    def simplify(self):
        gcd = self.gcd(self.numerator, self.denominator)
        self.numerator //= gcd
        self.denominator //= gcd
        return self
        
    @staticmethod
    def gcd(a, b):
        while b:
            a, b = b, a % b
        return a
    
    def __add__(self, other):
        new_numerator = self.numerator * other.denominator + other.numerator * self.denominator
        new_denominator = self.denominator * other.denominator
        return Fraction(new_numerator, new_denominator).simplify()
    
    def __sub__(self, other):
        new_numerator = self.numerator * other.denominator - other.numerator * self.denominator
        new_denominator = self.denominator * other.denominator
        return Fraction(new_numerator, new_denominator).simplify()
    
    def __mul__(self, other):
        new_numerator = self.numerator * other.numerator
        new_denominator = self.denominator * other.denominator
        return Fraction(new_numerator, new_denominator).simplify()
    
    def __truediv__(self, other):
        new_numerator = self.numerator * other.denominator
        new_denominator = self.denominator * other.numerator
        return Fraction(new_numerator, new_denominator).simplify()



# 2 1 2 1 1 4 1  
def ans(N):
    # Initialize the continued fraction for e
    e_continued_fraction = [2]
    for k in range(1, N):
        e_continued_fraction.extend([1, 2*k, 1])

    e_continued_fraction = e_continued_fraction[:N]
    temp = Fraction(e_continued_fraction[-1], 1)
    for i in range(N-2, -1, -1):
        n = e_continued_fraction[i]
        temp = (Fraction(1,1)/temp) + Fraction(n, 1)
    print(temp)
    return temp

def sumdigits(n):
    return sum([int(i) for i in str(n)])

N = 100
print(sumdigits(str(ans(N).numerator)))


