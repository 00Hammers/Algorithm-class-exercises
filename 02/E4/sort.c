#include <stdlib.h>
#include <stdio.h>
/*
? Shell Sort
Si scriva un programma in C che per ogni sequenza numerica acquisita da file (sort.txt) 
invochi tutti gli algoritmi di ordinamento sopra indicati e stampi a video:
	? il numero di scambi
	? il numero di iterazioni del ciclo esterno
	? per ogni passo del ciclo esterno il numero di iterazioni del ciclo interno
	? il numero totale di iterazioni.
*/

void insertionSort(int *vet);
int len(int *vet);
int liberaMemoria(int **sequenze, int n);
void selectionSort(int *vet);
void shellSort(int *vet);
void stampaInfo(int swaps, int cnt_i, int cnt_j);
void stampaSequenze(int **sequenze, int n);
void swap(int *n1, int *n2);

int main() {
	FILE *fp = fopen("sort.txt", "r");
	int i, j, n, m;
	fscanf(fp, "%d", &n);
	int *sequenze[n];
	for(i=0; i<n; i++)
	{
		fscanf(fp, "%d", &m);
		sequenze[i] = (int *) malloc((m+1)*sizeof(int));
		
		for(j=0; j<m; j++)
			fscanf(fp, "%d", &sequenze[i][j]);
		sequenze[i][j] = '\0';
	}
	fclose(fp);
	
	stampaSequenze(sequenze, n);

	for(i=0; i<n; i++)
	{
//		selectionSort(sequenze[i]);
//		insertionSort(sequenze[i]);
		shellSort(sequenze[i]);
	}
	stampaSequenze(sequenze, n);
	
	liberaMemoria(sequenze, n);
	
	return 0;
}

int len(int *vet) {
	int i;
	for(i=0; vet[i]!='\0'; i++);
	
	return i;
}

int liberaMemoria(int **sequenze, int n) {
	int i;
	for(i=0; i<n; i++)
		free(sequenze[i]);
}

void selectionSort(int *vet) {
	int i, j, i_min;
	int swaps=0, cnt_i=0, cnt_j=0;
	int n = len(vet);
	int tmp;
	for(i=0; i<n; i++)
	{
		cnt_i++;
		for(j=i, i_min=i; j<n; j++)
		{
			cnt_j++;
			if(vet[j]<vet[i_min])
				i_min = j;
		}
		
		if(i_min!=i/* && vet[i]!=vet[i_min]*/)
		{
			swap(&vet[i], &vet[i_min]);
			swaps++;
		}
	}
	
	stampaInfo(swaps, cnt_i, cnt_j);
}

void insertionSort(int *vet) {
	int i, j, i_min;
	int swaps=0, cnt_i=0, cnt_j=0;
	int n = len(vet);
	int tmp;
	for(i=0; i<n-1; i++)
	{
		cnt_i++;
		for(j=i+1; j>0 && vet[j]<vet[j-1]; j--)
		{
			cnt_j++;
			swap(&vet[j], &vet[j-1]);
			swaps++;
		}
	}
	
	stampaInfo(swaps, cnt_i, cnt_j);
}

void shellSort(int *vet) {
	int swaps=0, cnt_i=0, cnt_j=0;
	int n = len(vet);
	int i, j, gap;
	for(gap=n/2; gap>=1; gap/=2)
	{
		for(i=0; i<n-gap; i++)
		{
			cnt_i++;
			for(j=i+gap; j>=gap && vet[j]<vet[j-gap]; j--)
			{
				cnt_j++;
				swap(&vet[j], &vet[j-gap]);
				swaps++;
			}
		}
	}
	
	stampaInfo(swaps, cnt_i, cnt_j);
}

void stampaInfo(int swaps, int cnt_i, int cnt_j) {
	printf("\nSwaps: %d\tCnt_i: %d\tCnt_j: %d", swaps, cnt_i, cnt_j);
}

void stampaSequenze(int **sequenze, int n) {
	int i, j;	
	printf("\nSequenze: ");
	for(i=0; i<n; i++)
	{
		printf("\n");
		for(j=0; j<len(sequenze[i]); j++)
			printf("%d ", sequenze[i][j]);
	}
}
	
void swap(int *n1, int *n2) {
	int tmp = *n1;
	*n1 = *n2;
	*n2 = tmp;
}




