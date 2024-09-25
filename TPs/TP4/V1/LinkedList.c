#include "LinkedList.h"

extern void LLprintElement(Element e);
extern bool LLelementEquals(Element e1, Element e2);
extern void LLfreeElement(Element e1);

Liste LLnewList(Element e) {
	Liste liste = malloc(sizeof(Cellule));
	liste->suiv = NULL;
	liste->val = e;
	return liste;
}

bool LLestVide(Liste liste) {
	return liste == NULL;
}

Liste LLaddFirst(Liste liste, Element e) {
	Liste l = LLnewList(e);
	l->suiv = liste;
	return l;
}

Liste LLadd(Liste liste, Element e) {
	if(LLestVide(liste)) return LLaddFirst(liste, e);
	Liste tmp = liste;
	Liste prev = NULL;
	while(liste != NULL) {
		prev = liste;
		liste = liste->suiv;
	}
	prev->suiv = LLnewList(e);
	return tmp;
}

int LLsize(Liste liste) {
	int k = 0;
	while(liste!=NULL) {
		liste=liste->suiv;
		k++;
	}
	return k;
}

Element LLget(Liste liste, int j) {
	int k = 0;
	while(liste!=NULL) {
		if(k == j) return liste->val;
		liste=liste->suiv;
		k++;
	}
	return NULL;
}

Liste LLset(Liste liste, int j, Element e){
	if(j==0) return LLaddFirst(liste, e);
	Liste tmp = liste;
	int k = 0;
	while(liste != NULL) {
		if(k == j) {
			liste->val = e;
		}
		liste = liste->suiv;
		k++;
	}

	return tmp;
}

Liste LLremove(Liste liste, Element e) {
	if (liste == NULL) return liste;
	if (LLelementEquals(liste->val, e)) {
		Liste tmp = liste->suiv;

		LLfreeElement(liste->val);
		free(liste);

		return tmp;
	}
	liste->suiv = LLremove(liste->suiv, e);
	return liste;
}

Liste LLremoveAll(Liste liste, Element e) {
	if (liste == NULL) return liste;
	Liste tmp;
	if (LLelementEquals(liste->val, e)) {
		tmp = liste->suiv;

		LLfreeElement(liste->val);
		free(liste);
		liste = NULL; //mandatory
	}

	tmp = LLremove(tmp, e);
	return liste;
}

void LLdestruct(Liste liste) {
	if(liste == NULL) return;
	LLdestruct(liste->suiv);
	LLfreeElement(liste->val);
	free(liste);
}

bool LLcontains(Liste liste, Element e) {
	while(liste != NULL) {
		if(LLelementEquals(liste->val, e)) return true;
		liste = liste->suiv;
	}
	return false;
}

void LLprint(Liste liste) {
	while(liste != NULL) {
		LLprintElement(liste->val);
		liste = liste->suiv;
	}
	printf("\n");
}