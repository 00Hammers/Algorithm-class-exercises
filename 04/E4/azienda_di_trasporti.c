#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define WORD_LEN_MAX 30
#define CMD_LEN_MAX 12
#define N_COMANDI 7

char parametri[WORD_LEN_MAX];
char *lista_comandi[CMD_LEN_MAX] = {"fine", "stampa", "data", "tratta", "partenza", "arrivo", "cerca"};
enum comando_e {
	r_fine, r_stampa, r_data, r_tratta, r_partenza, r_arrivo, r_cerca
};

typedef struct {
	int giorno;
	int mese;
	int anno;
} t_data;

typedef struct {
	char cod[7];
	char partenza[WORD_LEN_MAX];
	char destinazione[WORD_LEN_MAX];
	char data_str[11];
	t_data data;
	char ora_partenza[WORD_LEN_MAX];
	char ora_destinazione[WORD_LEN_MAX];
	int ritardo;
} t_corsa;

t_corsa *getCorseDaFile(char *path, int *n_corse);
char *getLowercaseStr(char *str);
enum comando_e leggiComando();
int isDateEqual(char *data1, char *data2);
int isDateLess(char *data1, char *data2);
int isStrLess(char *str1, char *str2);
int isTimeLess(char *time1, char *time2);
void ordinaPerArrivo(t_corsa *corse, int n_corse);
void ordinaPerCodice(t_corsa *corse, int n_corse);
void ordinaPerData(t_corsa *corse, int n_corse);
void ordinaPerPartenza(t_corsa *corse, int n_corse);
void ricercaTratta(t_corsa *corse, int n_corse);
void ricercaBinariaTratta(char *key, t_corsa *corse, int l, int r);
void ricercaSequenzialeTratta(char *key, t_corsa *corse, int n_corse);
void setDateParametro(t_data *data1, t_data *data2);
void stampaCorsa(t_corsa corsa);
void stampaCorse(t_corsa *corse, int n_corse);
void stampaCorseSuFile(char *path, t_corsa *corse, int n_corse);
void stampaOSalvaCorse(t_corsa *corse, int n_corse);
void stampaMenu();
void swap(t_corsa *corsa1, t_corsa *corsa2);

enum key_e {
	k_null, k_data, k_tratta, k_partenza, k_arrivo
};

enum key_e chiave_ordinamento = k_null;

int main()
{
	int n_corse;
	t_corsa *corse = getCorseDaFile("corse.txt", &n_corse);
	stampaCorse(corse, n_corse);
	enum comando_e comando = -1;
	while(comando)
	{
		stampaMenu();
		comando = leggiComando();
		gets(parametri);

		switch(comando)
		{
			case r_stampa:
				stampaOSalvaCorse(corse, n_corse);
				break;
			case r_data:
				ordinaPerData(corse, n_corse);
				break;
			case r_tratta:
				ordinaPerCodice(corse, n_corse);
				break;
			case r_partenza:
				ordinaPerPartenza(corse, n_corse);
				break;
			case r_arrivo:
				ordinaPerArrivo(corse, n_corse);
				break;
			case r_cerca:
				ricercaTratta(corse, n_corse);
				break;
			case r_fine:
				break;
			default:
				printf("\nErrore inserimento comando.");
				break;
		}
	}
	
	free(corse);
	
	return 0;
}

t_corsa *getCorseDaFile(char *path, int *n_corse) {
	FILE *fp = fopen(path, "r");
	if(fp == NULL) return NULL;
	
	fscanf(fp, "%d", n_corse);
	t_corsa *corse = malloc(sizeof(t_corsa)*(*n_corse));
	
	int i = -1;
	while(++i<*n_corse)
	{
		fscanf(fp, "\n%s %s %s %s %s %s %d", corse[i].cod, corse[i].partenza, corse[i].destinazione, corse[i].data_str,
											 corse[i].ora_partenza, corse[i].ora_destinazione, &corse[i].ritardo);
		
		sscanf(corse[i].data_str, "%d/%d/%d", &corse[i].data.anno, &corse[i].data.mese, &corse[i].data.giorno);
	}

	return corse;
}

char *getLowercaseStr(char *str) {
	int str_len = strlen(str);
	char *str_dest = malloc(str_len*sizeof(char));

	int i = 0;
	for(i=0; i<str_len; i++)
		str_dest[i] = tolower(str[i]);
	str_dest[i] = '\0';
		
	return str_dest;
}

int isDateEqual(char *data1, char *data2) {
	return strcmp(data1,data2) == 0;
}

int isDateLess(char *data1, char *data2) {
	return strcmp(data1,data2) < 0;
}

int isStrLess(char *str1, char *str2) {
	return strcmp(str1, str2) < 0;
}

int isTimeLess(char *time1, char *time2) {
	return strcmp(time1, time2) < 0;
}

enum comando_e leggiComando() {
	char *cmd_read = malloc(CMD_LEN_MAX*sizeof(char));
	printf("\nInserire comando: ");
	scanf("%s", cmd_read);
	cmd_read = getLowercaseStr(cmd_read);

	enum comando_e c = -1;
	int trovato = 0, i = 0;
	
	while(i<N_COMANDI/* && !trovato*/)
	{
		if(strcmp(cmd_read, lista_comandi[i]) == 0)
		{
			c = i;
//			trovato = 1;
			break;
		}
		
		i++;
	}
	
	free(cmd_read);
	
	return c;
}

void ordinaPerArrivo(t_corsa *corse, int n_corse) {
	int i, j;
	t_corsa tmp;
	for(i=0; i<n_corse; i++)
	{
		for(j=i+1; j<n_corse; j++)
		{
			if(strcmp(corse[i].destinazione, corse[j].destinazione) > 0)
			{
				swap(&corse[i], &corse[j]);
			}
		}
	}
	
	chiave_ordinamento = k_arrivo;
}

void ordinaPerCodice(t_corsa *corse, int n_corse) {
	int i, j, i_min;
	t_corsa tmp;
	for(i=0, i_min=0; i<n_corse; i++)
	{
		for(j=i+1; j<n_corse; j++)
		{
			if(strcmp(corse[i].cod, corse[j].cod) > 0)
			{
				swap(&corse[i], &corse[j]);
			}
		}
	}
	
	chiave_ordinamento = k_tratta;
}

void ordinaPerData(t_corsa *corse, int n_corse) {
	int i, j, i_min;
	t_corsa tmp;
	for(i=0, i_min=0; i<n_corse; i++)
	{
		for(j=i+1; j<n_corse; j++)
		{
			if(!isDateLess(corse[i].data_str, corse[j].data_str))
			{
				if(isDateEqual(corse[i].data_str, corse[j].data_str))
				{
					if(!isTimeLess(corse[i].ora_partenza, corse[j].ora_partenza))
						swap(&corse[i], &corse[j]);
				}
				else
					swap(&corse[i], &corse[j]);
			}
		}
	}
	
	chiave_ordinamento = k_data;
}

void ordinaPerPartenza(t_corsa *corse, int n_corse) {
	int i, j;
	t_corsa tmp;
	for(i=0; i<n_corse; i++)
	{
		for(j=i+1; j<n_corse; j++)
		{
			if(strcmp(corse[i].partenza, corse[j].partenza) > 0)
			{
				swap(&corse[i], &corse[j]);
			}
		}
	}
	
	chiave_ordinamento = k_partenza;
}

void ricercaTratta(t_corsa *corse, int n_corse) {
	char partenza[WORD_LEN_MAX];
	sscanf(parametri, "%s", partenza);
	
	if(chiave_ordinamento == k_tratta)
		ricercaBinariaTratta(partenza, corse, 0, n_corse);
	else
		ricercaSequenzialeTratta(partenza, corse, n_corse);
}

void ricercaBinariaTratta(char *key, t_corsa *corse, int l, int r) {
	printf("\nBinaria");
	int m = (l+r)/2;
	int str_cmp = strcmp(getLowercaseStr(key), getLowercaseStr(corse[m].cod));
	
	if(str_cmp == 0)
		stampaCorsa(corse[m]);
	else
		if(l==r)
		{			
			printf("\nTratta non trovata.");
		}
		else
		{
			if(str_cmp < 0)
				ricercaBinariaTratta(key, corse, l, m);
			else
				ricercaBinariaTratta(key, corse, m+1, r);
		}
}

void ricercaSequenzialeTratta(char *key, t_corsa *corse, int n_corse) {
	printf("\nSequenziale");
	int i, index=-1;
	for(i=0; i<n_corse && index==-1; i++)
		if(strcmp(getLowercaseStr(key), getLowercaseStr(corse[i].cod)) == 0)
			index = i;
	
	if(index == -1)
		printf("\nTratta non trovata");
	else
		stampaCorsa(corse[index]);
}

void setDateParametro(t_data *data1, t_data *data2) {
	sscanf(parametri, "%d/%d/%d %d/%d/%d", data1->anno, data1->mese, data1->giorno,
										   data2->anno, data2->mese, data2->giorno);
}

void stampaCorsa(t_corsa corsa) {
	printf("\n%s %s %s %s %s %s %d", corsa.cod, corsa.partenza, corsa.destinazione, corsa.data_str,
									 corsa.ora_partenza, corsa.ora_destinazione, corsa.ritardo);
}

void stampaCorse(t_corsa *corse, int n_corse) {
	int i = -1;
	while(++i<n_corse)
		stampaCorsa(corse[i]);
	
	printf("\n");
}

void stampaCorseSuFile(char *path, t_corsa *corse, int n_corse) {
	FILE *fp = fopen(path, "w");
	if(fp == NULL) printf("\nErrore file.");

	int i = -1;
	while(++i<n_corse)
		fprintf(fp, "%s %s %s %s %s %s %d\n", corse[i].cod, corse[i].partenza, corse[i].destinazione, corse[i].data_str,
											corse[i].ora_partenza, corse[i].ora_destinazione, corse[i].ritardo);
	fclose(fp);
}

void stampaOSalvaCorse(t_corsa *corse, int n_corse) {
	printf("\nOpzioni:");
	printf("\n  [1] stampa a video.");
	printf("\n  [2] stampa su file.");
	printf("\nScelta: ");
	
	int scelta;
	scanf("%d", &scelta);
	
	if(scelta==1)
		stampaCorse(corse, n_corse);
	else if(scelta==2)
		stampaCorseSuFile("log.txt", corse, n_corse);
	else
		printf("Input non valido.");
}

void stampaMenu() {
	printf("\nMENU");
	printf("\n  [stampa]   stampa contenuti del log");
	printf("\n  [data]     ordinamento del vettore per data, e a parità di date per ora");
	printf("\n  [tratta]   ordinamento del vettore per codice di tratta");
	printf("\n  [partenza] ordinamento del vettore per stazione di partenza");
	printf("\n  [arrivo]   ordinamento del vettore per stazione di arrivo");
	printf("\n  [cerca]    ricerca di una tratta per stazione di partenza");
	printf("\n  [fine]     chiusura programma");
}

void swap(t_corsa *corsa1, t_corsa *corsa2) {
	t_corsa tmp = *corsa1;
	*corsa1 = *corsa2;
	*corsa2 = tmp;
}





