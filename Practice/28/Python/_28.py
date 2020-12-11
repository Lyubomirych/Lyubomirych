import math
from collections import Counter


n=int(input("Введите число n(1<=n<=1000000000): "))

def print_factorization(number):
    s = []
    c = []
    for i in range(2, int(math.sqrt(number)) + 1): 
        while (number % i == 0):
            s.append(i)
            number //= i 

    if (number != 1): 
        s.append(number)
        #print (number)
    print("Решение стандартным умножением:")
    print(n, "= ", end='')
    print(*s, sep='*', end='\n')
    c = Counter(s)
    if (len(s)>1):
        print("Решение преобразованием умножения одинаковых в степень:")
        print(n,"= ", 1, end='')
        for i in range(max(s)+1):
            if(c[i]>1):
                print(" *", i, "^",c[i], end='')
            elif(c[i]>0 and c[i]<=1):
                print(" *",i, end='')
        print(end='\n')



print_factorization(n)
k=input("Enter to close")
