#include <stdlib.h>
#include <stdio.h>

#define DIM_BRANI_MAX 255

typedef struct {
	char **brani;
	int num_brani;
} Livello;

void freeMemory(Livello *val, int n_val);
int trovaSoluzioni(int pos, Livello *val, char **sol, int n, int count);

int main() {
	int n_amici, n_brani, i, j;
	
	FILE *fp = fopen("brani.txt", "r");
	fscanf(fp, "%d", &n_amici);
	Livello val[n_amici];
	
	for(i=0; i<n_amici; i++)
	{
		fscanf(fp, "%d", &n_brani);
		val[i].num_brani = n_brani;
		val[i].brani = (char **) malloc(n_brani*sizeof(char *));
		
		for(j=0; j<n_brani; j++)
		{
			val[i].brani[j] = (char *) malloc(DIM_BRANI_MAX*sizeof(char));
			fscanf(fp, "%s", val[i].brani[j]);
		}
	}
	
	fclose(fp);
	
	char **sol = (char **) malloc(n_amici*sizeof(char *));
	int res = trovaSoluzioni(0, val, sol, n_amici, 0);
	printf("\nNumero playlist possibili: %d",res);
	
	freeMemory(val, n_amici);
	
	return 0;
}

void freeMemory(Livello *val, int n_val) {
	int i, j;
	
	for(i=0; i<n_val; i++)
	{		
		for(j=0; j<val[i].num_brani; j++)
			free(val[i].brani[j]);

		free(val[i].brani);
	}
}

int trovaSoluzioni(int pos, Livello *val, char **sol, int n, int count) {
	int i;
	
	if(pos >= n)
	{
		for(i=0; i<n; i++)
			printf("%s\n", sol[i]);
		printf("\n");
		
		return count+1;
	}
	
	for(i=0; i<val[pos].num_brani; i++)
	{
		sol[pos] = val[pos].brani[i];
		count = trovaSoluzioni(pos+1, val, sol, n, count);
	}
	
	return count;
}
