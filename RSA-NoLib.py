import math

# Fonction pour calculer le PGCD 
def pgcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

# Fonction de l'algorithme d'Euclide étendu (pour trv l'inverse modulaire)
def bezout(a, b):
    x0, x1, y0, y1 = 1, 0, 0, 1
    while b != 0:
        q, a, b = a // b, b, a % b
        x0, x1 = x1, x0 - q * x1
        y0, y1 = y1, y0 - q * y1
    return a, x0, y0  # a = PGCD, x0 = coefficient de Bézout

# Fonction d'exponentiation modulaire (pr chiffrer/déchiffrer)
def puissance(base, exponent, modulo):
    result = 1
    base = base % modulo
    while exponent > 0:
        if (exponent % 2) == 1:  # Si exponent est impair
            result = (result * base) % modulo
        exponent = exponent >> 1  # Divise exponent par 2
        base = (base * base) % modulo
    return result

# Conversion du texte en nombre
def to_number(text):
    number = 0
    for char in text:
        number = number * 256 + ord(char)  # Chaque caractère est codé sur 1 octet
    return number

# Conversion du nombre en texte
def from_number(number):
    chars = []
    while number > 0:
        chars.append(chr(number % 256))  # On récupère les caractères un par un
        number //= 256
    return ''.join(reversed(chars))

# Système RSA

# Deux grands nombres premiers p et q
p = 12371247788555446551320478301289
q = 54684665222227225444533546543532501
n = p * q
print(n, "égal à p*q")

# On calcule φ(n) = (p-1)*(q-1)
z = (p - 1) * (q - 1)

# Choisir e, qui doit être premier avec φ(n)
e = 525567875157816551

# Vérification que e est premier avec φ(n
def verification(e, z):
    if pgcd(e, z) != 1:
        print("Erreur : e n'est pas premier avec (p-1)*(q-1)")
    else:
        print('Tout va bien, e est bien premier avec (p-1)*(q-1)')

verification(e, z)

# Calculer d, l'inverse de e mod φ(n)
_, d, _ = bezout(e, z)
d = d % z  # On prend l'inverse modulaire de e

print("La relation de Bézout:")
print(f"e * d ≡ 1 mod φ(n) où d = {d}")
print(d, "est l'inverse de e")

# Le message à chiffrer
Message = 'Donnez moi un poste de pentester svp'
print(Message)

# Convertir le message en nombre
M = to_number(Message)
print(M, "est le message numérisé M")

# Bob chiffre le message
C = puissance(M, e, n)
print(C, "est le message chiffré")

# Alice déchiffre le message
D = puissance(C, d, n)
print(D, "devrait être égal à M")

# Vérification que le déchiffrement est correct
if M == D:
    print("Le déchiffrement a réussi, le message déchiffré est correct.")
else:
    print(f"Le message déchiffré ({D}) est différent du message original ({M}).")

# Retrouver le message à partir du nombre déchiffré
message_retrouve = from_number(D)
if message_retrouve is not None:
    print('Et enfin: ', message_retrouve)
else:
    print("Impossible de retrouver le message original à partir du nombre déchiffré.")
