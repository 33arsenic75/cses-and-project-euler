import math


def getPrimes(maxNumber):
    primes = [2]
    number = 3
    while number < maxNumber:
        for div in primes:
            if div >= int(math.sqrt(number)) + 1:
                isPrime = True
                break
            if number % div == 0:
                isPrime = False
                break

        if isPrime:
            primes.append(number)
        number += 2

    return primes


def isPrime(number):
    #print number

    number = int(number)
    # Divisible by 2, not prime
    if number % 2 == 0:
        return False

    div = 3

    # If divisible by something, not prime
    while div < int(math.sqrt(number)) + 1:
        if number % div == 0:
            return False
        # Increase by 2, we already checked even numbers
        div += 2

    return True


def getBinaryPermutations(digits):
    binaryPermutations = []
    currentBinary = '0' * digits

    n = 1
    while currentBinary != '1'*digits:
        currentBinary = "{0:b}".format(n)

        currentBinary = '0'*(digits - len(currentBinary)) + currentBinary
        binaryPermutations.append(currentBinary)

        n += 1

    return binaryPermutations


def main():
    primes = getPrimes(300000)
    permutations = getBinaryPermutations(len(str(primes[0])))

    permutationDigits = 0

    numberModify = ''

    answer = 0

    for number in primes:
        if answer != 0:
            break
        if(len(str(number)) > permutationDigits):
            permutations = getBinaryPermutations(len(str(number)))
            permutationDigits = len(str(number))
        for permut in permutations:

            numberModifyList = []

            for digitChange in range(0, 10):

                numberModify = str(number)
                leadingZero = False

                # to replace each 1 with the digit
                for i in range(0, len(permut)):
                    if permut[i] == '1':
                        if (i == 0) and (digitChange == 0):
                            leadingZero = True
                            continue
                        else:
                            # strings are inmutable, i cant replace chars
                            numberModify = numberModify[:i] + str(digitChange) + numberModify[i+1:]

                if isPrime(numberModify) and not leadingZero:
                    numberModifyList.append(numberModify)

            if len(numberModifyList) == 8:
                answer = min(numberModifyList)
                break

    print (str(answer))

if __name__ == "__main__":
    main()