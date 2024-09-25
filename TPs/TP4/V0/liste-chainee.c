#include "liste-chainee.h"
#include <stdlib.h>
#include <stdio.h>

#define TODO NULL;

// retourne vrai si l est vide et faux sinon
bool estVide(Liste l) {
	return l == NULL;
}

// créer une liste d'un seul élément contenant la valeur v
Liste creer(Element v){
	Liste liste = malloc(sizeof(Cellule));
	liste->val = v;
	liste->suiv = NULL;

	return liste;
}

// ajoute l'élément v en tete de la liste l
Liste ajoutTete(Element v, Liste l) {
	Liste liste = malloc(sizeof(Cellule));
	liste->val = v;
	liste->suiv = l;

	return liste;
}


void afficheElement(Element e) {
	printf("%i ",e);
}

// affiche tous les éléments de la liste l
// Attention, cette fonction doit être indépendante du type des éléments de la liste
// utiliser une fonction annexe affiche_element
// Attention la liste peut être vide !
// version itérative
void afficheListe_i(Liste l) {
	Liste liste = l;
	while(liste != NULL) {
		printf("%d,", liste->val);
		liste = liste->suiv;
	}
	printf("\n");
}

// version recursive
void afficheListe_r(Liste l) {
	if(l == NULL) {
		printf("\n");
		return;
	}
	printf("%d,", l->val);
	afficheListe_r(l->suiv);
}

void detruireElement(Element e) {}

// Détruit tous les éléments de la liste l
// version itérative
void detruire_i(Liste l) {
	Liste liste = l;
	while(liste != NULL) {
		Liste nListe = liste->suiv;
		detruireElement(liste->val);
		free(liste);
		liste = nListe;
	}
}

// version récursive
void detruire_r(Liste l) {
	if (l == NULL) return;
	detruire_r(l->suiv);
	detruireElement(l->val);
	free(l);
}

// retourne la liste dans laquelle l'élément v a été ajouté en fin
// version itérative
Liste ajoutFin_i(Element v, Liste l) {
	Liste queue = l;
	while(queue != NULL) {
		queue = queue->suiv;
	}

	queue->suiv = malloc(sizeof(Cellule));
	queue->suiv->val = v;
	queue->suiv->suiv = NULL;
	return l;
}

// version recursive
Liste ajoutFin_r(Element v, Liste l) {
	if(l == NULL) {
		l = malloc(sizeof(Cellule));
		l->suiv = NULL;
		l->val = v;
	}
	else if (l->suiv == NULL) {
		l->suiv = malloc(sizeof(Cellule));
		l->suiv->val = v;
		l->suiv->suiv = NULL;
	}
	else{
		ajoutFin_r(v, l->suiv);
	}
	return l;
}

// compare deux elements
bool equalsElement(Element e1, Element e2){
	//printf("\ne1=%d\ne2=%d\nres=%d\n\n", e1, e2, e1==e2);
	return e1 == e2;
}

// Retourne un pointeur sur l'élément de la liste l contenant la valeur v ou NULL
// version itérative
Liste cherche_i(Element v,Liste l) {
	Liste liste = l;
	while(liste != NULL) {
		if(equalsElement(v, liste->val))
			return liste;
		liste = liste->suiv;
	}
	return liste;
}

// version récursive
Liste cherche_r(Element v,Liste l) {
	if(l == NULL) return NULL;
	if(equalsElement(l->val, v)) return l;
	return cherche_r(v,l->suiv);
}

// Retourne la liste modifiée dans la laquelle le premier élément ayant la valeur v a été supprimé
// ne fait rien si aucun élément possède cette valeur
// version itérative
Liste retirePremier_i(Element v, Liste l) {
	if (l == NULL) return l;
	if (equalsElement(v, l->val)) {
		Liste tmp = l->suiv;
		free(l);
		return tmp;
	}

	Liste current = l->suiv;
	Liste prev = l;

	while(current != NULL) {
		if(equalsElement(v, current->val)) {

			prev->suiv = current->suiv;
			free(current);

			return l;
		}

		prev = current;
		current = current->suiv;
	}
	return l;
}


// version recursive
Liste retirePremier_r(Element v, Liste l) {
	if(l == NULL) return l;
	if(equalsElement(v, l->val)) {
		Liste res = l->suiv;
		free(l);
		return res;
	}
	l->suiv = retirePremier_r(v, l->suiv);
	return l;
}


void afficheEnvers_r(Liste l) {
	TODO;
}



