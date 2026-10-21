# Problem: Distinct Powers
# File: Distinct Powers.py
# Created: 2024-04-28
# Author: abhinav
# Link:
# Topic: Big Integers, Maps and Sets
#

def main():
    terms = []
    for a in range(2, 101):
        for b in range(2, 101):
            terms.append(a**b)

    # set() removes the duplicates
    # len() gives the number of elements
    print (len(set(terms)))


if __name__ == "__main__":
    main()