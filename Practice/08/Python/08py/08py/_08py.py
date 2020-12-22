def main():
 a, oper, b = input().split(' ')
 try:
     if oper == "+":
        c = int(a)+int(b)
        print(c, sep='\n')
     elif oper == "-":
        c = int(a)-int(b)
        print(c, sep='\n')
     elif oper == "*":
        c = int(a)*int(b)
        print(c, sep='\n')
     elif oper == "/":
        c = int(a)//int(b)
        print(c, sep='\n')
 except:
        print('Неправильно. Попробуйте ещё раз.')
        main()
main()   
