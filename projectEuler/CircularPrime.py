N = 1000000

global prm
prm = []

def rotate(n):
    num_str = str(n)
    num_len = len(num_str)
    rotations = 1 % num_len  # Ensure rotations are within the length of the number
    
    rotated_num = num_str[-1:] + num_str[:-1]
    return int(rotated_num)
    
def prime(n):
    for i in prm:
        if(n%i==0):
            return
    prm.append(n)

for i in range(2,N+1):
    prime(i)

mem = {}
ans = 0
for i in prm:
    j = rotate(i)
    f = True
    while(j!=i):
        if j in prm:
            j = rotate(j)
        else:
            f = False
            break
    if f:
        ans +=1

print(ans)
    