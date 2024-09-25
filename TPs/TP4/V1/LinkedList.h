#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef void* Element;
struct cellule_s {
	Element val;
	struct cellule_s* suiv;
};
typedef struct cellule_s Cellule;
typedef Cellule* Liste;

// create a new linked list with one element
Liste LLnewList(Element e);

// checks if the list contains any element
bool LLisEmpty(Liste liste);

// adds an element at the end of the list
Liste LLadd(Liste liste, Element e); 

// adds an element at the beginning of the list
Liste LLaddFirst(Liste liste, Element e); 

// return the list size
int LLsize(Liste liste); 

// set the element at index k to the given element
Liste LLset(Liste liste, int k, Element e); 

// return the element at index k
Element LLget(Liste liste, int k); 

// removes the first occurence of 'e' in the list
Liste LLremove(Liste liste, Element e); 

// removes all occurences of e in the list
Liste LLremoveAll(Liste liste, Element e); 

// frees the allocated memory
void LLdestruct(Liste liste); 

// checks if the list contains a certain element
bool LLcontains(Liste liste, Element e); 

// prints the list
void LLprint(Liste liste); 