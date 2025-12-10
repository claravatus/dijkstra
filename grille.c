#define _GNU_SOURCE
#include "grille.h"
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>

/**
 * coord_lin : fonction statique (de module) qui transforme des coordonnées
 * cartésiennes dans la grille en coordonnées "linéaires" permettant d'adresser
 * le tableau contenu dans la grille.
 *
 * @param grille grille avec le bon système de coordonnées
 * @param position position dans la grille en coordonnées cartésiennes entières
 * @return position dans le tableau en coordonnée linéaire
 */
static size_t coord_lin(grille_t grille, coord_t position) {
    int x = get_x(position); 
    int y = get_y(position); 
    assert(dans_les_bornes(grille, position)); 
    return (size_t)(y * grille->largeur + x);
}

grille_t creer_grille(int largeur, int profondeur) {
    grille_t grille = (grille_t)malloc(sizeof(struct grille_t));
    grille->largeur = largeur;
    grille->profondeur = profondeur;
    size_t taille = (size_t)largeur * profondeur;
    grille->hauteurs = (float*)calloc(taille, sizeof(float));
    return grille;
}

void detruire_grille(grille_t grille) {
    if (grille != NULL) {
        free(grille->hauteurs);
        free(grille);
    }
}

int get_largeur(grille_t grille) {
    return grille->largeur;
}

int get_profondeur(grille_t grille) {
    return grille->profondeur;
}

bool dans_les_bornes(grille_t grille, coord_t position) {
    int x = get_x(position);
    int y = get_y(position);
    bool x_ok = (x >= 0) && (x < grille->largeur);
    bool y_ok = (y >= 0) && (y < grille->profondeur);
    return x_ok && y_ok;
}

coord_t inferieur_gauche(grille_t grille) {
    return creer_coord(0, 0); 
}

coord_t superieur_droit(grille_t grille) {
    return creer_coord(grille->largeur - 1, grille->profondeur - 1);
}

void set_hauteur(grille_t grille, coord_t position, float hauteur) {
    size_t index = coord_lin(grille, position);
    grille->hauteurs[index] = hauteur;
}

float get_hauteur(grille_t grille, coord_t position) {
    size_t index = coord_lin(grille, position);
    return grille->hauteurs[index];
}

size_t get_voisins(grille_t grille, coord_t position, float seuil, coord_t** voisins) {
    const int dx[] = {0, 0, 1, -1};
    const int dy[] = {1, -1, 0, 0};
    float hauteur_centrale = get_hauteur(grille, position);
    size_t nb_voisins = 0;
    coord_t voisins_temp[4]; 
    int x_centre = get_x(position);
    int y_centre = get_y(position);
    for (int i = 0; i < 4; i++) {
        coord_t voisin_pos = creer_coord(x_centre + dx[i], y_centre + dy[i]);
        if (dans_les_bornes(grille, voisin_pos)) {
            float hauteur_voisin = get_hauteur(grille, voisin_pos);
            float denivele = fabsf(hauteur_centrale - hauteur_voisin); 
            if (denivele <= seuil) {
                voisins_temp[nb_voisins] = voisin_pos;
                nb_voisins++;
            }
        }
    }
    *voisins = (coord_t*)malloc(nb_voisins * sizeof(coord_t));
    for (size_t i = 0; i < nb_voisins; i++) {
        (*voisins)[i] = voisins_temp[i];
    } 
    return nb_voisins;
}


