#!/usr/bin/env python3
def main():
    import array  
    i = 0
    while (i == 0):
        cash = float(input("Денег: "))
        i = 1
    i = 0
    while (i == 0):
        qdrink = int(input("Разновидностй напитков: "))
        i = 1
    x = 0
    i = 0
    napitok = []
    while (x < qdrink):
        i = 0
        while (i == 0):
            try:
                vid, cena, emcost = input("Продукт  |  Цена  |  Литры, через пробел: \n").split()
                vid = str(vid) #задаем в исключении значения названия, цены и объема
                cena = float(cena)
                emcost = float(emcost)
                if ((cena > 0) and (emcost > 0)):
                    list = [vid, cena, emcost]
                    napitok.append(list)
                    x = x + 1
                    i = 1
                else:
                    print("Введите положительные значения!")
            except:
                print("формат ввода неверен, попробуйте еще ")
    try:
        b = 0
        c = -1
        s = []
        for i in napitok:
            vibor = cash//i[1]
            lit = vibor*i[2]
            mon = cash - vibor * i[1]
            list = [i[0], vibor, lit, mon]
            s.append(list)
            if (lit>b):
                b = lit
                c = c + 1
        if (c < 0):
            print("-1")
        else:
            result = s[c]
            print("Куплено: ", str(round(result[1])) + " бутылок '" + str(result[0])+"' ")
            print("Литраж: ", result[2])
            print("Сдача: ", result[3])
    except:
        print("Ошибка")
    vixod = input("\n закрыть программу? y/n: \n")
    if vixod == "y":
        quit(0)
if __name__ == '__main__':
    while True:  
        main()
