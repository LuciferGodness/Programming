def main():
 c = int(input())
 if c >  1000000000000000 or c < 0:
    print('Неправильно! Попробуйте ещё раз!')
    return main();
 count = 0
 i = 1
 while i<=c:
    count = count + 1
    i = i*2
 print(count)
main()