size, fe, step = map(int, input().split(' '))
arr = create(size, fe, step)
sort(arr)
print(arr)


def create(size, m = 0, h = 0) -> list:
    arr = []
    arr.append(m)
    i = 1
    for i in range (1, size):
        arr.append(arr[i]+h)
    return arr

def sort(arr) -> list:
    for i in range(1, len(arr)):
        key = arr[i]
        j = i-1
        while j >=0 and key < arr[j]:
            arr[j+1] = arr[j]
            j = j - 1
        arr[j+1] = key

    return arr

print1 = print

def print(arr) -> list:
    print1('[', end='')
    for i in range(len(arr)):
        print1(arr[i], end=', ')
    print1(arr[len(arr) - 1], ']', sep='')
    return arr

