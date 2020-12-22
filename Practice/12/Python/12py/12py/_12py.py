def main():
 a = int(input())
 if a > 1000000000 and a < 0:
   print('Неправильно! Попробуйте ещё раз!')
   return main()
 k = 1
 while a>1:
    k = k*a
    a = a-1
 print(k)
main()
