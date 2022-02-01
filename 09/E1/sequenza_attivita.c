#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct {
  int s, f, d;
} att;

void attSel(int n, att *v);
int attRec(int pos, att *v, att *sol, att *best_sol, int *n_best, int *mark, int n, int k);
int isValid(att *v, int n);
void stampaAtt(att *v, int n);
int totD(att *v, int n);

int main(int argc, char **argv) {
	FILE *fp = fopen("att.txt", "r");
	int n;
	fscanf(fp, "%d", &n);
	att v[n];
	
	int i;
	for(i=0; i<n; i++)
	{
		fscanf(fp, "%d %d", &v[i].s, &v[i].f);
		v[i].d = v[i].f - v[i].s;
	}
	
	fclose(fp);
	
	attSel(n, v);
	
  return 0;
}

int totD(att *v, int n) {
	int i, tot;
	for(i=0, tot=0; i<n; i++)
		tot += v[i].d;
	
	return tot;
}

int attRec(int pos, att *v, att *sol, att *best_sol, int *n_best, int *mark, int n, int k) {
	int i;
	if(pos>=k)
	{
		if(isValid(sol, k))
		{
			stampaAtt(sol, k);
			printf(" tot: %d", totD(sol,k));
			
			int tot = totD(sol, k);
			int tot_best = totD(best_sol, *n_best);
			
			if(tot > tot_best)
			{
				for(i=0; i<k; i++)
					best_sol[i] = sol[i];
				
				best_sol = sol;
				*n_best = k;
			}
			
			return 1;
		}
		
		return 0;
	}
	
	int ret;
	for(i=0; i<n; i++)
	{
		if(mark[i])
		{
			sol[pos] = v[i];
			mark[i] = 0;
			ret = attRec(pos+1, v, sol, best_sol, n_best, mark, n, k); 
			mark[i] = 1;
		}
	}

	return ret;
}

void attSel(int n, att *v) {
	att *sol = (att *) malloc(n*sizeof(att));
	att *best_sol = (att *) malloc(n*sizeof(att));
	
	int i, mark[n];
	for(i=0; i<n; i++)
		mark[i] = 1;
	
	int k, *n_best;
	char *importante = "non rimuovere"; // necessaria
	for(k=1, *n_best=0; k<=n; k++)
	{
		printf("\n\nk = %d", k);
		attRec(0, v, sol, best_sol, n_best, mark, n, k);
	}
	
	printf("\n\nAtt di durata complessiva %d", totD(best_sol, *n_best));
	stampaAtt(best_sol, *n_best);
	
	free(sol);
	free(best_sol);
}

int isValid(att *v, int n) {
	int i, s2, f1;
	for(i=1; i<n; i++)
	{
		s2 = v[i].s;
		f1 = v[i-1].f;
		
		if(f1>s2) return 0;
	}
	
	return 1;
}

void stampaAtt(att *v, int n) {
	int i;
	printf("\n");
	for(i=0; i<n; i++)
		printf("(%d, %d)\t", v[i].s, v[i].f);
}
