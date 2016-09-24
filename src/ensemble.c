#include "../include/ensemble.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


ensemble_t ensemble_vide(void){
    return 0;
}

ensemble_t ensemble_plein(void){
    uint16_t x;
    return (1<<(sizeof(x)*8))-1; // Complicated the function a bit to make it scalable.
}

uint16_t ensemble_cardinal(ensemble_t e){
    /* For educational purpose: variable precision SWAR algorithm
     * e=e-((e>>1)&0x5555);
     * e=(e&0x3333)+((x>>2)&0x3333);
     * e=((e+(e>>4))&0x0F0F)*0x0101;
     * return e>>8;
     * // Too lazy to make SWAR scalable, we will use something slower
    */
    uint32_t count=0; // We need uint32_t for scalability
    while(e>0){
        if((e&1)==1)
            count+=1;
        e=e>>1;
    }
    return count;
}

bool ensemble_appartient(ensemble_t e, uint16_t numero_elt){
    return ((e>>numero_elt)&1)==1;
}

ensemble_t ensemble_union(ensemble_t e1, ensemble_t e2){
    return e1|e2;
}

ensemble_t ensemble_intersection(ensemble_t e1, ensemble_t e2){
    return e1&e2;
}

ensemble_t ensemble_complementaire(ensemble_t e){
    // We can do: return (uint16_t)~x; But for scalibility we need something else.
    return e^((1<<(sizeof(e)*8))-1);
}

void ensemble_ajouter_elt(ensemble_t *e, uint16_t numero_elt){
    *e=*e|(1<<numero_elt);
}

void ensemble_retirer_elt(ensemble_t *e, uint16_t numero_elt){
    *e=*e&~(1<<numero_elt);
}

void ensemble_afficher(const char *msg, ensemble_t e){
    printf("%s ",msg);
    while(e){
        if(e&1)
            putchar('1');
        else
            putchar('0');
        e=e>>1;
    }
    putchar('\n');
}
