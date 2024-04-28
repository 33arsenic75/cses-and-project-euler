monthDays = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
days = [0, 0, 0, 0, 0, 0, 1]
def main():
    dayCount = 0
    sundays = 0
    for year in range(1900, 2001):
        for month in range(1, 13):
            daysThisMonth = 0
            if month == 2:
                if year % 4 == 0 or year % 400 == 0:
                    daysThisMonth = monthDays[month]+1
            daysThisMonth = monthDays[month]
            for day in range(1, daysThisMonth+1):
                if day == 1 and (year != 1900):
                    sundays += days[dayCount % 7]

                dayCount += 1
    print (sundays)


if __name__ == "__main__":
    main()