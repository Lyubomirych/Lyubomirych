#!/usr/bin/env python3
def main():
    dlina, bukvy = [input(f'{name}: ') for name in ['Сколько символов? ', 'Какие символы? ']]
    dlina = int(dlina)
    parol = ['']
    parol2 = []

    for i in range(dlina): #генерируем все возможные варианты слов
        for pas in parol:
            for let in bukvy:
                parol2 += [pas + let]
        parol = parol2; parol2 = []
    for pas, i in zip( parol, range(len(parol))): #отсеиваем не подходящие по условию слова такие как aaa
        if (not all([let in pas for let in bukvy])): #генератор, возвращающий массив, с результатом условия для каждой буквы
            del parol[i]                             #если буква будет отсутствовать в слове, на ее месте будет значение false, удаляем слово
    print(' '.join(parol))
    vixod = input("закрыть программу? y/n: ")
    if vixod == "y":
        quit(0)
if __name__ == '__main__':
    while True:  
        main()

