#include "dijkstra.h"
#include "liste_noeud.h"
#include <stdlib.h>
#include <stdio.h>

static void construire_chemin_vers(liste_noeud_t* cellule_connue, coord_t actuel, liste_noeud_t* chemin) {
    if (memes_coord(actuel, INVALIDE)) {
        return;
    }
    coord_t cellule_suite = precedent_noeud_liste(cellule_connue, actuel);
    float cout = cout_noeud_liste(cellule_connue, actuel);
    construire_chemin_vers(cellule_connue, cellule_suite, chemin);
    inserer_noeud_liste(chemin, actuel, cout, cellule_suite);
}

float dijkstra(grille_t grille, coord_t source, coord_t destination, float seuil, liste_noeud_t** chemin) {
    liste_noeud_t* a_visiter = creer_liste();
    liste_noeud_t* deja_vus = creer_liste();
    inserer_noeud_liste(a_visiter, source, 0.0, INVALIDE);
    float resultat_cout = COUT_INFINI;
    // algo D ig
    while (!est_vide_liste(a_visiter)) {
        coord_t coord1 = min_noeud_liste(a_visiter);
        float cout_coord1 = cout_noeud_liste(a_visiter, coord1);
        coord_t prec_coord1 = precedent_noeud_liste(a_visiter, coord1);
        inserer_noeud_liste(deja_vus, coord1, cout_coord1, prec_coord1);
        supprimer_noeud_liste(a_visiter, coord1);
        if (memes_coord(coord1, destination)) {
            resultat_cout = cout_coord1;
            break;
        }
        coord_t* voisins = NULL;
        size_t nb_voisins = get_voisins(grille, coord1, seuil, &voisins);

        for (size_t i = 0; i < nb_voisins; i++) {
            coord_t coord2 = voisins[i];
            float nouveau_cout = cout_coord1 + 1.0;
            if (!contient_noeud_liste(deja_vus, coord2)) {
                if (contient_noeud_liste(a_visiter, coord2)) {
                    if (nouveau_cout < cout_noeud_liste(a_visiter, coord2)) {
                        supprimer_noeud_liste(a_visiter, coord2);
                        inserer_noeud_liste(a_visiter, coord2, nouveau_cout, coord1);
                    }
                } else {
                    inserer_noeud_liste(a_visiter, coord2, nouveau_cout, coord1);
                }
            }
        }
        free(voisins); 
    }
    // ça c l'algo C 
    if (chemin != NULL) {
        if (resultat_cout != COUT_INFINI) {
            *chemin = creer_liste();
            construire_chemin_vers(deja_vus, destination, *chemin);
        } else {
            *chemin = NULL; 
        }
    }
    detruire_liste(&a_visiter);
    detruire_liste(&deja_vus);

    return resultat_cout;
}