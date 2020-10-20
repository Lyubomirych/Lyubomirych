#!/usr/bin/env python3

def main():
    print('Введите целое число, затем два диапазона целых чисел')
    S, l1, r1, l2, r2= map(int, input().split())
    if l1 + l2 == S:
        print(l1, l2)
    elif l1 + r2 == S:
        print(l1, r2)
    else:
        if r1 + l2 == S:
            print(r1, l2)
        elif r1 + r2 == S:
            print(r1, r2)
        else:
            print(-1, ", таких чисел не существует")
if __name__ == '__main__':
    while True:  
        main()

