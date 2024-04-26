dic = {}

for i in range(ord('A'), ord('Z')+1):
    dic[chr(i)] = (i - ord('A') + 1) * (i - ord('A') + 2) / 2


def istriangle(n):
    m = 8*n + 1
    if m**0.5 == int(m**0.5):
        return True
    return False

count = 0
with open("Coded Triangle Numbers.txt", "r") as file:
    # Read each line
    lines = file.readlines()

    # Iterate through each line
    for line in lines:
        # Split the line into words
        words = line.strip().split(',')

        # Access each word
        for word in words:
            sum = 0
            for i in word[1:-1]:
                sum += dic[i]
            if istriangle(sum):
                print(word[1:-1])
                count += 1


print(count)
