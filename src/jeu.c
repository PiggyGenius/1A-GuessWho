#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/jeu.h"
#include "../include/suspect.h"
#include "../include/ensemble.h"

#define SUSPECTS 24
#define CATEGORIES 7

typedef struct {
    char* question;
    uint8_t bit;
} question;

void welcome(void){
    char answer;
    printf("Hello tresspasser, welcome to the last game you will ever play MOUAHAHAHAHAHA.\n");
    printf("In front of you lies the game of evil, of lost souls, THE DIABOLICAL GUESS WHO !!!.\n\n");
    printf("Would you like to pick it up ? (y/n): ");
    answer=getchar();getchar();
    // Making my life complicated just to show buffer problems, try to remove second getchar() :)
    while(answer!='y' && answer!='n'){
        printf("Can you do simple tasks ? You have to answer by (y/n):");
        answer=getchar();getchar(); // Probably ugly but still interesting :);
    }
    if(answer=='y')
        printf("\nNot showing fear proves stupidity, not courage ! LET US BEGIN THE GAME OF EVIL.\n\n");
    else
        printf("\nIs the pathetic baby going to cry ? THE LOSER'S SOUL WILL BE LOST FOREVER, THE GAME IS ON.\n\n");
}

void init(struct liste_suspects* list){
    struct suspect* suspect[SUSPECTS];
    char* names[SUSPECTS]={"Andre","Phillipe","Jean-louis","Francois","Robert","Carole","Melanie","Fabien","Patricia","Baptiste","Sebastien","Olivier","Nicolas","Luc","Simon","Maxime","Cedric","Pierre","Martin","Elodie","Victor","Goerges","Thierry","Celine"};
    // nth Bit set to 1 means suspect possesses attribute number n
    // Example: value of andre = 2^0+2^4+2^9+2^12=4625.
    ensemble_t attributs[SUSPECTS]={4625,5185,4673,8769,201,12609,2082,293,546,285,2113,1093,273,2121,8513,197,4241,321,577,8482,1041,10305,2117,194};

    for(uint8_t i=0;i<24;i++){
        suspect[i]=creer_suspect(names[i],attributs[i]);
        ajouter_suspect(list,suspect[i]);
    }
}

void delsuspects(ensemble_t suspect,struct liste_suspects* list){
    if(list->nb_suspects==0)
        return;
    struct suspect* tmp=list->tete;
    ensemble_t target;
    ensemble_t s;
    while(tmp!=NULL){
        target=tmp->attributs;
        s=suspect;
        for(uint8_t i=0;i<sizeof(ensemble_t)*8;i++){
            if((target&1)==0 && (s&1)==1){
                retirer_suspect(list,tmp);
                break;
            }
            target=target>>1;
            s=s>>1;
        }
        tmp=tmp->suiv;
    }
}

void setsuspect(ensemble_t* quest,ensemble_t* suspect,uint8_t random,char answer){
    if(answer=='y'){
        if(random==1){
            for(uint8_t i=0;i<4;i++)
                ensemble_ajouter_elt(quest,i);
        }
        else if(random==0){
            ensemble_ajouter_elt(quest,0);
        }
        else if(random>3 && random<7){
            for(uint8_t i=3;i<7;i++)
                ensemble_ajouter_elt(quest,i);
        }
        else if(random>6 && random<12){
            for(uint8_t i=6;i<12;i++)
                ensemble_ajouter_elt(quest,i);
        }
        ensemble_ajouter_elt(suspect,random);
    }
    else {
        if(random==0){
            ensemble_ajouter_elt(quest,1);
            ensemble_ajouter_elt(suspect,1);
        }
        else if(random==1){
            ensemble_ajouter_elt(quest,0);
            ensemble_ajouter_elt(suspect,0);
        }
        else if(random<7 && random>3){
            if(ensemble_appartient(*quest,4) && ensemble_appartient(*quest,5)){
                ensemble_ajouter_elt(quest,6);
                ensemble_ajouter_elt(suspect,6);
            }
            if(ensemble_appartient(*quest,5) && ensemble_appartient(*quest,6)){
                ensemble_ajouter_elt(quest,4);
                ensemble_ajouter_elt(suspect,4);
            }
            if(ensemble_appartient(*quest,4) && ensemble_appartient(*quest,6)){
                ensemble_ajouter_elt(quest,5);
                ensemble_ajouter_elt(suspect,5);
            }
        }
        else if(random<12 && random>6){
            if(ensemble_appartient(*quest,7) && ensemble_appartient(*quest,8) && ensemble_appartient(*quest,9) && ensemble_appartient(*quest,10)){
                ensemble_ajouter_elt(quest,11);
                ensemble_ajouter_elt(suspect,11);
            }
            if(ensemble_appartient(*quest,8) && ensemble_appartient(*quest,9) && ensemble_appartient(*quest,10) && ensemble_appartient(*quest,11)){
                ensemble_ajouter_elt(quest,7);
                ensemble_ajouter_elt(suspect,7);
            }
            if(ensemble_appartient(*quest,7) && ensemble_appartient(*quest,9) && ensemble_appartient(*quest,10) && ensemble_appartient(*quest,11)){
                ensemble_ajouter_elt(quest,8);
                ensemble_ajouter_elt(suspect,8);
            }
            if(ensemble_appartient(*quest,7) && ensemble_appartient(*quest,8) && ensemble_appartient(*quest,10) && ensemble_appartient(*quest,11)){
                ensemble_ajouter_elt(quest,9);
                ensemble_ajouter_elt(suspect,9);
            }
            if(ensemble_appartient(*quest,7) && ensemble_appartient(*quest,8) && ensemble_appartient(*quest,9) && ensemble_appartient(*quest,11)){
                ensemble_ajouter_elt(quest,10);
                ensemble_ajouter_elt(suspect,10);
            }
        }
    }
}

void askquestions(struct liste_suspects* list){
    uint8_t random;
    char answer;
    char* questions[]={"Is the suspect a man ?","Is the suspect a woman ?","Does the suspect have a mustache ?","Does the suspect have a beard ?","Is the suspect bold ?","Does the suspect have long hair ?","Does the suspect have short hair ?","Is the color of the suspect's hair black ?","Is the color of the suspect's hair chestnut ?","Is the color of the suspect's hair white ?","Is the color of the suspect a ginger ?","Is the color of the suspect's hair blonde ?","Does the suspect wear glasses ?","Does the suspect wear a hat ?"};
    ensemble_t quest=0,suspect=0;
    uint8_t length=sizeof(questions)/sizeof(char*);
    ensemble_t max=ensemble_complementaire(0);
    for(uint8_t i=length;i<sizeof(ensemble_t)*8;i++)
        ensemble_retirer_elt(&max,i);
    srand((unsigned int) time(NULL));

    while(list->nb_suspects>1 && quest!=max){
        do {
            random=rand()%length;
        } while(ensemble_appartient(quest,random));
        printf("%s: ",questions[random]);
        ensemble_ajouter_elt(&quest,random);

        answer=getchar();getchar();
        while(answer!='y' && answer!='n'){
            printf("You have to answer by (y/n):");
            answer=getchar();getchar();
        }
        setsuspect(&quest,&suspect,random,answer);
        delsuspects(suspect,list);
    }
}

int main(void){
    struct liste_suspects* list=creer_liste_suspects();
    welcome();
    init(list);
    printf("Here are all the suspects:\n\n\n");
    affiche_liste_suspects(list);
    askquestions(list);
    if(list->nb_suspects==1)
        printf("\n\nThe name of the suspect is: %s\n",list->tete->nom);
    else
        printf("\n\nYou cheated ! No suspect has these criterias.\n");
    detruire_liste_suspects(&list);
    return EXIT_SUCCESS;
}
