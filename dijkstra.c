#include "dijkstra.h"
#include "liste_noeud.h"
#include "grille.h"
#include <stdlib.h>
#include <stdio.h>

// algo C (je voyais pas trop l'intérêt de le mettre dans le .h )
static void construire_chemin_vers(coord_t n, coord_t source, liste_noeud_t* visites, liste_noeud_t* chemin) {
    if (!memes_coord(n, source)) {
        // (C-1) Soit n_p = prec(n)
        coord_t n_p = precedent_noeud_liste(visites, n);
        // (C-3.1) Appel récursif vers le précédent
        construire_chemin_vers(n_p, source, visites, chemin);
        // (C-3.2) Ajouter au chemin le noeud n_p
        float cout_np = cout_noeud_liste(visites, n_p);
        coord_t prec_np = precedent_noeud_liste(visites, n_p);
        inserer_noeud_liste(chemin, n_p, cout_np, prec_np);
    }
    // ig si la condition n'est pas remplie ça ne fait plus rien et algo fini 
} 

// algo D 
float dijkstra(grille_t grille, coord_t source, coord_t destination, float seuil, liste_noeud_t** chemin) {
    liste_noeud_t* a_visiter = creer_liste();
    liste_noeud_t* visites = creer_liste();
    float resultat_cout = COUT_INFINI;
    bool trouve = false;
    // (D-1) Ajouter le noeud de départ à cout 0
    inserer_noeud_liste(a_visiter, source, 0.0, source);
    // (D-2) Tant qu'il existe noeud, faire :
    while (!est_vide_liste(a_visiter) && !trouve) {
        // (D-2.1) Noeud courant n_c de coût minimal
        coord_t n_c = min_noeud_liste(a_visiter);
        float cout_nc = cout_noeud_liste(a_visiter, n_c);
        coord_t prec_nc = precedent_noeud_liste(a_visiter, n_c);
        // (D-2.2) Ajouter n_c dans Visités
        inserer_noeud_liste(visites, n_c, cout_nc, prec_nc);
        // (D-2.3) Supprimer n_c de AVisiter
        supprimer_noeud_liste(a_visiter, n_c);
        if (memes_coord(n_c, destination)) {
            resultat_cout = cout_nc;
            trouve = true; 
        } else {
            // (D-2.4) Exploration des voisins (que si on trouve le chemin du coup)
            coord_t* voisins = NULL;
            size_t nb_voisins = get_voisins(grille, n_c, seuil, &voisins);
            if (nb_voisins > 0 && voisins != NULL) { // On ne traite que s'il y a des voisins
                for (size_t i = 0; i < nb_voisins; i++) {
                    coord_t n_v = voisins[i];
                    if (!contient_noeud_liste(visites, n_v)) {
                        float delta_prime = cout_nc + 1.0; 
                        float delta = cout_noeud_liste(a_visiter, n_v);
                        if (delta_prime < delta) {
                            inserer_noeud_liste(a_visiter, n_v, delta_prime, n_c);
                        }
                    }
                }
                free(voisins); 
                voisins = NULL;
            }
        }

    if (chemin != NULL) {
        if (resultat_cout != COUT_INFINI) {
            *chemin = creer_liste();
            construire_chemin_vers(destination, source, visites, *chemin);
            inserer_noeud_liste(*chemin, destination, resultat_cout, precedent_noeud_liste(visites, destination));
        } else {
            *chemin = NULL;
        }
    }

    detruire_liste(&a_visiter);
    detruire_liste(&visites);
    return resultat_cout;
}