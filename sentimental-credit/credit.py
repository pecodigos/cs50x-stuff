from cs50 import get_string

# Prompt the user for a credit card number
number = get_string("Card number: ")

# Luhn's Algorithm
total = 0
for index, digit in enumerate(reversed(number)):
    if index % 2 == 0:
        total += int(digit)
    else:
        doubled = int(digit) * 2
        if doubled > 9:
            doubled_str = str(doubled)
            for char in doubled_str:
                total += int(char)
        else:
            total += doubled

# Check, using Luhn's Algorithm, if credit card is valid
if total % 10 != 0:
    print("INVALID")
else:
    for i in range(51, 56):
        if number.startswith(str(i)) and len(number) == 16:
            master = True
            break
        else:
            master = False
    # Report via print wheter it is a valid American Express, MasterCard or Visa card number
    if (number.startswith("34") or number.startswith("37")) and len(number) == 15:
        print("AMEX")
    elif number.startswith("4") and (len(number) == 13 or len(number) == 16):
        print("VISA")
    elif master == True:
        print("MASTERCARD")
    else:
        print("INVALID")
