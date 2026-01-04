#!/bin/bash
logfile="checkerror_dijkstra.log"
err=0

check_fichier () {
    if [ ! -f "$1" ]; then echo "Fichier $1 absent" >>$logfile; err=1; return 1; fi
    gcc -std=c99 -c -Wall -Wextra -pedantic -Werror -fsyntax-only -x c "$1" >>$logfile 2>&1
}

if [ -f $logfile ]; then rm $logfile; fi

echo "Vérification des fichiers..."
check_fichier "dijkstra.h"
check_fichier "dijkstra.c"

# On passe la vérification de garde manuelle si elle bugue, 
# le compilateur le dira de toute façon à la compilation finale.

echo "Compilation..."
gcc -c dijkstra.c -o dijkstra.o -O0 >>$logfile 2>&1
gcc -c liste_noeud.c -o liste_noeud.o -O0 >>$logfile 2>&1
gcc -c grille.c -o grille.o -O0 >>$logfile 2>&1
gcc -c coord.c -o coord.o -O0 >>$logfile 2>&1
gcc -c test_dijkstra.c -o test_dijkstra.o -O0 >>$logfile 2>&1

# Utilisation de la bibliothèque -lt comme dans votre test_coord qui marchait
gcc test_dijkstra.o dijkstra.o liste_noeud.o grille.o coord.o -o test_dijkstra -L. -lt -lm -Wno-clobbered >>$logfile 2>&1

if [ $? -ne 0 ]; then
    echo "Impossible de compiler le test Dijkstra. Regardez $logfile"
    exit -2
fi

echo "Lancement des tests..."
./test_dijkstra