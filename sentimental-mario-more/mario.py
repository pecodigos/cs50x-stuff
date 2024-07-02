from cs50 import get_int

# Prompt the user with get_int for the half-pyramid height, a positive integer between 1 and 8, inclusive
while True:
    height = get_int("Enter height: ")
    # If the user fail to provide a positive integer no greater than 8, you should re-prompt for the same again
    if height > 8 or height < 1:
        print("It must be a number between 1 and 8.")
    else:
        break

# Generete the desired half-pyramids
for row in range(height):
    for space in range(height - row - 1):
        print(" ", end="")
    for column in range(row + 1):
        print("#", end="")
    print("  ", end="")
    for column2 in range(row + 1):
        print("#", end="")
    print()
