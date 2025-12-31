#include "dijkstra.h"
#include <stdio.h>
#include <assert.h>

int main() {
    // 1. Initialisation de la grille (dépend de votre implémentation de grille_t)
    grille_t grille = creer_grille(5, 5); 
    
    coord_t source = {0, 0};
    coord_t destination = {4, 4};
    float seuil = 0.5; // Exemple de seuil de franchissement
    liste_noeud_t* chemin = NULL;

    printf("Exécution de Dijkstra...\n");
    float cout = dijkstra(grille, source, destination, seuil, &chemin);

    // 2. Vérification des résultats
    if (cout == COUT_INFINI) {
        printf("Aucun chemin trouvé.\n");
    } else {
        printf("Chemin trouvé ! Coût total : %.2f\n", cout);
        
        // 3. Affichage du chemin pour vérification visuelle
        printf("Étapes du chemin :\n");
        // Supposons une fonction d'affichage ou une boucle sur la liste
        // afficher_liste(chemin);
    }

    // 4. Nettoyage
    if (chemin) detruire_liste(&chemin);
    // detruire_grille(grille);

    return 0;
}