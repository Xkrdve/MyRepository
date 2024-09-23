/**
 Compilation
 gcc --std=c99 -W -Wall -o prixTuring prixTuring.c

 Exécution
 ./prixTuring

 Tests
 diff out.csv turingWinners.csv

**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <stdbool.h>

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MAIN
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

typedef struct
{
	int annee;
	char* nom; // \0
	char* nature; // \0
} dataPrixTuring;



bool checkFile(FILE* file);
int convertToIntFromCharTab(char* tab);
int numberOfWinners(FILE* file);
void readWinners(FILE* file, dataPrixTuring* data);
void printData(dataPrixTuring data[], int size);
void getAnnee(char* line);
char* getNom(char* line);
char* getNature(char* line);
int tailleStr(char* str);
void freeData(dataPrixTuring* data, int size);
void writeWinners(FILE* file, dataPrixTuring* data, int size);
void printInfo(dataPrixTuring* data, int size, int annee);
int compareFunction (const void* ptr1, const void* ptr2);
void sortTuringWinnersByYear(dataPrixTuring* dataIn, int size);


/**
 * 
 * 
 * */

int main(int argc, char** argv)
{
	bool info = false;
	bool sort = false;
	int anneeInfo = 0;

	char* filename = "turingWinners.csv\0";
	char* outputFilename = "out.csv\0";

	//gestion des arguments
	for (int k = 1; k < argc; k++) {
		if(!strcmp(argv[k], "-o") && k+1 < argc) {
			k++;
			outputFilename = argv[k];
		}
		else if(!strcmp(argv[k], "--info") && k+1 < argc) {
			k++;
			info = true;
			anneeInfo = convertToIntFromCharTab(argv[k]);
		}
		else if(!strcmp(argv[k], "--sort")) {
			sort = true;
		}
		else {
			filename = argv[k];
		}
	}

	// Lire le 1er csv
	FILE* file;
	file = fopen(filename, "r");

	// verification que le fichier existe et autres erreurs
	if (!checkFile(file)) 
		return EXIT_FAILURE;

	// lecture ligne par ligne pour trouver le nombre de lignes du fichier
	int nombreDeLignes = numberOfWinners(file);

	// stockage des données en mémoire vive
	dataPrixTuring data[nombreDeLignes];
	readWinners(file, data);


	if(info) printInfo(data, nombreDeLignes, anneeInfo);

	// on affiche dans la console
	// printData(data, nombreDeLignes);

    fclose(file);

    if(sort) {
    	sortTuringWinnersByYear(data, nombreDeLignes);
    }

    file = fopen(outputFilename, "w");
	if (!checkFile(file)) 
		return EXIT_FAILURE;

	writeWinners(file, data, nombreDeLignes);

	fclose(file);


    freeData(data, nombreDeLignes);

	return EXIT_SUCCESS;
}

// verifie si le fichier existe
bool checkFile(FILE* file) {
	if (file == NULL) {
		printf("code erreur %d\n", errno);

		if (errno == ENOENT) 
			printf("Le fichier n'existe pas\n");
		else
			printf("Erreur inconnue\n");

		return false;
	}
	return true;
}

// caste un char* en int
int convertToIntFromCharTab(char* tab) {
	char c = tab[0];
	int res = 0;
	for(int i = 0; c != '\0'; i++) {
		res *= 10;
		res += c - '0';
		c = tab[i+1];
	}
	return res;
}

// renvoie le nombre de lignes du fichier csv
int numberOfWinners(FILE* file) {
	rewind(file);
	char line[1024];
	int tailleFichier = 0;
	while(fgets(line, 1024, file)) {
		tailleFichier++;
		//printf("%s\n", line);
	}
	return tailleFichier;
}

// copie les informations du fichier csv en mémoire pour utilisation
void readWinners(FILE* file, dataPrixTuring* data) {
	rewind(file);
	int currentDataPrixTuring = 0;
	char line[1024];

	while(fgets(line, 1024, file)) {

		// on récupère les infos de la ligne
		/**
		 * Le principe est de parcourir la ligne et de remplacer chaque ';' et '\n' par un '\0' pour transformer
		 * un char* et trois char*
		 * ensuite, on copie ces char* dans un espace mémoire correctement alloué avant la sortie du range
		 * */

		//getNature et getNom renvoient les addresses du début de l'information respective dans le char* line initial.
		char* nature = getNature(line);
		char* nom = getNom(line);

		//pour l'année, on a pas besoin de renvoyer l'addresse de début car c'est la première info dans la ligne
		getAnnee(line);
		char* anneeStr = line;
		// cast en entier
		int annee = convertToIntFromCharTab(anneeStr);

		data[currentDataPrixTuring].annee = annee;
		data[currentDataPrixTuring].nom = malloc(sizeof(char) * (tailleStr(nom)+1));
		strcpy(data[currentDataPrixTuring].nom, nom);
		data[currentDataPrixTuring].nature = malloc(sizeof(char) * (tailleStr(nature)+1));
		strcpy(data[currentDataPrixTuring].nature, nature);

		currentDataPrixTuring++;
	}

}

// transforme le premier ';' en '\0'
void getAnnee(char* line) {
	char c = line[0];
	int k = 0;
	while(c != ';') {
		if(c == '\0') return;
		k++;
		c = line[k];
	}
	line[k] = '\0';
}

// renvoie la taille d'une chaine de caractères
int tailleStr(char* str) {
	int taille = 0;
	char c = str[taille];
	while(c != '\0') {
		c = str[++taille];
	}
	return taille;
}

// libère la mémoire allouée dans readWinners
void freeData(dataPrixTuring* data, int size) {
	for(int i = 0; i<size; i++) {
		dataPrixTuring d = data[i];
		free(d.nom);
		free(d.nature);
	}
}

// ecris dans un fichier sortie
void writeWinners(FILE* file, dataPrixTuring* data, int size) {
	for(int i = 0; i < size; i++) {
		char str[1024];
		sprintf(str, "%d;%s;%s\n", data[i].annee, data[i].nom, data[i].nature);
		fputs(str, file);
	}
}

void sortTuringWinnersByYear(dataPrixTuring* dataIn, int size) {
	qsort(dataIn, size, sizeof(dataPrixTuring), compareFunction);
}

int compareFunction (const void* ptr1, const void* ptr2) {
	return ((dataPrixTuring*) ptr1)->annee - ((dataPrixTuring*) ptr2)->annee;
}

// renvoie l'addresse dans le char* line du début du nom et remplace le deuxième ';' par '\0'
char* getNom(char* line) {
	char c = line[0];
	int k = 0;
	int n = 0;
	char* t = line;
	while(c != ';' || n == 0) {
		if(c == '\0') return NULL;
		if(c == ';') {
			n++;
			t = line+k+1;
		}
		k++;
		c = line[k];
	}
	line[k] = '\0';
	return t;
}

void printInfo(dataPrixTuring* data, int size, int annee) {
	for(int i = 0; i < size; i++) {
		dataPrixTuring d = data[i];
		if(d.annee != annee) continue;
		printf("année: %d\n", d.annee);
		printf("nom: %s\n", d.nom);
		printf("nature: %s\n\n", d.nature);
	}
}

// renvoie l'addresse du début de la nature et remplace '\n' par '\0'
char* getNature(char* line) {
	char c = line[0];
	int k = 0;
	char* t = line;
	while(c != '\n') {
		if(c == '\0') return NULL;
		k++;
		if(c == ';') 
			t = line+k;
		c = line[k];
	}
	line[k] = '\0';
	return t;
}

// affiche les données
void printData(dataPrixTuring data[], int size) {
	for(int i = 0; i < size; i++) {
		dataPrixTuring d = data[i];
		printf("année: %d\n", d.annee);
		printf("nom: %s\n", d.nom);
		printf("nature: %s\n\n", d.nature);
	}
}