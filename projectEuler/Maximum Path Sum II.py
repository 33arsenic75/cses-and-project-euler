with open("Maximum Path Sum II.txt", "r") as file:
    lines = file.readlines()

# Process each line to extract the numbers
temp = []
for line in lines:
    numbers = list(map(int, line.strip().split()))
    temp.append(numbers)

n = len(temp)
ans = [[0] * n for _ in range(n)]
ans[0][0]=temp[0][0]

for i in range(1,n):
    ans[i][0] = ans[i-1][0] + temp[i][0]

for i in range(1,n):
    for j in range(1,i+1):
        ans[i][j] = max(ans[i][j], temp[i][j] + ans[i-1][j],  temp[i][j] + ans[i-1][j-1])

print(max(ans[n-1]))