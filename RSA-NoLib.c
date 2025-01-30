#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

// Fonction pour calculer le PGCD
void pgcd(mpz_t result, mpz_t a, mpz_t b) {
    mpz_gcd(result, a, b);
}

// Algorithme d'Euclide étendu pour trouver l'inverse modulaire
// Calcul de l'inverse modulaire (bezout) 
void bezout(mpz_t d, mpz_t a, mpz_t b, mpz_t x, mpz_t y) {
    mpz_t temp, q, r, x0, x1, y0, y1;
    mpz_inits(temp, q, r, x0, x1, y0, y1, NULL);

    mpz_set_ui(x0, 1);
    mpz_set_ui(x1, 0);
    mpz_set_ui(y0, 0);
    mpz_set_ui(y1, 1);

    while (mpz_cmp_ui(b, 0) != 0) {
        gmp_printf("a = %Zd, b = %Zd\n", a, b);  // Debugage, affichage de a et b
        mpz_fdiv_qr(q, r, a, b);

        if (mpz_cmp_ui(r, 0) == 0) {
            gmp_printf("Le reste devient zéro, arrêt de l'algorithme.\n");
            break;
        }

        mpz_set(a, b);
        mpz_set(b, r);

        mpz_mul(temp, q, x1);
        mpz_sub(x, x0, temp);
        mpz_set(x0, x1);
        mpz_set(x1, x);

        mpz_mul(temp, q, y1);
        mpz_sub(y, y0, temp);
        mpz_set(y0, y1);
        mpz_set(y1, y);
    }

    mpz_set(d, x0);
    if (mpz_cmp_ui(d, 0) < 0) {
        mpz_add(d, d, b);
    }

    gmp_printf("Valeur de d après bezout : %Zd\n", d);  // Debugage, Vérification de d
    mpz_clears(temp, q, r, x0, x1, y0, y1, NULL);
}

// Fonction d'exponentiation modulaire
void puissance(mpz_t result, mpz_t base, mpz_t exponent, mpz_t modulo) {
    mpz_t temp;
    mpz_init(temp);
    mpz_set_ui(result, 1);
    mpz_mod(temp, base, modulo);

    while (mpz_cmp_ui(exponent, 0) > 0) {
        if (mpz_tstbit(exponent, 0)) {
            mpz_mul(result, result, temp);
            mpz_mod(result, result, modulo);
        }
        mpz_mul(temp, temp, temp);
        mpz_mod(temp, temp, modulo);
        mpz_fdiv_q_2exp(exponent, exponent, 1);
    }
    mpz_clear(temp);
}

// Conversion du texte en nombre
void to_number(mpz_t result, const char *text) {
    mpz_set_ui(result, 0);
    while (*text) {
        mpz_mul_ui(result, result, 256);
        mpz_add_ui(result, result, (unsigned char)(*text));
        text++;
    }
}

// Conversion du nombre en texte
void from_number(mpz_t number, char *output) {
    size_t i = 0;
    mpz_t temp;
    mpz_init(temp);

    while (mpz_cmp_ui(number, 0) > 0) {
        mpz_fdiv_qr_ui(temp, number, number, 256);
        output[i++] = (char)mpz_get_ui(temp);
    }
    output[i] = '\0';

    for (size_t j = 0; j < i / 2; j++) {
        char tmp = output[j];
        output[j] = output[i - j - 1];
        output[i - j - 1] = tmp;
    }

    mpz_clear(temp);
}

int main() {
    mpz_t p, q, n, z, e, d, M, C, D, gcd;
    mpz_inits(p, q, n, z, e, d, M, C, D, gcd, NULL);

    mpz_set_str(p, "12371247788555446551320478301289", 10);
    mpz_set_str(q, "54684665222227225444533546543532501", 10);
    mpz_mul(n, p, q);
    gmp_printf("n = p * q = %Zd\n", n);

    mpz_t p_original, q_original;
    mpz_inits(p_original, q_original, NULL);
    mpz_set(p_original, p);
    mpz_set(q_original, q);

    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    mpz_mul(z, p, q);
    gmp_printf("φ(n) = %Zd\n", z);

    mpz_set_str(e, "525567875157816551", 10);

    // Vérification du PGCD de e et φ(n)
    pgcd(gcd, e, z);
    gmp_printf("PGCD de e et φ(n) : %Zd\n", gcd);
    if (mpz_cmp_ui(gcd, 1) != 0) {
        printf("Erreur : e n'est pas premier avec φ(n)\n");
        mpz_clears(p_original, q_original, gcd, NULL);
        return 1;
    } else {
        printf("Tout va bien, e est bien premier avec φ(n)\n");
    }

    bezout(d, e, z, p_original, q_original);
    mpz_mod(d, d, z);
    gmp_printf("L'inverse de e mod φ(n) est : d = %Zd\n", d);

    // Vérification si d est positif
    if (mpz_cmp_ui(d, 0) < 0) {
        mpz_add(d, d, z); 
    }

    const char *Message = "Donnez moi un poste de pentester svp";
    gmp_printf("Message original : %s\n", Message);

    to_number(M, Message);
    gmp_printf("Message numérisé : M = %Zd\n", M);

    puissance(C, M, e, n);
    gmp_printf("Message chiffré : C = %Zd\n", C);

    puissance(D, C, d, n);
    gmp_printf("Message déchiffré (numérisé) : D = %Zd\n", D);

    if (mpz_cmp(M, D) == 0) {
        printf("Le déchiffrement a réussi, le message déchiffré est correct.\n");
    } else {
        printf("Erreur : le message déchiffré est incorrect.\n");
    }

    char message_retrouve[256];
    from_number(D, message_retrouve);
    printf("Le message déchiffré est : %s\n", message_retrouve);

    mpz_clears(p, q, n, z, e, d, M, C, D, gcd, p_original, q_original, NULL);

    return 0;
}
