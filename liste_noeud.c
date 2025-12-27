#include "liste_noeud.h"
#include <stdlib.h>

typedef struct cellule {
    coord_t noeud;
    float cout;
    coord_t precedent;
    struct cellule* suivant;
} cellule_t;

struct liste_noeud_s {
    cellule_t* tete;
};


static cellule_t* chercher_cellule(const liste_noeud_t* liste, coord_t noeud) {
    if (liste == NULL) return NULL;
    cellule_t* courante = (*liste).tete;
    while (courante != NULL) {
        if (coord_egal((*courante).noeud, noeud)) {
            return courante;
        }
        courante = (*courante).suivant;
    }
    return NULL;
}


liste_noeud_t* creer_liste() {
    liste_noeud_t* liste = malloc(sizeof(liste_noeud_t)); // on donne de la place en mémoire
    if (liste != NULL) {
        (*liste).tete = NULL;
    }
    return liste;
}


void detruire_liste(liste_noeud_t** liste) {
    if (liste == NULL || *liste == NULL) return;
    cellule_t* courante = (**liste).tete;
    while (courante != NULL) {
        cellule_t* a_supprimer = courante;
        courante = (*courante).suivant;
        free(a_supprimer);
    }
    free(*liste);
    *liste = NULL;
}

bool contient_noeud_liste(const liste_noeud_t* liste, coord_t noeud) {
    return chercher_cellule(liste, noeud) != NULL;
}


float cout_noeud_liste(const liste_noeud_t* liste, coord_t noeud) {
    cellule_t* cellule = chercher_cellule(liste, noeud);
    if (cellule != NULL) {
        return (*cellule).cout;
    }
    return COUT_INFINI;
}


coord_t precedent_noeud_liste(const liste_noeud_t* liste, coord_t noeud) {
    cellule_t* c = chercher_cellule(liste, noeud);
    if (c != NULL) {
        return (*c).precedent;
    }
    return COORDONNEE_DEFAUT;
}


coord_t min_noeud_liste(const liste_noeud_t* liste) {
    if (liste == NULL || (*liste).tete == NULL) {
        return COORDONNEE_DEFAUT;
    }
    cellule_t* courante = (*liste).tete;
    cellule_t* min = courante;
    while (courante != NULL) {
        if ((*courante).cout < (*min).cout) {
            min = courante;
        }
        courante = (*courante).suivant;
    }
    return (*min).noeud;
}

void inserer_noeud_liste(liste_noeud_t* liste, coord_t noeud, float cout, coord_t precedent) {
    if (liste == NULL) return;
    cellule_t* c = chercher_cellule(liste, noeud);
    if (c != NULL) {
        (*c).cout = cout;
        (*c).precedent = precedent;
        return;
    }
    cellule_t* nouvelle = malloc(sizeof(cellule_t));
    if (nouvelle == NULL) return;
    (*nouvelle).noeud = noeud;
    (*nouvelle).cout = cout;
    (*nouvelle).precedent = precedent;
    (*nouvelle).suivant = (*liste).tete;
    (*liste).tete = nouvelle;
}


void supprimer_noeud_liste(liste_noeud_t* liste, coord_t noeud) {
    if (liste == NULL || (*liste).tete == NULL) return;
    cellule_t* courante = (*liste).tete;
    cellule_t* precedente = NULL;
    while (courante != NULL) {
        if (coord_egal((*courante).noeud, noeud)) {
            if (precedente == NULL) {
                (*liste).tete = (*courante).suivant;
            } else {
                (*precedente).suivant = (*courante).suivant;
            }
            free(courante);
            return;
        }
        precedente = courante;
        courante = (*courante).suivant;
    }
}


