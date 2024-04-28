from itertools import permutations
# Generate all permutations of '123456789'
perms = permutations('1234567890')

def check(s):
    s2 = int(s[1:4])
    s3 = int(s[2:5])
    s4 = int(s[3:6])
    s5 = int(s[4:7])
    s6 = int(s[5:8])
    s7 = int(s[6:9])
    s8 = int(s[7:10])
    if s2%2 == 0 and s3%3 == 0 and s4%5 == 0 and s5%7 == 0 and s6%11 == 0 and s7%13 == 0 and s8%17 == 0:
        return True
    
sum = 0
for perm in perms:
    # print(''.join(perm))
    if(check(''.join(perm))):
        sum += int(''.join(perm))

print(sum)
