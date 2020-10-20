#!/usr/bin/env python3

def main():
    x = input('Введите число: ')
    x = float(x)
    y = input('Введите степень: ')
    y = int(y)
    i = 0
    res = 1
    while i < y:
        res= res*x
        i= i+1
    print(x, " в степени ", y, " = ", res)
if __name__ == '__main__':
    while True:  
        main()


