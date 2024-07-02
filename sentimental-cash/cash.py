from cs50 import get_float


def main():
    # Get user's input
    while True:
        money = get_float("Change: ")
        if money <= 0:
            pass
        else:
            money = money * 100
            break

    # Calculate quarters
    quarters = calcQuarquers(money)
    money = money % 25

    # Calculate dimes
    dimes = calcDimes(money)
    money = money % 10

    # Calculate nickels
    nickels = calcNickels(money)
    money = money % 5

    # Calculate pennies
    pennies = calcPennies(money)
    money = money % 1

    # Sum and print
    change = quarters + dimes + nickels + pennies
    print(int(change))


def calcQuarquers(money):
    return money // 25


def calcDimes(money):
    return money // 10


def calcNickels(money):
    return money // 5


def calcPennies(money):
    return money // 1


main()
