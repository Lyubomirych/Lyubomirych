import collections
#!/usr/bin/env python3
def main():
    string = 'hallo, klempner, das, ist, fantastisch, fluggegecheimen' # известные слова из немецкого языка 
    simvols = [i for i in string if i.isalpha()]
    simvols_len = len(simvols)
    simvols = dict(collections.Counter(simvols))
    ver = 1
    slowo = list(input('\n Введите стоп слово: \n'))
    for i in slowo:
        ver = ver * (simvols[i] / simvols_len)
    print(ver)
    vixod = input("закрыть программу? y-да: \n")
    if vixod == "y":
        quit(0)
if __name__ == '__main__':
    while True:  
        main()