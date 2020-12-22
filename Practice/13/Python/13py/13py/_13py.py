def main():
 c = int(input())
 if c > 1000000000 or c < 0:
   print('Неправильно! Попробуйте ещё раз!')
   return main()
 count = 0
 k = 2
 while k*k <= c and count == 0:
    if c%k == 0:
        count+=1
    k+=1
 if count == 0:
  print ('Простое')
 else:
  print ('Сложное')
main()
