def repeatsDigits(number):
    digits = []
    for d in str(number):
        if d in digits:
            return True
        digits.append(d)

    return False


def main():
    pandigitals = []

    for n in range(1, 100000):
        if repeatsDigits(n):
            continue
        for m in range(n, 100000):
            if repeatsDigits(m):
                continue

            allDigits = str(n) + str(m) + str(m*n)

            if len(allDigits) > 9:
                break
            if len(allDigits) == 9:
                if '0' not in allDigits:
                    if not repeatsDigits(allDigits):
                        pandigitals.append(n*m)

    print (sum(set(pandigitals)))

if __name__ == "__main__":
    main()