"""
1. Saisir un nombre entier positif et inverser dans la variable l’ordre des chiffres de ce nombre
(par exemple, si la valeur de départ est 5342 dans la i, l'exécution du programme donnera la
valeur 2435 dans la i).

"""

"""

nombre = int(input("Entrez un nombre : "));
inverse = 0

while nombre != 0:
    inverse = inverse *10
    inverse = inverse + int(nombre%10)
    nombre = int(nombre/10)

print(inverse)

"""

"""
2. Saisir un nombre entier positif et afficher la somme et la moyenne arithmétique de ses
chiffres (par exemple, pour le nombre 2155, la somme des chiffres est 13 (2 + 1 + 5 + 5) et
la moyenne est 3,25 (13/4))

"""

"""

nombre = int(input("Entrez un nombre : "))
somme = 0
i = 0

while nombre != 0:
    somme += int(nombre % 10)
    nombre = int(nombre / 10)
    i+=1
print("La somme est de : {} et la moyenne de : {}".format(somme, somme/i))

"""

"""
1. Afficher une table de multiplication ainsi :
    1 2 3 4 5 6 7 8 9 10
    2 4 6 8 10 12 14 16 18 20
    3 6 9 12 15 18 21 24 27 30
    4 8 12 16 20 24 28 32 36 40
    5 10 15 20 25 30 35 40 45 50
    6 12 18 24 30 36 42 48 54 60
    7 14 21 28 35 42 49 56 63 70
    8 16 24 32 40 48 56 64 72 80
    9 18 27 36 45 54 63 72 81 90
    10 20 30 40 50 60 70 80 90 100

Pour afficher la table en alignant correctement les nombres en colonnes (4 caractères pour
chaque colonne), utilisez la fonction format() décrite dans la section 1.2 des notes de cours.

"""

"""

for i in range(1, 11):
    for j in range(1, 11):
        print("{:4d}".format(i*j), end='')
    print('\n')

"""

"""

2. Afficher un triangle rempli d’étoiles s’étendant sur un nombre de lignes entré au clavier et se
présentant comme dans cet exemple où 5 lignes ont été entrées:

"""

"""

nombre_etoile = int(input("Entrez un nombre de lignes : "))

for i in range(1, nombre_etoile):
    print("*"*i)

"""