#include "LinkedList.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void LLprintElement(Element e);
bool LLelementEquals(Element e1, Element e2);
void LLfreeElement(Element e1);

int main(int argc, char const *argv[])
{
	int a = 1;
	Liste liste = LLnewList(&a); // liste = {1}

	int b = 2;
	liste = LLadd(liste, &b); // liste = {1,2}
	LLprint(liste);

	int c = 7;
	LLset(liste, 1, &c); // liste = {1,7}
	LLprint(liste);

	printf("%d\n", LLsize(liste));

	int d = 1;
	liste = LLremove(liste, &d); // "liste = " is mandatory because 1 is the first element in the list.
	// liste = {7}
	LLprint(liste);

	printf("%d\n", LLcontains(liste, &b)); //false
	printf("%d\n", LLcontains(liste, &c)); //true

	LLdestruct(liste);
	return 0;
}

void LLfreeElement(Element e1) {} // abstract for integer

bool LLelementEquals(Element e1, Element e2) {
	return *((int*) e1) == *((int*) e2);
}

void LLprintElement(Element e) {
	printf("%d ", * ((int*) e));
}