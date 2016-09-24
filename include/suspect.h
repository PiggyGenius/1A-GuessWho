#ifndef SUSPECT_H
#define SUSPECT_H

#include "ensemble.h"

#define HOMME 0
#define FEMME 1

#define MOUSTACHE 2

#define BARBE 3

#define COIFFURE_CHAUVE 4
#define COIFFURE_LONG 5
#define COIFFURE_COURT 6

#define CHEUVEUX_NOIRS 7
#define CHEUVEUX_CHATINS 8
#define CHEUVEUX_BLANCS 9
#define CHEUVEUX_ROUX 10
#define CHEVEUX_BLONDS 11

#define LUNETTES 12

#define CHAPEAU 13

/* Suspect du jeu Qui est-ce. */
struct suspect {
    char *nom;
    ensemble_t attributs;
    struct suspect *suiv;
    struct suspect *prec;
};

/* Liste doublement chainée de suspects. */
struct liste_suspects {
    uint16_t nb_suspects;
    struct suspect *tete;
    struct suspect *queue;
};

/* Retourne un nouveau suspect initialisé en fonction des paramètres
 * nom et attributs. */
extern struct suspect *creer_suspect(const char *nom, ensemble_t attributs);

/* Créé une nouvelle liste de suspects, initialement vide. */
extern struct liste_suspects *creer_liste_suspects(void);

/* Détruit la liste de suspects passée en paramètre. */
extern void detruire_liste_suspects(struct liste_suspects **pl);

/* Ajoute le suspect s en fin de la liste de suspects l. */
extern void ajouter_suspect(struct liste_suspects *l, struct suspect *s);

/* Retire le suspect s de la liste de suspects l. */
extern void retirer_suspect(struct liste_suspects *l, struct suspect *s);

/* Affiche les noms de tous les suspects de la liste l. */
extern void affiche_liste_suspects(struct liste_suspects *l);

#endif /* SUSPECT_H */
