from itertools import permutations

def process(s):
    for l in range(1,9):
        n = int(s[:l])
        s2 = ""
        for i in range(1,10):
            s2 += str(n*i)
            if s2 == s:
                return True
            elif len(s2) > len(s):
                break
    return False


# Generate all permutations of '123456789'
perms = permutations('123456789')

# Sort permutations in decreasing order
decreasing_perms = sorted(perms, reverse=True)

# Print the permutations
for perm in decreasing_perms:
    if(process(''.join(perm))):
        print(''.join(perm))
        break
