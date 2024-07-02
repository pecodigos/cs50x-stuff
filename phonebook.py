people = {
    "Carter": "+55-48-99999-8888",
    "Pedro": "+55-48-99803-8701",
    "Doug": "+55-48-99787-4893",
}

name = input("Name: ")

if name in people:
    number = people[name]
    print(f"Found: {number}")
else:
    print("Not found")
