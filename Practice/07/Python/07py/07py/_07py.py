def main(i):
 print('Выберите способ:\n 1.Через стороны\n 2. Через координаты ')
 import math
 d = int(input())
 if d == 1:
    print('Введите стороны')
    a = float(input())
    b = float(input())
    c = float(input())
    if a > 1000 or b > 1000 or c > 1000:
        print('Неправильно. Попробуйте ещё раз.')
        return main(i)
    else:
        p = (a+b+c)//2
        s = math.sqrt(p*(p-a)*(p-b)*(p-c))
        print(s)
 elif d == 2:
    print('Введите координаты')
    x1, y1 = map(float,input().split())
    x2, y2 = map(float,input().split())
    x3, y3 = map(float,input().split())
    if x1 > 1000 or x2 > 1000 or x3 > 1000 or y1 > 1000 or y2 > 1000 or y3 > 1000:
        print('Неправильно. Попробуйте ещё раз.')
        return main(i)
    a = math.sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))
    b = math.sqrt((x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3))
    c = math.sqrt((x3-x1)*(x3-x1)+(y3-y1)*(y3-y1))
    p = (a+b+c)//2
    s = math.sqrt(p * (p - a) * (p - b) * (p - c))
    print (s)
main(0)


