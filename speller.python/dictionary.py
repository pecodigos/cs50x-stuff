words = set()

def check(word):
    return word.lower() in words

def load(dictionary):
    with open(dictionary) as file:
        words.update(files.read().splitlines())
    return true

def size():
    return len(words)


