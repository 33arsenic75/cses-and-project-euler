def getTriangleNumbers(maxNumber):
    triangleNumbers = []
    n = 1
    t = 0

    while t < maxNumber:
        t = (n*(n+1))/2
        triangleNumbers.append(t)
        n += 1

    return triangleNumbers


def main():
    """
    Reusing code of problem 22
    """

    triangleWordCount = 0
    # It is waaay more efficient to have a list of triangle numbers
    # than calculating them each time
    # The biggest triangle number is more than enought (is for "ZZZZZZZZZZZ")
    triangleNumbers = getTriangleNumbers(500)

    file = open("Coded Triangle Numbers.txt", "r")
    text = file.read()
    file.close()

    # Create a list with the words in the format ["jonno", "seijo", ... ]
    text = text.replace("\"", "")
    words = text.split(",")

    for word in words:
        wordValue = 0

        for c in word:
            # ord(char) returns the value of the ascii character.
            # ord('A') is 65, but I want the score to start in 1
            # so I substract 64 so score with 'A' is 1
            wordValue += ord(c)-64

        if wordValue in triangleNumbers:
            triangleWordCount += 1

    print(triangleWordCount)

if __name__ == "__main__":
    main()