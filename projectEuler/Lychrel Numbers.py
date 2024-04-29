def islycherel(n):
    for i in range(50):
        n += int(str(n)[::-1])
        if str(n) == str(n)[::-1]:
            return False
    return True

print(sum([1 for i in range(1,10000) if islycherel(i)]))