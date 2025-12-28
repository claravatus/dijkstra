#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <stdbool.h>
#include <stddef.h>
#include "coord.h"
#include "grille.h"
#include "liste_noeud.h"

float dijkstra(
        grille_t grille,
        coord_t source, coord_t destination,
        float seuil,
        liste_noeud_t** chemin);


#endif