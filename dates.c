#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 5

/**
 * ECHANGE CONTENU
 * */
void echangeContenu(int*, int*);


/**
 * MATRICES
 * */

void matrix_mult(int64_t matriceResultat[][SIZE], int64_t matriceA[][SIZE], int64_t matriceB[][SIZE]) {
    for(uint m = 0; m < SIZE; m++) {
        for(uint n = 0; n < SIZE; n++) {
            matriceResultat[m][n] = 0;
            for (uint k = 0; k < SIZE; k++) {
                matriceResultat[m][n] += matriceA[m][k] * matriceB[k][n];
            }
        }
    }
}

void matrix_print(int64_t mat[][SIZE]) {
    for(uint m = 0; m < SIZE; m++) {
        for(uint n = 0; n < SIZE; n++) {
            printf("%ld ", mat[m][n]);
        }
        printf("\n");
    }

}

/**
 * MANIP DE DATES
 * */
typedef enum {
    JANVIER = 1,
    FEVRIER,
    MARS,
    AVRIL,
    MAI,
    JUIN,
    JUILLET,
    AOUT,
    SEPTEMBRE,
    OCTOBRE,
    NOVEMBRE,
    DECEMBRE
} Mois;

typedef struct
{
    short jour;
    Mois mois;
    short annee;
} Date;

void afficheDate(Date* date) {
    printf("%d/%d/%d\n", date->jour, date->mois, date->annee);
}

void initialiseDate(Date* date) {
    printf("Veuillez donnez un jour: ");
    scanf("%hd", &date->jour);
    short mois = 1;
    printf("Veuillez donnez un mois: ");
    scanf("%hd", &mois);
    date->mois = (Mois) mois;
    printf("Veuillez donnez une année: ");
    scanf("%hd", &date->annee);
}

Date creerDateParCopie() {
    Date date;
    printf("Veuillez donnez un jour: ");
    scanf("%hd", &date.jour);
    short mois = 1;
    printf("Veuillez donnez un mois: ");
    scanf("%hd", &mois);
    date.mois = (Mois) mois;
    printf("Veuillez donnez une année: ");
    scanf("%hd", &date.annee);
    return date;
}

Date* newDate() {
    Date* date = (Date*) malloc(sizeof(Date));
    initialiseDate(date);
    return date;
}

uint nbreJours(Mois mois, short annee) {
    switch (mois) {

    default:
        return 30;

    case JANVIER:
    case MARS:
    case MAI:
    case JUILLET:
    case AOUT:
    case OCTOBRE:
    case DECEMBRE:
        return 31;

    case FEVRIER:
        return 28 + (annee%4 != 0 || (annee % 100 == 0 && annee % 400 != 0) ? 0 : 1);

    }
}

bool dateValide(Date uneDate) {
    return uneDate.jour >= 1 && uneDate.jour <= nbreJours(uneDate.mois, uneDate.annee);
}

uint jourDansAnnee(Date date) {
    return nbreJours(JANVIER, date.annee) + nbreJours(FEVRIER, date.annee) + nbreJours(MARS, date.annee) + nbreJours(AVRIL, date.annee) + nbreJours(MAI, date.annee) + nbreJours(JUIN, date.annee) + nbreJours(JUILLET, date.annee) + nbreJours(AOUT, date.annee) + nbreJours(SEPTEMBRE, date.annee) + nbreJours(OCTOBRE, date.annee) + nbreJours(NOVEMBRE, date.annee) + nbreJours(DECEMBRE, date.annee);
}

int main(void) {
    /*
    int a = 10;
    int b = 20;
    printf("a=%d et b=%d\n", a, b);
    echangeContenu(&a, &b);
    printf("a=%d et b=%d\n", a, b);

    int64_t matriceA[][SIZE] = {{1,2,3,4,5},{1,2,3,4,5},{1,2,3,4,5},{1,2,3,4,5},{1,2,3,4,5}};
    int64_t matriceB[][SIZE] = {{6,7,8,9,10},{6,7,8,9,10},{6,7,8,9,10},{6,7,8,9,10},{6,7,8,9,10}};
    int64_t matriceResultat[SIZE][SIZE];

    matrix_print(matriceA);
    matrix_print(matriceB);

    matrix_mult(matriceResultat, matriceA, matriceB);
    matrix_print(matriceResultat);
    */

    Date* date = newDate();

    //initialiseDate(&date);
    afficheDate(date);
    printf("%d\n", jourDansAnnee(*date));

    free(date);
}

void echangeContenu(int* a, int* b) {
    int c = *a;
    *a = *b;
    *b = c;
}
