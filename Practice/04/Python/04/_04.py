
a = int(input("Введите значение a:"))
b = int(input("Введите значение b:"))
x=a
a=b
b=x
print("a =", a , "b =", b, "\n")
a, b = b, a
print("a =", a , "b =", b, "\n")