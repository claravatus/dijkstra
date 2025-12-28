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
    cellule_t* trouve = NULL; // initialisation
    if (liste != NULL) {
        cellule_t* courante = (*liste).tete;
        while (courante != NULL && trouve == NULL) { // on cherche tant qu'on a pas trouvé ou qu'on est pas à la fin
            if (coord_egal((*courante).noeud, noeud)) {
                trouve = courante; 
            } else {
                courante = (*courante).suivant; 
            }
        }
    }
    return trouve;
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
    float resultat = COUT_INFINI; // initialisation 
    cellule_t* cellule = chercher_cellule(liste, noeud);
    if (cellule != NULL) {
        resultat = (*cellule).cout;
    }
    return resultat ;
}


coord_t precedent_noeud_liste(const liste_noeud_t* liste, coord_t noeud) {
    coord_t resultat = INVALIDE;
    cellule_t* cellule = chercher_cellule(liste, noeud);
    if (cellule != NULL) {
        resultat = (*cellule).precedent;
    }
    return resultat;
}

coord_t min_noeud_liste(const liste_noeud_t* liste) {
    coord_t resultat = INVALIDE;
    if (liste != NULL && (*liste).tete != NULL) {
        cellule_t* courante = (*liste).tete;
        cellule_t* cellule_min = (*liste).tete;
        while (courante != NULL) {
            if ((*courante).cout < (*cellule_min).cout) {
                cellule_min = courante; 
            }
            courante = (*courante).suivant;
        }
        resultat = (*cellule_min).noeud;
    }
    return resultat; 
}

void inserer_noeud_liste(liste_noeud_t* liste, coord_t noeud, float cout, coord_t precedent) {
    if (liste != NULL) { // est-ce que le noeud existe 
        cellule_t* cellule = chercher_cellule(liste, noeud);
        if (cellule != NULL) { // le point existe déjà donc on modif juste ce qu'on veut 
            (*cellule).cout = cout;
            (*cellule).precedent = precedent;
        } 
        else { // le point est nouveau : on le rajoute 
            cellule_t* nouvelle = malloc(sizeof(*nouvelle));
            if (nouvelle != NULL) {
                (*nouvelle).noeud = noeud;
                (*nouvelle).cout = cout;
                (*nouvelle).precedent = precedent;
                (*nouvelle).suivant = (*liste).tete;
                (*liste).tete = nouvelle;
            }
        }
    }
}

void supprimer_noeud_liste(liste_noeud_t* liste, coord_t noeud) {
    if (liste != NULL && (*liste).tete != NULL) {
        cellule_t* courante = (*liste).tete;
        cellule_t* precedente = NULL;
        cellule_t* a_supprimer = NULL;
        while (courante != NULL && a_supprimer == NULL) {
            if (coord_egal((*courante).noeud, noeud)) {
                a_supprimer = courante; // ig on a trouvé ici
            } else {
                precedente = courante; 
                courante = (*courante).suivant;
            }
        }
        if (a_supprimer != NULL) {
            if (precedente == NULL) {
                (*liste).tete = (*a_supprimer).suivant;
            } else {
                (*precedente).suivant = (*a_supprimer).suivant;
            }
            free(a_supprimer); 
        }
    }
}

