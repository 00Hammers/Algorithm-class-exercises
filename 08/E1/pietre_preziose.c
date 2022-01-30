#include <stdlib.h>
#include <stdio.h>

#define N 4

typedef struct s_pietre {
	int z;
	int s;
	int r;
	int t;
} t_pietre;

int creaCollana(int pos, char *pietre, t_pietre n_pietre, char *collana, int n, int k);
int isValid(char *vet, t_pietre n_pietre);
int len(char *vet);
int checkNPietre(char *vet, t_pietre n_pietre);
int contaPietre(char *vet, char c);

int main() {
	char pietre[N+1] = "ZSRT";
	t_pietre n_pietre;
	n_pietre.z = 2;
	n_pietre.s = 1;
	n_pietre.r = 1;
	n_pietre.t = 2;
	
	int k_max = n_pietre.z + n_pietre.s + n_pietre.r + n_pietre.t;
	
	char *collana = (char*)malloc(k_max*sizeof(char));
	
	int k, valid;
	for(k=k_max, valid=0; !valid && k>0 && k<=k_max; k--)
	{
		valid = creaCollana(0, pietre, n_pietre, collana, N, k);
		
		if(valid)
			printf("\nPossibile collana di lunghezza %d: %s", len(collana), collana);
		
	}
	
	free(collana);
	
	return 0;
}

int creaCollana(int pos, char *pietre, t_pietre n_pietre, char *collana, int n, int k) {
	int i;
	
	if(pos>=k)
	{
		if(isValid(collana, n_pietre))
			return 1;
		
		return 0;
	}
	
	for(i=0; i<n; i++)
	{
		collana[pos] = pietre[i];
		collana[pos+1] = '\0';
		
		if(creaCollana(pos+1, pietre, n_pietre, collana, n, k)) 
			return 1;
	}
	
	return 0;
}

int isValid(char *vet, t_pietre n_pietre) {
	int n = len(vet);
	if(n==1) return 1;
	int z,r,s,t;
	
	int i, flag;
	for(i=1, flag=1; i<n && flag; i++)
	{
		z = vet[i]=='Z' && (vet[i-1]=='Z' || vet[i-1]=='T'); // ZZ o TZ
		r = vet[i]=='R' && (vet[i-1]=='Z' || vet[i-1]=='T'); // ZR o TR
		s = vet[i]=='S' && (vet[i-1]=='S' || vet[i-1]=='R'); // SS o RS
		t = vet[i]=='T' && (vet[i-1]=='S' || vet[i-1]=='R'); // ST o RT
		
		if((z+r+s+t)==0) // se son tutte false allora isValid==0
			flag = 0;
		
		if(!checkNPietre(vet, n_pietre)) // non devono esserci più pietre di quante disponibili
			flag = 0;
	}
	
	return flag;
}

int len(char *vet) {
	int i;
	for(i=0; vet[i]!='\0'; i++);
	
	return i;
}

int checkNPietre(char *vet, t_pietre n_pietre) {
	if(contaPietre(vet, 'Z') > n_pietre.z) return 0;
	if(contaPietre(vet, 'R') > n_pietre.r) return 0;
	if(contaPietre(vet, 'S') > n_pietre.s) return 0;
	if(contaPietre(vet, 'T') > n_pietre.t) return 0;

	return 1;
}

int contaPietre(char *vet, char c) {
	int i, cont;
	int n = len(vet);
	
	for(i=0, cont=0; i<n; i++)
		cont += (vet[i]==c);
	
	return cont;
}
