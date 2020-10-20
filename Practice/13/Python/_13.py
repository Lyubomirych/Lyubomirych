#!/usr/bin/env python3

def main():
    n = int(input("Введите число больше 2 и меньше 1 миллиарда: "))
    if n>=2 and n<=10**9:
        if ((n != 2 and n != 3) and (n % 2 == 0 or n % 3 == 0)):
            print(n, " - составное число")
        else:
            print(n, " - простое число")
    elif n<2:
        print("проверяемое число меньше 2")
    else: 
        print("поверяемое число больше 1 миллиарда")
if __name__ == '__main__':
    while True:  
        main()



