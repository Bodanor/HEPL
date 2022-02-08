'''

Exercice 1 :

1. Entrer la taille pour les côtés a, b et c et afficher si le triangle est rectangle ou non, c’est-à-
dire s'il satisfait le théorème de Pythagore ou non (par exemple, quand a = 3, b = 4 et
c = 5, alors le triangle est rectangle). Les valeurs sont des entiers.
'''

'''
a = int(input("Entrez l'hypotenuse : "))
b = int(input("Entrez le cote b : "))
c = int(input("Entrez le cote c : "))

if (a**2 == (b**2+ c**2)):
    print("C'est un triangle rectangle !")
else:
    print("Ce n'est pas un triangle rectangle !")
'''

'''

Exercice 2

2. Entrer 2 flottants et saisir l'opération à réaliser sur ces 2 nombres parmi : 
1 pour +, 2 pour -, 3 pour * et 4 pour /, puis afficher le résultat de l’opération en
entier et en flottant.
'''

'''

flottant1 = float(input("Entrez le premier flottant : "))
flottant2 = float(input("Entrez un deuxieme flottant : "))

operation = int(input("Entrez l'operation à effectuer : \n\n1) Additioner\n2) soustraire\n3) Multiplie\n4) Diviser\n\n Choix(1-4) : "))

if operation == 1:
    print("L'addition de {} avec {} vaut : {} en flottant et {} en entier ".format(flottant1, flottant2, flottant1+flottant2, int(flottant1+flottant2)))
elif operation == 2:
    print("La soustraction de {} avec {} vaut : {} en flottant et {} en entier".format(flottant1, flottant2, flottant1-flottant2, int(flottant1-flottant2)))
elif operation == 3:
    print("La multiplication de {} avec {} vaut : {} en flottant et  {} en entier".format(flottant1, flottant2, flottant1 * flottant2, int(flottant1*flottant2)))
elif operation == 4:
    print("La division de {} avec {} vaut : {} en flottant et {} en entier".format(flottant1, flottant2, flottant1 / flottant2, int(flottant1/flottant2)))

'''

'''

Exercice 3 : 

3. Entrer la taille des 3 côtés d'un triangle. Afficher si ce triangle est quelconque, isocèle (= 2
des 3 côtés ont la même taille) ou équilatéral (= les 3 côtes ont la même taille). Les valeurs
sont des entiers.
'''

'''

a = int(input("Entrez le cote a : "))
b = int(input("Entrez le cote b : "))
c = int(input("Entrez le cote c : "))

if a == b == c:
    print("C'est un triangle équilatéral !")
elif (a == b and a != c ) | (c == a and c != b) | (b == c and b != a):
    print("C'est un triangle isocèle !")
else:
    print("C'est un triangle quelconque !")

'''

'''

Exercice 4 : 

4. Entrer la taille pour les côtés a, b, c et d d'un quadrilatère. Afficher si ce quadrilatère est un
losange (a = b = c = d), un parallélogramme (a = c et b = d) ou une autre forme. Les
valeurs sont des flottants.

'''

'''

a = float(input("Entrez le cote a : "))
b = float(input("Entrez le cote b : "))
c = float(input("Entrez le cote c : "))
d = float(input("Entrez le cote d : "))

if a == b == c == d:
    print("C'est un losange !")
elif a == c and b == d:
    print("C'est un parallelogramme")
else:
    print("C'est une autre forme !")

'''