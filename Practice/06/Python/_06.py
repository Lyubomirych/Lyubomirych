import math
#!/usr/bin/env python3
def main():
    a = float(input("Введите значения a: "))
    b = float(input("Введите значения b: "))
    c = float(input("Введите значения c: "))
    d = pow(b,2)-4*a*c 
    if a == 0 and b == 0 and c != 0: 
        print("Система не имеет решений, так как ", c, "не может быть равен 0")
    if a == 0 and b == 0 and c == 0: 
        print("Решение системы - любое число")
    elif a != 0 :
        if d < 0:
            print("Дискриминант равен ", d)
            print("Действительных корней нет")
        elif d == 0:
            x = -b / (2 * a)
            print("x = " , x)
        else:
            x1 = (-b + d ** 0.5) / (2 * a)
            x2 = (-b - d ** 0.5) / (2 * a)
            print("Дискриминант равен ", d)
            print("x1 = %.2f \nx2 = %.2f" % (x1, x2))
    elif a == 0 and b!= 0:
        x = -c/b
        print("x = ", x)
    vixod = input("закрыть программу? y/n: ")
    if vixod == "y":
        quit(0)
if __name__ == '__main__':
    while True:  
        main()

