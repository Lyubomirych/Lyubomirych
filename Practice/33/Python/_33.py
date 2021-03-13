
def create(dlina, first_element = 0, shag = 0):
    return [i for i in range(first_element, first_element + shag*dlina, shag)]

def sort(array, dlina):
    for i in range(1, dlina):
        temp = array[i]
        j = i - 1
        while (j >= 0 and temp < array[j]):
            array[j + 1] = array[j]
            j = j - 1
        array[j + 1] = temp

    return array

def myprint(array):
    print(array)
    return array

print('Введите длинну массива, начало и шаг: ');
dlina = int(input())
first_element = int(input())
shag = int(input())
arr = create(dlina, first_element, shag)
myprint(sort(arr, dlina))
