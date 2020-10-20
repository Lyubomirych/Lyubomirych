#!/usr/bin/env python3

def main():
    n = int(input("Введите число: "))
    if n>=0 and n<=10**15:
        i = 0
        while 2**i <= n:
            i = i + 1
        print("степеней двойки начиная с нулевой: ", i)
    elif n<0: 
        print("введите положительное число ")
    else:
        print("слишком большое число ")
if __name__ == '__main__':
    while True:  
        main()





