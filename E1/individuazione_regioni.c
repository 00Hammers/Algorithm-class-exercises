#include <stdlib.h>
#include <stdio.h>

#define MAX 50

typedef struct {
	int i;
	int j;
} t_pos;

typedef struct {
	t_pos pos;
	int altezza;
	int larghezza;
	int area;
} t_reg;

void stampaMatrice(int mat[MAX][MAX], int nr, int nc);
int getRegione(t_reg *r, int mat[MAX][MAX], int i, int j, int nr, int nc);
void stampaRegione(t_reg r);
void stampaRegioni(t_reg r_al, t_reg r_la, t_reg r_ar);

int main() {
	FILE *fp = fopen("mappa.txt","r");

	int nr, nc;
	fscanf(fp, "%d %d", &nr, &nc);

	int mat[MAX][MAX];
	int i, j;
	for(i=0; i<nr; i++)
		for(j=0; j<nc; j++)
			fscanf(fp, "%d", &mat[i][j]);

	fclose(fp);	
	
	stampaMatrice(mat, nr, nc);
	
	t_reg r_tmp;
	t_reg r_alte; r_alte.altezza = 0;
	t_reg r_larg; r_larg.larghezza = 0;
	t_reg r_area; r_area.area = 0;
	
	for(i=0; i<nr; i++)
		for(j=0; j<nc; j++)
			if(mat[i][j]==1)
				if(getRegione(&r_tmp, mat, i, j, nr, nc))
				{
					if(r_tmp.altezza > r_alte.altezza)
						r_alte = r_tmp;
					
					if(r_tmp.larghezza > r_larg.larghezza)
						r_larg = r_tmp;
					
					if(r_tmp.area > r_area.area)
						r_area = r_tmp;
				}
	
	stampaRegioni(r_alte, r_larg, r_area);
	
	return 0;
}

void stampaMatrice(int mat[MAX][MAX], int nr, int nc) {
	int i, j;
	printf("\n    ");
	for(j=0; j<nc; j++)	printf("%d ", j);
	printf("\n    ");
	for(j=0; j<nc; j++)	printf("__");
	
	for(i=0; i<nr; i++)
	{
		printf("\n%d  |", i);
		for(j=0; j<nc; j++)
			printf("%d ", mat[i][j]);
	}
}

int getRegione(t_reg *r, int mat[MAX][MAX], int i, int j, int nr, int nc) {
	if(i) if(mat[i-1][j] == 1) return 0;
	if(j) if(mat[i][j-1] == 1) return 0;
	
	r->pos.i = i;
	r->pos.j = j;
	r->altezza = 1;
	r->larghezza = 1;
	
	int k;
	for(k=i+1; k<nr && mat[k][j]==1; k++)
		r->altezza++;

	for(k=j+1; k<nc && mat[i][k]==1; k++)
		r->larghezza++ ;
		
	r->area = (r->altezza)*(r->larghezza);
	
	return 1;
}

void stampaRegioni(t_reg r_al, t_reg r_la, t_reg r_ar) {
	printf("\n\nREGIONE PIU ALTA");
	stampaRegione(r_al);
	
	printf("\nREGIONE PIU LARGA");
	stampaRegione(r_la);
	
	printf("\nREGIONE PIU AMPIA");
	stampaRegione(r_ar);
}

void stampaRegione(t_reg r) {
	printf("\nRegione [%d][%d]:", r.pos.i, r.pos.j);
	printf("\nAltezza:   %d", r.altezza);
	printf("\nLarghezza: %d", r.larghezza);
	printf("\nArea:      %d\n", r.area);
}
