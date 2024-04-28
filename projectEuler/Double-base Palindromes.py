def ispalindrome10(n):
    return str(n) == str(n)[::-1]

def ispalindrome2(n):
    return bin(n)[2:] == bin(n)[2:][::-1]

print(sum(i for i in range(1,1000000) if ispalindrome10(i) and ispalindrome2(i)))
