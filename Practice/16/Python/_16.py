sig = 'a55661'
chisl = int(input('Введите количество билетов: '))
bilet = [i for i in input('Введите номера билетов: ').split()]
n = 0
for bilet in bilet:
    korbil = bilet[0] + bilet[4:]
    if korbil == sig:
        print(bilet)
        n += 1
if n == 0:
    print(-1)






