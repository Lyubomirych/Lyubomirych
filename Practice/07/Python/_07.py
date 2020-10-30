import math
#!/usr/bin/env python3

def main():
   x = int(input("Если вы хотите найти площадь по сторонам, введите 1 или 2 если по координатам вершин: "))
   if x == 1:
        a = int(input("Введите длину стороны A: "))
        b = int(input("Введите длину стороны B: "))
        c = int(input("Введите длину стороны C: "))
        if (a > 0 and b > 0 and c > 0):
            p = (a+b+c)/2
            print ("p = ", p, "S = ", math.sqrt(p*(p-a)*(p-b)*(p-c)) )
        else: print("Необходимы значения больше нуля ")
   elif x == 2:
        x1, y1 = (float(i) for i in input("Введите значения ax, ay ").split())
        x2, y2 = (float(i) for i in input("Введите значения bx, by ").split())
        x3, y3 = (float(i) for i in input("Введите значения cx, cy ").split())
        print("S = ", ((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1))/2)
   else:
        print("неверно введенное зачение")
if __name__ == '__main__':
    while True:  
        main()