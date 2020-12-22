print ('Введите переменные a, b, c ')
import math
a = float(input())
b = float(input())
c = float(input())
d = (b*b)-(4*a*c)
if d>0 and a!=0:
    x1 = (-b + math.sqrt(d))//(2*a)
    print('x1 = ', x1)
    x2 = (-b - math.sqrt(d))//(2*a)
    print ('x2 = ', x2)
if d<0:
    print('Нет корней')
if a==0:
    x = (-c)//b
    print ('x = ', x)


