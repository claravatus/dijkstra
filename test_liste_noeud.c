#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "liste_noeud.h"
#include "coord.h"
#include "tests.h"

#define PRECISION 1e-4

int main() {
    INITIALIZE_TESTS();
    SET_ANALYSIS("test_liste_noeud.csv");

    BEGIN_SECTION("liste/gestion-basique")
        BEGIN_TESTI("creation-est_vide")
            liste_noeud_t* l = creer_liste();
            ASSERT(l != NULL);
            ASSERT(est_vide_liste(l));
            detruire_liste(&l);
            ASSERT(l == NULL); 
        END_TEST

        BEGIN_TESTI("insertion-contient")
            liste_noeud_t* l = creer_liste();
            coord_t c1 = creer_coord(10, 10);
            inserer_noeud_liste(l, c1, 5.5, INVALIDE);
            
            ASSERT(!est_vide_liste(l));
            ASSERT(contient_noeud_liste(l, c1));
            ASSERT_EQ_F(cout_noeud_liste(l, c1), 5.5, PRECISION);
            
            detruire_liste(&l);
        END_TEST

        REPORT_TO_STDOUT;
        REPORT_ANALYSIS;
    END_SECTION()

    BEGIN_SECTION("liste/recherche-et-couts")
        BEGIN_TESTI("precedent-et-cout")
            liste_noeud_t* l = creer_liste();
            coord_t source = creer_coord(0, 0);
            coord_t destination = creer_coord(1, 1);
            
            inserer_noeud_liste(l, destination, 12.0, source);
            
            ASSERT(contient_noeud_liste(l, destination));
            ASSERT_EQ_F(cout_noeud_liste(l, destination), 12.0, PRECISION);
            
            coord_t prec = precedent_noeud_liste(l, destination);
            ASSERT(memes_coord(prec, source));
            
            detruire_liste(&l);
        END_TEST

        BEGIN_TESTI("noeud-inexistant")
            liste_noeud_t* l = creer_liste();
            coord_t c = creer_coord(5, 5);
            ASSERT_EQ_F(cout_noeud_liste(l, c), COUT_INFINI, PRECISION);
            coord_t prec = precedent_noeud_liste(l, c);
            ASSERT(memes_coord(prec, INVALIDE));
            
            detruire_liste(&l);
        END_TEST

        REPORT_TO_STDOUT;
        REPORT_ANALYSIS;
    END_SECTION()

    BEGIN_SECTION("liste/algorithme-min")
        BEGIN_TESTI("recherche-min")
            liste_noeud_t* l = creer_liste();
            coord_t c1 = creer_coord(1, 1); // coût 10
            coord_t c2 = creer_coord(2, 2); // coût 5  <-- Min
            coord_t c3 = creer_coord(3, 3); // coût 15
            
            inserer_noeud_liste(l, c1, 10.0, INVALIDE);
            inserer_noeud_liste(l, c2, 5.0, INVALIDE);
            inserer_noeud_liste(l, c3, 15.0, INVALIDE);
            
            coord_t min = min_noeud_liste(l);
            ASSERT(memes_coord(min, c2));
            
            detruire_liste(&l);
        END_TEST

        REPORT_TO_STDOUT;
        REPORT_ANALYSIS;
    END_SECTION()

    BEGIN_SECTION("liste/suppression")
        BEGIN_TESTI("supprimer-noeud")
            liste_noeud_t* l = creer_liste();
            coord_t c1 = creer_coord(1, 1);
            
            inserer_noeud_liste(l, c1, 10.0, INVALIDE);
            ASSERT(contient_noeud_liste(l, c1));
            
            supprimer_noeud_liste(l, c1);
            ASSERT(!contient_noeud_liste(l, c1));
            ASSERT(est_vide_liste(l));
            
            detruire_liste(&l);
        END_TEST

        REPORT_TO_STDOUT;
        REPORT_ANALYSIS;
    END_SECTION()

    END_ANALYSIS;

    return 0;
}