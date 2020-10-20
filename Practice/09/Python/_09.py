import math
#!/usr/bin/env python3

def main():
    h1, m1 = map(int, input('Когда пришел первый? ').split(':'))
    h2, m2 = map(int, input('Когда пришел второй? ').split(':'))
    if -15 <= (h1*60+m1) - (h2*60+m2) <= 15:
        print('Встреча состоится')
    else:
        print('Встреча не состоится') 
if __name__ == '__main__':
    while True:  
        main()
