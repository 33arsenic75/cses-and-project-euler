def score(s):
    ans = 0
    for c in s:
        ans += ord(c) - ord('A') + 1
    return ans


import pandas as pd
import csv
df = pd.read_csv("NamesScores.csv")
df = df.columns.tolist()
df.sort()

ans = 0
for i in range(1,len(df)+1):
    ans+=i*score(df[i-1])
print(ans)