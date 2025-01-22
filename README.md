# Système de Chiffrement RSA en Python

## Description

Ce projet implémente un système de chiffrement RSA en Python. Il montre l'utilisation des concepts mathématiques sous-jacents au RSA, tels que le calcul du PGCD, l'algorithme d'Euclide étendu pour trouver l'inverse modulaire et l'exponentiation modulaire pour chiffrer et déchiffrer des messages. Le système utilise une clé publique pour le chiffrement et une clé privée pour le déchiffrement, conformément aux principes de la cryptographie asymétrique.

## Fonctionnalités

- **Calcul du PGCD** : Utilisation de l'algorithme d'Euclide pour calculer le PGCD de deux nombres.
- **Algorithme d'Euclide étendu** : Utilisation de l'algorithme d'Euclide étendu pour calculer l'inverse modulaire et les coefficients de Bézout.
- **Exponentiation modulaire** : Algorithme d'exponentiation rapide pour le chiffrement et le déchiffrement des messages.
- **Conversion entre texte et nombre** : Conversion du texte en nombre pour le chiffrement et inversement.
- **Système RSA** : Mise en œuvre complète du chiffrement et du déchiffrement RSA, avec génération des clés publique et privée.

## Fonctionnement

Le système RSA repose sur trois étapes principales :
1. **Génération des clés** : Utilisation de deux grands nombres premiers `p` et `q` pour calculer `n`, et du calcul de φ(n) pour déterminer `e` et `d`.
2. **Chiffrement** : Le message est converti en un nombre, puis chiffré en utilisant la clé publique (composée de `e` et `n`).
3. **Déchiffrement** : Le message chiffré est déchiffré en utilisant la clé privée (composée de `d` et `n`), récupérant ainsi le message original.

## Exécution du Projet

Le projet implémente les étapes suivantes :
1. Calcul du PGCD et vérification que `e` est premier avec φ(n).
2. Utilisation de l'algorithme de Bézout pour calculer `d`, l'inverse modulaire de `e`.
3. Conversion du message en nombre et chiffrement avec la clé publique.
4. Déchiffrement du message avec la clé privée et récupération du message original.

### Exemple

Le message "Donnez moi un poste de pentester svp" est converti en un nombre, puis chiffré et déchiffré pour démontrer le fonctionnement du système RSA.

## Prérequis

- Python 3

## Utilisation

1. Clonez ce projet ou téléchargez le fichier Python.
2. Exécutez le fichier Python pour voir l'implémentation du chiffrement et du déchiffrement RSA en action.

## Remarques

Ce projet est une démonstration simplifiée du chiffrement RSA avec des valeurs relativement petites pour des raisons de lisibilité. Dans un contexte réel, des nombres beaucoup plus grands seraient utilisés pour garantir la sécurité des communications.
