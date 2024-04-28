from itertools import permutations

def isprm(n):
    if n < 2: return False
    if n == 2: return True
    if n % 2 == 0: return False
    p = 3
    while p*p <= n:
        if n % p == 0: return False
        p += 2
    return True

s = "123456789"
# Generate all permutations of '123456789'
def process(s):
    perms = permutations(s)
    decreasing_perms = sorted(perms, reverse=True)
    # Print the permutations
    for perm in decreasing_perms:
        if(isprm(int(''.join(perm)))):
            print(''.join(perm))
            return True
    return False

for i in range(9,0,-1):
    ss = s[:i]
    if(process(ss)):
        break