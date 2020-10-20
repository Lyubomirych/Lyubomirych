import math
#!/usr/bin/env python3

def main():
    x, op, y = ((i) for i in input("Введите выражение с элементами через пробел: ").split())
    x = int(x)
    y = int(y)
    if op == "+":
        print("x + y = ", x+y)
    elif op == "-":
         print("x - y = ", x-y)
    elif op == "*":
         print("x * y = ", x*y)
    elif op == "/":
         print("x / y = ", x/y)
    else:
        print("неверно введенное зачение, ввод только значений +, -, *, /")
if __name__ == '__main__':
    while True:  
        main()
