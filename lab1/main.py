with open('input.txt', 'w') as f:
    n = int(input())
    for i in range(n-1):
        f.write(str(i)+'\n')
    f.write(str(n-1))
