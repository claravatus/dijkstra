#ifndef __LISTE_NOEUD_H__
#define __LISTE_NOEUD_H__
#include "coord.h"
#include <stdbool.h>

#define COUT_INFINI (1.0/0.0) // ce qui équivaut à un "infini" normalement puisque c'est pas possibe la division par 0
#define INVALIDE (coord_t){.abscisse = -1, .ordonnee = -1} // utile pour que le programme dise si une cellule existe

typedef struct liste_noeud_s liste_noeud_t;
liste_noeud_t* creer_liste();

void detruire_liste(liste_noeud_t** liste);

bool est_vide_liste(const liste_noeud_t* liste);

bool contient_noeud_liste(const liste_noeud_t* liste, coord_t noeud);

bool contient_arrete_liste(const liste_noeud_t* liste, coord_t n1, coord_t n2); 

float cout_noeud_liste(const liste_noeud_t* liste, coord_t noeud);

coord_t precedent_noeud_liste(const liste_noeud_t* liste, coord_t noeud);

coord_t min_noeud_liste(const liste_noeud_t* liste);

void inserer_noeud_liste(liste_noeud_t* liste, coord_t noeud, float cout, coord_t precedent);

void supprimer_noeud_liste(liste_noeud_t* liste, coord_t noeud);

#endif