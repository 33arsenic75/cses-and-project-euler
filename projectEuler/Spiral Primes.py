def isprm(n):
    if n < 2:
        return False
    if n == 2:
        return True
    if n % 2 == 0:
        return False
    for i in range(3, int(n**0.5)+1, 2):
        if n % i == 0:
            return False
    return True


dic = {}
dic[1]=0
def count(n):
    ans = 0
    ans += isprm(n**2 - n + 1)
    ans += isprm(n**2 - 2*n + 2)
    ans += isprm(n**2 - 3*n + 3)
    dic[n] = ans + dic[n-2]
    if 10* dic[n] < 2*n - 1:
        print(n) 
        return True
    return False

i = 3
while(True):
    if count(i):
        break
    i += 2
