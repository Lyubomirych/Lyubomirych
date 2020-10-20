import math
#!/usr/bin/env python3

def main():
    x = input("Введите целое число: ")
    x = int(x)
    if x>=0:
        fact = math.factorial(x)
        if (fact<=(10**9)):
            print(fact)
        else:
            print("слишком большое число")
    else:
        print("поменяйте число, оно не может быть отрицательным")
if __name__ == '__main__':
    while True:  
        main()


