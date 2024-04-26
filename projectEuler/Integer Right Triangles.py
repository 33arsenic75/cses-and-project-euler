global dic
dic = {}
def process(p):
    count = 0
    for i in range(1,p+1):
        for j in range(i,p+1):
            k = p - i - j
            if i**2 + j**2 == k**2 and i>0 and j>0 and k>0:
                count += 1
    dic[p] = count






for i in range(1,1001):
    dic[i] = 0

for i in range(1,1001):
    process(i)

print(max(dic, key=dic.get))


