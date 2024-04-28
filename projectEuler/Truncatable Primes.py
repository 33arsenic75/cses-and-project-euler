def prime(n):
    prm = [2]
    for i in range(3,n+1,2):
        for j in prm:
            if j*j > i:
                prm.append(i)
                break
            if i%j == 0:
                break
    return prm

prm = prime(1000000)

def trunable(n):
    for i in range(0,len(str(n))):
        if int(str(n)[i:]) not in prm:
            return False
    for i in range(1,len(str(n))):
        if int(str(n)[:-i]) not in prm:
            return False
    return True

print(sum(i for i in prm if i > 10 and trunable(i)))