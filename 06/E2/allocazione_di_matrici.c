#include <stdlib.h>
#include <stdio.h>

int **malloc2dR(int **mat, FILE *fp, int nr, int nc);
void malloc2dP(int ***mat, FILE *fp, int nr, int nc);
void stampaMatrice(int **mat, int nr, int nc);
void stampaVet(int *vet, int n);
void separa(int **mat, int nr, int nc, int **w, int *nw, int **b, int *nb);
int isEven(int val);

int main() {
	FILE *fp = fopen("mat.txt","r");
	int nr, nc;
	fscanf(fp, "%d %d", &nr, &nc);

	int **mat;
	mat = malloc2dR(mat, fp, nr, nc);
	fclose(fp);
	stampaMatrice(mat, nr, nc);
	
//	malloc2dP(&mat2, fp, nr, nc);
//	stampaMatrice(mat2, nr, nc);
	int *w, *b, nw, nb;
	separa(mat, nr, nc, &w, &nw, &b, &nb);
	stampaVet(w, nw);
	stampaVet(b, nb);

	free(mat);
	free(w);
	free(b);

	printf("\nmain finito");
	return 0;
}

int **malloc2dR(int **mat, FILE *fp, int nr, int nc) {
	mat = (int **) calloc(nr, sizeof(int *));
	
	int i, j;
	for(i=0; i<nr; i++)
	{
		mat[i] = (int *) calloc(nc, sizeof(int *));
		
		for(j=0; j<nc; j++)
			fscanf(fp, "%d", &mat[i][j]);
	}
	
	return mat;
}

void malloc2dP(int ***mat, FILE *fp, int nr, int nc) {
	*mat = (int **) calloc(nr, sizeof(int *));
	
	int i, j;
	for(i=0; i<nr; i++)
	{
		*(mat)[i] = (int *) calloc(nc, sizeof(int *));
		
		for(j=0; j<nc; j++)
			fscanf(fp, "%d", &(*mat)[i][j]);
	}
}

void separa(int **mat, int nr, int nc, int **w, int *nw, int **b, int *nb) {
	int dim = nr*nc;
	*nb = dim/2;
	*nw = dim - *nb;
	
	*w = (int *) calloc(*nw, sizeof(int));
	*b = (int *) calloc(*nb, sizeof(int));
	
	int i, j, iw, ib, var;
	for(i=0, iw=0, ib=0, var=0; i<nr; i++)
	{
		for(j=0; j<nc; j++, var=!var)
		{
			if(var)
				(*b)[ib++] = mat[i][j];
			else
				(*w)[iw++] = mat[i][j];
		}
		
		if(isEven(nc)) var = !var;
	}
}

void stampaMatrice(int **mat, int nr, int nc) {
	int i, j;
	for(i=0; i<nr; i++)
	{
		for(j=0; j<nc; j++)
			printf("%d ", mat[i][j]);
		
		printf("\n");
	}
}

void stampaVet(int *vet, int n) {
	int i;
	for(i=0; i<n; i++)
		printf("%d ", vet[i]);
}

int isEven(int val) {
	return val%2 == 0;
}



