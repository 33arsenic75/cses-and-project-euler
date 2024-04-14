totalyears = 100
totaldays = 100*365 + 24
ans = 0
for i in range(1,totaldays+1):
    ans+=(i%7==0)
print(ans)