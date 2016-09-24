#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../include/ensemble.h"
#include "tests.h"

int main(int argc, char **argv)
{
    ensemble_t vide = ensemble_vide();
    CHECK("ensemble vide", vide == 0);

    ensemble_t plein = ensemble_plein();
    CHECK("ensemble plein", plein == 0b1111111111111111);

    ensemble_t pairs = 0b0101010101010101;
    ensemble_t impairs = ensemble_complementaire(pairs);
    CHECK("complementaire", impairs == 0b1010101010101010);

    impairs = 0b1010101010101010;
    ensemble_t intersec = ensemble_intersection(pairs, impairs);
    CHECK("intersection", intersec == vide);

    ensemble_t uni = ensemble_union(pairs, impairs);
    CHECK("union", uni == plein);

    ensemble_t singleton = 0b0000000000010000;
    CHECK("appartient (1)", ensemble_appartient(singleton, 4));
    CHECK("appartient (2)", !ensemble_appartient(singleton, 5));

    ensemble_ajouter_elt(&singleton, 0);
    CHECK("ajouter element", singleton == 0b0000000000010001);

    ensemble_retirer_elt(&singleton, 4);
    CHECK("retirer element", singleton == 0b0000000000000001);

    ensemble_t poids_forts = 0b1111111100000000;
    ensemble_t poids_faibles = 0b0000000011111111;
    CHECK("cardinal (1)", ensemble_cardinal(poids_forts) == 8);
    CHECK("cardinal (2)", ensemble_cardinal(poids_faibles) == 8);
    CHECK("cardinal (3)", ensemble_cardinal(vide) + ensemble_cardinal(plein) == 16);

    return EXIT_SUCCESS;
}
