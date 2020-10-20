import collections

n = []
red_list = [1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36] # black_list = [2, 4, 6, 8, 10, 11, 13, 15, 17, 20, 22, 24, 26, 28, 29, 31, 33, 35]
red, black = 0, 0
def get_probability(i):
    n.append(i)
    c = collections.Counter(n)
    a = [k for k, v in c.items() if v == max(c.values())]
    for i in a:
        print(i, end=' ')
    print()
    return a
while True:
    print()
    num = int(input('Введите число: '))
    if num < 0:
        quit(0)
    if num in red_list:
        red += 1
    else:
        black += 1
    print("Выпадали числа:")
    nums = get_probability(num)
    print("Не выпадали числа:")
    for i in range(36):
        if i in nums:
            continue
        print(i, end=' ')
    print()
    print("красных выпало:", red, "черных выпало:", black)

