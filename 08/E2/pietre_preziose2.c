#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N 4
#define MAX_RIP 3

typedef struct s_pietra {
	char nome;
	int val;
	int n;
} t_pietra;

typedef struct s_pietre {
	t_pietra z;
	t_pietra s;
	t_pietra r;
	t_pietra t;
	char str[N+1];
} t_pietre;

int creaCollana(int pos, t_pietre pietre, char *collana, int n, int k, int *val);
int isValid(char *vet, t_pietre p);
int len(char *vet);
int checkNPietre(char *vet, t_pietre p);
int contaPietre(char *vet, char c);
t_pietre getPietre();
void stampaPietre(t_pietre p);
int valoreCollana(char *vet, t_pietre p);
int checkRip(char *vet, int n);

int main() {
	t_pietre pietre = getPietre();
	stampaPietre(pietre);
	
	int k_max = pietre.z.n + pietre.s.n + pietre.r.n + pietre.t.n;
	
	char *collana = (char*)malloc(k_max*sizeof(char));
	
	int k, valid, val_max, val;
	char *collana_max = (char*)malloc(sizeof(collana));
	for(k=1, valid=0, val_max=0; k>0 && k<=k_max; k++)
	{
		val = 0;
		
		if(creaCollana(0, pietre, collana, N, k, &val))
		{
			if(val>val_max)
			{
				strcpy(collana_max, collana);
				val_max = val;
			}
		}
	}
	
	if(val_max)
		printf("\nPossibile collana di valore %d: %s", val_max, collana_max);
	
	free(collana);
	free(collana_max);
	
	return 0;
}

int creaCollana(int pos, t_pietre pietre, char *collana, int n, int k, int *val) {
	int i;
	
	if(pos>=k)
	{
		if(isValid(collana, pietre))
		{
			*val = valoreCollana(collana, pietre);
			return 1;
		}
		
		return 0;
	}
	
	for(i=0; i<n; i++)
	{
		collana[pos] = pietre.str[i];
		collana[pos+1] = '\0';
		
		if(creaCollana(pos+1, pietre, collana, n, k, val)) 
			return 1;
	}
	
	return 0;
}

int isValid(char *vet, t_pietre p) {
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
		
		if(!checkNPietre(vet, p)) // non devono esserci più pietre di quante disponibili
			flag = 0;
		
		if(!checkRip(vet, n))
			flag = 0;
	}
	
	return flag;
}

int checkRip(char *vet, int n) {
	int i, cont;
	
	for(i=1, cont=1; i<n; i++)
	{
		if(vet[i]==vet[i-1])
		{
			cont++;
			if(cont>MAX_RIP)
				return 0;
		}
		else cont=0;
	}
	
	return 1;
}

int len(char *vet) {
	int i;
	for(i=0; vet[i]!='\0'; i++);
	
	return i;
}

int checkNPietre(char *vet, t_pietre p) {
	int n_z = contaPietre(vet, p.z.nome); // trova quanti Z ci sono nella collana
	int n_s = contaPietre(vet, p.s.nome);
	int n_r = contaPietre(vet, p.r.nome);
	int n_t = contaPietre(vet, p.t.nome);

	if((n_z > p.z.n) || (n_s > p.s.n) || (n_r > p.r.n) || (n_t > p.t.n))
		return 0;
	
	if(n_z > n_s) return 0;
	
	return 1;
}

int valoreCollana(char *vet, t_pietre p) {
	int n_z = contaPietre(vet, p.z.nome); // trova quanti Z ci sono nella collana
	int n_s = contaPietre(vet, p.s.nome);
	int n_r = contaPietre(vet, p.r.nome);
	int n_t = contaPietre(vet, p.t.nome);
	
	return n_z*p.z.val + n_s*p.s.val + n_r*p.r.val + n_t*p.t.val;
}

int contaPietre(char *vet, char c) {
	int i, cont;
	int n = len(vet);
	
	for(i=0, cont=0; i<n; i++)
		cont += (vet[i]==c);
	
	return cont;
}

t_pietre getPietre() {
	t_pietre p;
	
	p.z.nome = 'Z';
	p.z.val = 6;
	p.z.n = 4;
	
	p.s.nome = 'R';
	p.s.val = 8;
	p.s.n = 2;
	
	p.r.nome = 'S';
	p.r.val = 6;
	p.r.n = 1;
	
	p.t.nome = 'T';
	p.t.val = 20;
	p.t.n = 5;
	
	strcpy(p.str, "ZSRT");
	
//	stampaPietre(p);

	return p;
}

void stampaPietre(t_pietre p) {
	printf("\nInfo pietre:");
	printf("\nz: %c\tn: %d\tval: %d", p.z.nome, p.z.n, p.z.val);
	printf("\ns: %c\tn: %d\tval: %d", p.s.nome, p.s.n, p.s.val);
	printf("\nr: %c\tn: %d\tval: %d", p.r.nome, p.r.n, p.r.val);
	printf("\nt: %c\tn: %d\tval: %d\n", p.t.nome, p.t.n, p.t.val);
}




