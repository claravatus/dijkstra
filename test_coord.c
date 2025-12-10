// test_coord.c
#include <stdio.h>    // Pour printf
#include <assert.h>   // Pour la fonction assert()
#include <math.h>     // Pour les comparaisons de nombres flottants (fabs)
#include "coord.h"    // Inclut votre structure et les déclarations de fonctions

// Définition d'une marge d'erreur pour les comparaisons de floats (nécessaire)
#define EPSILON 0.0001

// Fonction d'aide pour comparer deux flottants
int float_egal(float a, float b) {
    // Vérifie si la valeur absolue de la différence est inférieure à l'EPSILON
    return fabs(a - b) < EPSILON;
}

// Fonction principale de test
void test_module_coord() {
    printf("--- Démarrage des tests du module coord ---\n\n");

    // ----------------------------------------------------
    // TEST 1 : Création et Getters
    // ----------------------------------------------------
    printf("1. Test de creer_coord et get_x/get_y...\n");
    coord_t p1 = creer_coord(10, 20);

    // Vérification
    assert(get_x(p1) == 10);
    assert(get_y(p1) == 20);
    printf("   -> Création et getters OK.\n");

    // ----------------------------------------------------
    // TEST 2 : Setters (Modification)
    // ----------------------------------------------------
    printf("2. Test de set_x et set_y...\n");
    // Rappel: Les setters fonctionnent sur un pointeur dans la version corrigée
    set_x(&p1, -5);
    set_y(&p1, 0);

    // Vérification
    assert(get_x(p1) == -5);
    assert(get_y(p1) == 0);
    printf("   -> Setters OK.\n");

    // ----------------------------------------------------
    // TEST 3 : Comparaison de coordonnées (memes_coord)
    // ----------------------------------------------------
    printf("3. Test de memes_coord...\n");
    coord_t p2 = creer_coord(5, 5);
    coord_t p3 = creer_coord(5, 5);
    coord_t p4 = creer_coord(1, 2);

    // Vérification de l'égalité
    assert(memes_coord(p2, p3) == true);
    // Vérification de l'inégalité
    assert(memes_coord(p2, p4) == false);
    printf("   -> Comparaison (memes_coord) OK.\n");

    // ----------------------------------------------------
    // TEST 4 : Translation
    // ----------------------------------------------------
    printf("4. Test de translation...\n");
    coord_t p5 = creer_coord(10, 10);
    coord_t p5_trans = translation(p5, 5, -2); // Résultat attendu : (15, 8)

    // Vérification
    assert(get_x(p5_trans) == 15);
    assert(get_y(p5_trans) == 8);
    printf("   -> Translation OK.\n");


    // ----------------------------------------------------
    // TEST 5 : Distance Euclidienne
    // ----------------------------------------------------
    printf("5. Test de distance_euclidienne...\n");
    coord_t a = creer_coord(1, 1);
    coord_t b = creer_coord(4, 5);

    // Calcul manuel attendu : sqrt((4-1)^2 + (5-1)^2) = sqrt(3^2 + 4^2) = sqrt(9 + 16) = sqrt(25) = 5.0
    float distance_attendue = 5.0f;
    float distance_obtenue = distance_euclidienne(a, b);

    // Vérification des flottants
    assert(float_egal(distance_obtenue, distance_attendue));
    
    // Cas simple : distance à soi-même
    assert(float_egal(distance_euclidienne(a, a), 0.0f));
    
    // Cas avec racine carrée non entière : (0,0) à (1,1) -> sqrt(2) ≈ 1.414213...
    coord_t zero = creer_coord(0, 0);
    coord_t un_un = creer_coord(1, 1);
    assert(float_egal(distance_euclidienne(zero, un_un), 1.414213f));
    
    printf("   -> Distance Euclidienne OK.\n");
    
    printf("\n--- Tous les tests ont réussi ! (Asserts OK) ---\n");
}

int main() {
    test_module_coord();
    return 0;
}