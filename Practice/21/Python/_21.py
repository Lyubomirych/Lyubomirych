#!/usr/bin/env python3
def main():
    ves, rost = input("Введите ваш рост и вес: \n").split()
    ves = float(ves)
    rost = float(rost)
    if ves != 0 and rost != 0:
        def bmi (weight, height):       #Функция вычисляющая BMI
                return (weight / (height**2))*(10**4) 
        n = bmi(ves, rost)
        def print_bmi(bmi):           #Функция выводящая значение
            if bmi < 18.5:
                print("Underweight")
            elif 18.5 <= bmi < 25:
                print("Normal")
            elif 25 <= bmi < 30:
                print("Overweight")
            else:
                print("Obesity")
        print_bmi(n) # Вызов функции
        vixod = input("закрыть программу? y-да: \n")
        if vixod == "y":
            quit(0)
    else: print("Введите положительные значения: ")
if __name__ == '__main__':
    while True:  
        main()
