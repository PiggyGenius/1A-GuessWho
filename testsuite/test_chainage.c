#include <stdlib.h>
#include <string.h>

#include "../include/ensemble.h"
#include "../include/suspect.h"

#include "tests.h"

int main(int argc, char **argv)
{
    struct liste_suspects *l = creer_liste_suspects();
    CHECK("Création de la liste de suspects",
            (l != NULL)
            && (l->nb_suspects == 0)
            && (l->queue == NULL)
            && (l->tete == NULL));

    struct suspect *s1 = creer_suspect("A", 0);
    CHECK("Création de suspect (A, 0)",
            (s1 != NULL)
            && (strcmp(s1->nom, "A") == 0)
            && (s1->attributs == 0)
            && (s1->suiv == NULL)
            && (s1->prec == NULL));

    struct suspect *snull = creer_suspect(NULL, 0);
    CHECK("Création de suspect (NULL, 0)", (snull == NULL));

    ajouter_suspect(l, s1);
    CHECK("Ajout d'un suspect à la liste",
            (l != NULL)
            && (l->tete == s1)
            && (l->queue == s1)
            && (l->nb_suspects == 1));

    struct suspect *s2 = creer_suspect("B", 0);
    ajouter_suspect(l, s2);
    CHECK("Ajout d'un 2e suspect à la liste",
            (l != NULL)
            && (l->tete == s1)
            && (l->queue == s2)
            && (l->nb_suspects == 2)
            && (s1->suiv == s2)
            && (s2->prec == s1));

    retirer_suspect(l, s2);
    CHECK("Retrait d'un suspect de la liste (1)",
            (l != NULL)
            && (l->tete == s1)
            && (l->queue == s1)
            && (l->nb_suspects == 1));

    retirer_suspect(l, s1);
    CHECK("Retrait d'un suspect de la liste (2)",
            (l != NULL)
            && (l->nb_suspects == 0)
            && (l->queue == NULL)
            && (l->tete == NULL));

    return EXIT_SUCCESS;
}
