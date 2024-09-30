#include "arbre-bin-recherche.h"
#include <stdlib.h>
#include <stdbool.h>

// retourne TRUE si a est l'arbre vide et FALSE sinon
bool estVide(ArbreBinaire a) {
	return a == NULL;
}

// initialise l'arbre a à l'arbre vide
void initialiser(ArbreBinaire* a) {
	*a = NULL;
}

// créer un arbre contenant un seul noeud ayant la valeur e
ArbreBinaire creer(Element e) {
	ArbreBinaire a = malloc(sizeof(Noeud));
	a->val = e;
	initialiser(&(a->filsGauche));
	initialiser(&(a->filsDroit));
	return a;
}

// insere e dans a sachant que a est un arbre binaire de recherche
// si a contient déjà un element e, ce dernier n'est pas insérer afin d'éviter les doublons
// version itérative
ArbreBinaire insere_i(ArbreBinaire a, Element e) {
	ArbreBinaire tmp = a;
	if(estVide(a)) return creer(e);
	
	while(!estVide(tmp)) {
		if(tmp->val == e) return a;

		if(tmp->val >= e && estVide(tmp->filsGauche)) {
			tmp->filsGauche = creer(e);
			return a;
		}
		if(tmp->val < e && estVide(tmp->filsDroit)) {
			tmp->filsDroit = creer(e);
			return a;
		}
		if(tmp->val >= e) {
			tmp = tmp->filsGauche;
		}
		else if(tmp->val < e) {
			tmp = tmp->filsDroit;
		}
	}
	return a;
}	

// insere e dans a sachant que a est un arbre binaire de recherche
// si a contient déjà un element e, ce dernier n'est pas insérer afin d'éviter les doublons
// version récursive
ArbreBinaire insere_r(ArbreBinaire a, Element e) {
	if(estVide(a)) return creer(e);
	if(e == a->val) return a;

	if(e < a->val) 
		a->filsGauche = insere_r(a->filsGauche, e);
	if(e > a->val) 
		a->filsDroit = insere_r(a->filsDroit, e);

	return a;
}

// retourne le nombre de noeud contenus dans l'arbre a
int nombreDeNoeud(ArbreBinaire a) {
	return estVide(a) ? 0 : 1 + nombreDeNoeud(a->filsGauche) + nombreDeNoeud(a->filsDroit);
}


// retourne la profondeur du noeud ayant la valeur e dans a
// retourne -1 si a est vide ou si e n'est pas dans a
int profondeur(ArbreBinaire a, Element e){
	if(estVide(a)) return -1;
	if(a->val == e) return 0;
	int pgauche = profondeur(a->filsGauche, e);
	int pdroite = profondeur(a->filsDroit, e);

	if(pgauche == -1 && pdroite == -1) return -1;

	return pgauche > pdroite ? pgauche + 1 : pdroite + 1;
}

// retourne la hauteur de l'arbre a
int hauteur(ArbreBinaire a){
	return 0;
}

// retourne le pere de elem dans l'arbre a ou NULL s'il n'existe pas
ArbreBinaire pere(ArbreBinaire a, Element elem){

	return NULL;
}


void afficheRGD_r(ArbreBinaire a){
}

void afficheGRD_r(ArbreBinaire a){
	if(estVide(a)) return;

	printf("(");
	afficheGRD_r(a->filsGauche);
	printf(" %d ", a->val);
	afficheGRD_r(a->filsDroit);
	printf(")");
}

void afficheGDR_r(ArbreBinaire a){
}

// retourne le noeud dont la valeur est minimum dans l'arbre
// Suppose que a est un arbre binaire de recherche sans doublons
ArbreBinaire min(ArbreBinaire a){
	return NULL;
}

// retourne le noeud dont la valeur est maximum dans l'arbre
// Suppose que a est un arbre binaire de recherche sans doublons
ArbreBinaire max(ArbreBinaire a){
	return NULL;
}


// retourne l'arbre dont la valeur de la racine est elem et NULL si elem n'existe dans a 
// version récursive
ArbreBinaire recherche_r(ArbreBinaire a, Element elem){

	return NULL;
}


// suppime x de a
ArbreBinaire supprimer_r(ArbreBinaire a,Element x)
{

	return NULL;
}

void detruire_r(ArbreBinaire a){
	if(estVide(a)) return;
	detruire_r(a->filsGauche);
	detruire_r(a->filsDroit);
	free(a);
}

