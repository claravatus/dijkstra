#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"
#include "liste_noeud.h"
#include "grille.h"
#include "coord.h"
#include "tests.h"

#define PRECISION 1e-4

int main() {
    INITIALIZE_TESTS();
    SET_ANALYSIS("test_dijkstra.csv");

    BEGIN_SECTION("dijkstra/chemin-simple")
        BEGIN_TESTI("trajet-direct-horizontal")
            // Création d'une grille 5x5 sans obstacles
            grille_t g = creer_grille(5, 5);
            coord_t src = creer_coord(0, 0);
            coord_t dst = creer_coord(2, 0);
            liste_noeud_t* chemin = NULL;

            float cout = dijkstra(g, src, dst, 0.5, &chemin);

            // Coût attendu : 2.0 (0,0 -> 1,0 -> 2,0)
            ASSERT_EQ_F(cout, 2.0, PRECISION);
            ASSERT(chemin != NULL);
            
            detruire_liste(&chemin);
            detruire_grille(g);
        END_TEST

        BEGIN_TESTI("trajet-avec-obstacle")
            // Grille 3x3
            // S . .
            // # # .
            // . . D
            grille_t g = creer_grille(3, 3);
            coord_t src = creer_coord(0, 0);
            coord_t dst = creer_coord(2, 2);
            liste_noeud_t* chemin = NULL;
            float cout = dijkstra(g, src, dst, 0.5, &chemin);
            ASSERT_EQ_F(cout, 4.0, PRECISION);
            ASSERT(chemin != NULL);
            detruire_liste(&chemin);
            detruire_grille(g);
        END_TEST

        REPORT_TO_STDOUT;
    END_SECTION()

    BEGIN_SECTION("dijkstra/cas-limites")
        BEGIN_TESTI("source-egale-destination")
            grille_t g = creer_grille(3, 3);
            coord_t src = creer_coord(1, 1);
            liste_noeud_t* chemin = NULL;

            float cout = dijkstra(g, src, src, 0.5, &chemin);

            ASSERT_EQ_F(cout, 0.0, PRECISION);
            ASSERT(chemin != NULL);

            detruire_liste(&chemin);
            detruire_grille(g);
        END_TEST

        REPORT_TO_STDOUT;
    END_SECTION()

    END_ANALYSIS;
    return 0;
}