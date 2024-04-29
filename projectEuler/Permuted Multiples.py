def issame(n):
    for i in range(2,7):
        if sorted(str(n)) != sorted(str(n*i)):
            return False
    return True

i = 1
while(True):
    if issame(i):
        print(i)
        break
    i += 1