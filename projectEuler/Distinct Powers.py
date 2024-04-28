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