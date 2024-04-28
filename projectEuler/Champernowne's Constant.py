def main():
    concaten = ""
    number = 0

    # Create a string with all the numbers
    # Stop when I wont need more positions (+1000000)
    while len(concaten) <= 1000000:
        concaten += str(number)
        number += 1

    answer = 1
    digit = 1
    # The digits I need goes: 1, 10, 100, 1000, 10000 ...
    # It is multiplied by ten every time
    # I get that digit position (a single number) from the string
    while digit <= 1000000:
        answer *= int(concaten[digit])
        digit *= 10

    print(str(answer))


if __name__ == "__main__":
    main()