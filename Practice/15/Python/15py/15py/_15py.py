def main():
 import random
 print('Добро пожаловать. Начнём игру')
 rn = random.randint(1,100)
 i = 0
 k = 5
 for i in range(k):
   f = int(input())
   if f > rn:
      print('Загаданное число меньше')
   elif f < rn:
      print('Загаданное число больше')
   elif f == rn:
      print('Поздравляю, вы угадали!')
      break
 if f!=rn:
       print('Вы проиграли. Было загадано:', rn)
 print('Хотите начать сначала?(1-ДА)')
 count = int(input())
 if count == 1:
     return main()
main()
