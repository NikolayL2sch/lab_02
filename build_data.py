from random import *
f = open("students_2.txt","w+")
n = 1000
names = ['Nikolay', 'Artem', 'Dima', 'Nikita', 'Gosha', 'Umed', 'Vlad', 'Max', 'Andrey', 'Ilya', 'Danil', 'Masha', 'Anya']
streets = ['Grazhdan', 'Prostornaya', 'Bolshaya', 'Rusakovskaya', 'Krasnoselskaya', 'Umnaya', 'Baumanskaya', 'Izmailovskaya', 'Krasivaya', 'Moskovskaya', 'Krondstadt']
for i in range(n):
    f.write((names[randint(0, 12)]+' '))
    f.write((str(randint(0,1))+' '))
    f.write((str(randint(18,35))+' '))
    f.write((str(randint(0, 100))+' '))
    f.write((str(randint(1969, 2022))+' '))
    lives = randint(0, 1)
    f.write((str(lives)+' '))
    if lives == 0:
        f.write((streets[randint(0,10)]+' '))
        f.write((str(randint(1, 100))+' '))
        f.write((str(randint(1, 1000))+' '))
    else:
        f.write((str(randint(1, 100))+' '))
        f.write((str(randint(1, 1000))+' '))
    f.write('\n')
f.close()
