#!/bin/bash
# Script de test pour la conformité de liste_noeud

logfile="checkerror_liste.log"
err=0

check_fichier () {
    if [ ! -f "$1" ]; then
        echo "Je ne trouve pas le fichier $1 ! Vérifiez que vous êtes bien dans le bon répertoire..."
        echo "Fichier $1 absent" >>$logfile
        err=1
        return 1
    fi

    echo "Vérification de la syntaxe pour $1 :" >>$logfile
    echo "gcc -std=c99 -c -Wall -Wextra -pedantic -Werror -fsyntax-only -x c $1" >>$logfile 
    gcc -std=c99 -c -Wall -Wextra -pedantic -Werror -fsyntax-only -x c "$1" >>$logfile 2>&1

    if [ $? -ne 0 ]; then
        echo "Je n'arrive pas à compiler le fichier $1... Veuillez corriger les erreurs et recommencer"
        err=1
    fi
}

check_garde () {
    include="$1"
    anchor="$2"
    tmpfile="__tmp_${include}"
    if [ -f "${tmpfile}" ]; then rm "${tmpfile}"; fi
    sed "/$anchor/a static const int x = 1;" ${include} > ${tmpfile}
 
    read -r -d '' RESULT <<END_DOC
#include "${tmpfile}"
#include "${tmpfile}"
void test() {}
END_DOC

    echo "" >>$logfile
    echo "[le header ${include} est correctement gardé]" >>$logfile
    echo "$RESULT" | gcc -c -fsyntax-only -x c - >>$logfile 2>&1
    rm "${tmpfile}"

    if [[ $? -ne 0 ]]; then
        echo "Erreur : le header ${include} n'est pas correctement gardé !"
        err=1
        return 1
    fi
    return 0
}

check () {
    name="$1"
    include="$2"
    code="$3"
    errmsg="$4"

    read -r -d '' RESULT <<END_DOC
#include "coord.h"
#include "${include}"
void test() {
${code}
}
END_DOC

    echo "" >>$logfile
    echo "[${name}]" >>$logfile
    echo "$RESULT" | gcc -c -Wall -Wextra -pedantic -Werror -fsyntax-only -x c - >>$logfile 2>&1

    if [[ $? -ne 0 ]]; then
        echo "Erreur : ${errmsg}"
        err=1
        return 1
    fi
    return 0
}

if [ -f $logfile ]; then rm $logfile; fi

echo "Vérification des fichiers..."
check_fichier "liste_noeud.h"
check_fichier "liste_noeud.c"

if [ $err -ne 0 ]; then
    echo "Les erreurs des fichiers testés empêchent de poursuivre le test..."
    exit -1
fi

check_garde "liste_noeud.h" "creer_liste();"

check \
    "Définition de liste_noeud_t" \
    "liste_noeud.h" \
    "liste_noeud_t* l; (void) l;" \
    "Le type liste_noeud_t n'est pas accessible" \
&& check \
    "Fonction est_vide_liste" \
    "liste_noeud.h" \
    "liste_noeud_t* l = NULL; bool b = est_vide_liste(l); (void) b;" \
    "La fonction est_vide_liste n'a pas la bonne signature ou manque stdbool.h" \
&& check \
    "Fonction inserer_noeud_liste" \
    "liste_noeud.h" \
    "coord_t c = {0,0}; inserer_noeud_liste(NULL, c, 1.0, c);" \
    "La fonction inserer_noeud_liste n'a pas la bonne signature" \
&& check \
    "Fonction cout_noeud_liste" \
    "liste_noeud.h" \
    "coord_t c = {0,0}; float f = cout_noeud_liste(NULL, c); (void) f;" \
    "La fonction cout_noeud_liste n'a pas la bonne signature" \
&& check \
    "Fonction min_noeud_liste" \
    "liste_noeud.h" \
    "coord_t c = min_noeud_liste(NULL); (void) c;" \
    "La fonction min_noeud_liste n'a pas la bonne signature"

if [ $err -ne 0 ]; then
    echo "Le fichier liste_noeud.h n'est pas conforme."
    exit -2
fi

echo "Compilation du binaire de test..."

# Compilation des objets
gcc -c test_liste_noeud.c -o test_liste_noeud.o -O0
gcc -c liste_noeud.c -o liste_noeud.o -O0
gcc -c coord.c -o coord.o -O0
gcc test_liste_noeud.o liste_noeud.o coord.o -o test_liste_noeud -L. -lt -lm

if [ $? -ne 0 ]; then
    echo "Impossible de compiler le test :("
    exit -3
fi

echo "Check ok. Lancement des tests..."
./test_liste_noeud