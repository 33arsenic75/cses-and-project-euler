def cycle(n):
    r = 1
    i = 0
    seen = {}
    seen[r] = 0
    while(True):
        i+=1
        if r == 0:
            return 0
        r = (r*10)%n
        if seen.get(r) != None:
            return i - seen[r]
        seen[r] = i
        


N = 1000
max_cycle = 0
max_cycle_num = 0
for i in range(1,N):
    temp = cycle(i)
    if temp > max_cycle:
        max_cycle = temp
        max_cycle_num = i

print(max_cycle_num, max_cycle)
