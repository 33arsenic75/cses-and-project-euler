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



def get_continued_fraction(n):
    lst = [1]
    for i in range(1, n):
        lst.append(2)
    return lst

def ans(N):
    # Initialize the continued fraction for e
    continued_fraction = get_continued_fraction(N)
    continued_fraction = continued_fraction[:N]
    temp = Fraction(continued_fraction[-1], 1)
    for i in range(N-2, -1, -1):
        n = continued_fraction[i]
        temp = (Fraction(1,1)/temp) + Fraction(n, 1)
    return temp



def isnumgreater(n):
    return len(str(n.numerator)) > len(str(n.denominator))


print(sum(1 for i in range(2,1001) if isnumgreater(ans(i))))



