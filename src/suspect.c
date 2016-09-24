#include "../include/suspect.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct suspect *creer_suspect(const char *name, ensemble_t attributs){
    if(name==NULL)
        return NULL;
    struct suspect* tsuspect = malloc(sizeof(struct suspect));
    tsuspect->nom=malloc(strlen(name)+1);
    strcpy(tsuspect->nom,name);
    tsuspect->attributs=attributs;
    return tsuspect;
}

struct liste_suspects *creer_liste_suspects(void){
    struct liste_suspects* list = malloc(sizeof(struct liste_suspects));
    list->nb_suspects=0;
    return list;
}

void detruire_liste_suspects(struct liste_suspects **pl){
    if((*pl)==NULL)
        ;
    else {
        struct suspect* tmp=(*pl)->tete;
        while(tmp!=NULL){
            (*pl)->tete=(*pl)->tete->suiv;
            free(tmp->nom);
            free(tmp);
            tmp=(*pl)->tete;
        }
        free(*pl);
    }
}

void ajouter_suspect(struct liste_suspects *liste, struct suspect *suspect){
    if(liste->nb_suspects==0){
        liste->tete=suspect;
        liste->tete->suiv=NULL;
        liste->tete->prec=NULL;
        liste->queue=liste->tete;
    }
    else {
        suspect->suiv=NULL;
        suspect->prec=liste->queue;
        liste->queue->suiv=suspect;
        liste->queue=suspect;
    }
    liste->nb_suspects+=1;
}

void retirer_suspect(struct liste_suspects *liste, struct suspect *suspect){
    struct suspect* tmp=NULL;
    if(liste->nb_suspects==1){
        free(liste->tete->nom);
        free(liste->tete);
        liste->tete=NULL;
        liste->queue=NULL;
    }
    else if(liste->tete==suspect){
        liste->tete->suiv->prec=NULL;
        tmp=liste->tete->suiv;
        free(liste->tete->nom);
        free(liste->tete);
        liste->tete=tmp;
    }
    else if(liste->queue==suspect){
        liste->queue->prec->suiv=NULL;
        tmp=liste->queue->prec;
        free(liste->queue->nom);
        free(liste->queue);
        liste->queue=tmp;
    }
    else {
        tmp=liste->tete;
        while(tmp!=suspect){
            tmp=tmp->suiv;
        }
        tmp->prec->suiv=tmp->suiv;
        tmp->suiv->prec=tmp->prec;
        free(tmp->nom);
        free(tmp);
    }
    liste->nb_suspects-=1;
}

void affiche_liste_suspects(struct liste_suspects *l){
    struct suspect* tmp=l->tete;
    while(tmp!=NULL){
        printf("%s\n",tmp->nom);
        tmp=tmp->suiv;
    }
    putchar('\n');
}
