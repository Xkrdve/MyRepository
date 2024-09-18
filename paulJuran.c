// Paul Juran

#include <stdlib.h>
#include <stdio.h>

#define ARRAY_LENGTH(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))


int* repeat(int t1[], int t2[], int length);
void printTab(int tab[], int length);
int sumTab(int tab[], int length);


int main() {

	int t1[] = {1,2,4};
	int t2[] = {10,3,8};

	int length = 3;

	printTab(t1, length);
	printTab(t2, length);

	int* res = repeat(t1,t2,length);

	printTab(res, sumTab(t1,length));
	free(res);

}



int* repeat(int t1[], int t2[], int length) {
	int tailleTot = 0;

	// compute size of res
	tailleTot = sumTab( t1, length);

	// allocate
	int* res = malloc(tailleTot * sizeof(int));
	int current = 0;

	// copy and duplicate values
	for(int i = 0; i<length; i++) {
		for(int k = 0; k < t1[i]; k++) {
			res[current] = t2[i];
			current++;
		}
	}

	return res;
}



void printTab(int tab[], int length) {
	printf("{ ");
	for (int i = 0; i < length; i++) {
		printf("%d ", tab[i]);
	}
	printf("}\n");
}

int sumTab(int tab[], int length) {
	int res = 0;
	for(int i = 0; i < length; i++) {
		res += tab[i];
	}
	return res;
}