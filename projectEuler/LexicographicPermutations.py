from itertools import permutations
# Generate all permutations of '123456789'
perms = permutations('0123456789')

# Sort permutations in decreasing order
decreasing_perms = sorted(perms)
N = 1000000
# Print thepermutations

print (''.join(decreasing_perms[N-1]))
