prm = []


def issquare(n):
    if n < 0:
        return False
    if n**0.5 == int(n**0.5):
        return True
    return False

i = 3
while(True):
    p = True
    for j in prm:
        if(i%j == 0):
            p = False
            break
    if(p):
        prm.append(i)
    f = False
    for j in prm:
        if(issquare((i-j)/2)):
            f = True
            break
    if not f:
        print(i)
        break
    i += 2
