M = 10**10

dic = {i: pow(i,i,M) for i in range(1, 1000+1)}

print(sum(dic[i] for i in range(1, 1000+1)) % M)


# (10 + 1)^11 = 11C1* 10