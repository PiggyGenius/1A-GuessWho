#ifndef ENSEMBLE_H
#define ENSEMBLE_H

#include <stdint.h>
#include <stdbool.h>

typedef uint16_t ensemble_t;

/* Retourne un nouvel ensemble initialement vide. */
extern ensemble_t ensemble_vide(void);

/* Retourne un nouvel ensemble initialement plein. */
extern ensemble_t ensemble_plein(void);

/* Retourne le cardinal de l'ensemble b */
extern uint16_t ensemble_cardinal(ensemble_t b);

/* Retourne vrai si l'élément de numéro numero_elt appartient à
 * l'ensemble b, faux sinon */
extern bool ensemble_appartient(ensemble_t b, uint16_t numero_elt);

/* Retourne un nouvel ensemble correspondant à l'union des ensembles
 * e1 et e2. */
extern ensemble_t ensemble_union(ensemble_t e1, ensemble_t e2);

/* Retourne un nouvel ensemble correspondant à l'intersection des
 * ensembles e1 et e2. */
extern ensemble_t ensemble_intersection(ensemble_t e1, ensemble_t e2);

/* Retourne un nouvel ensemble correspondant au complémentaire de
 * l'ensemble e. */
extern ensemble_t ensemble_complementaire(ensemble_t e);

/* Ajoute l'élément de numéro numero_elt à l'ensemble e. */
extern void ensemble_ajouter_elt(ensemble_t *e, uint16_t numero_elt);

/* Retire l'élément de numéro numero_elt de l'ensemble e.*/
extern void ensemble_retirer_elt(ensemble_t *e, uint16_t numero_elt);

/* Affiche l'ensemble e précédé du message msg, sous la forme: "suite
   de 0 et de 1 (val décimale)".

   Exemple :

   ensemble_afficher("Pouet pouet :", 0b00001101);

   affiche :

   Pouet pouet : 00001101 (13)
*/
extern void ensemble_afficher(const char *msg, ensemble_t e);

#endif /* ENSEMBLE_H */
