#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define WORD_LEN_MAX 30
#define CMD_LEN_MAX 12
#define N_COMANDI 6

char parametri[WORD_LEN_MAX];
char *lista_comandi[CMD_LEN_MAX] = {"fine", "date", "partenza", "capolinea", "ritardo", "ritardo_tot"};
enum comando_e {
	r_fine, r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot
};

typedef struct {
	char cod[7];
	char partenza[WORD_LEN_MAX];
	char destinazione[WORD_LEN_MAX];
	char data[WORD_LEN_MAX];
	char ora_partenza[WORD_LEN_MAX];
	char ora_destinazione[WORD_LEN_MAX];
	int ritardo;
} t_corsa;

typedef struct {
	int giorno;
	int mese;
	int anno;
} t_data;

t_corsa *getCorseDaFile(char *path, int *n_corse);
char *getLowercaseStr(char *str);
enum comando_e leggiComando();
void ricercaInRitardo(t_corsa *corse, int n_corse);
void ricercaPerCapolinea(t_corsa *corse, int n_corse);
void ricercaPerPartenza(t_corsa *corse, int n_corse);
void ricercaRitardoTotale(t_corsa *corse, int n_corse);
void ricercaTraDate(t_corsa *corse, int n_corse);
void stampaCorsa(t_corsa corsa);
void stampaCorse(t_corsa *corse, int n_corse);
void stampaMenu();

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
			case r_date:
				ricercaTraDate(corse, n_corse);
				break;
			case r_partenza:
				ricercaPerPartenza(corse, n_corse);
				break;
			case r_capolinea:
				ricercaPerCapolinea(corse, n_corse);
				break;
			case r_ritardo:
				ricercaInRitardo(corse, n_corse);
				break;
			case r_ritardo_tot:
				ricercaRitardoTotale(corse, n_corse);
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
		fscanf(fp, "\n%s %s %s %s %s %s %d", corse[i].cod, corse[i].partenza, corse[i].destinazione, corse[i].data,
											 corse[i].ora_partenza, corse[i].ora_destinazione, &corse[i].ritardo);

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

int isDateBetween(char *data, char *data_inizio, char *data_fine) {
	t_data d, d_start, d_end;
	
	sscanf(data, "%d/%d/%d", &d.anno, &d.mese, &d.giorno);
	sscanf(data_inizio, "%d/%d/%d", &d_start.anno, &d_start.mese, &d_start.giorno);
	sscanf(data_fine, "%d/%d/%d", &d_end.anno, &d_end.mese, &d_end.giorno);
	
	int flag = 0;
	
	if(d.anno >= d_start.anno && d.anno <= d_end.anno)
		if(d.mese >= d_start.mese && d.mese <= d_end.mese)
			if(d.giorno >= d_start.giorno && d.giorno <= d_end.giorno)
				flag = 1;
	return flag;
}

enum comando_e leggiComando() {
	char *cmd_read = malloc(CMD_LEN_MAX*sizeof(char));
	printf("\nInserire comando: ");
	scanf("%s", cmd_read);
	cmd_read = getLowercaseStr(cmd_read);
//	printf("\ncmd: %s", cmd_read);

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

void ricercaInRitardo(t_corsa *corse, int n_corse) {
	char data1[11], data2[11];
	sscanf(parametri, "%s %s", data1, data2);
	
	int i, flag=0;
	for(i=0; i<n_corse; i++)
	{
		if(isDateBetween(corse[i].data, data1, data2))
		{
			flag = 1;
			stampaCorsa(corse[i]);
		}
	}
	
	if(!flag) printf("\nTratte non trovate nel periodo richiesto.");
}

void ricercaPerCapolinea(t_corsa *corse, int n_corse) {
	char capolinea[WORD_LEN_MAX];
	sscanf(parametri, "%s", capolinea);
	
	int i;
	for(i=0; i<n_corse; i++)
		if(strcmp(getLowercaseStr(capolinea), getLowercaseStr(corse[i].destinazione)) == 0)
			stampaCorsa(corse[i]);
}

void ricercaPerPartenza(t_corsa *corse, int n_corse) {
	char partenza[WORD_LEN_MAX];
	sscanf(parametri, "%s", partenza);
	
	int i;
	for(i=0; i<n_corse; i++)
		if(strcmp(getLowercaseStr(partenza), getLowercaseStr(corse[i].partenza)) == 0)
			stampaCorsa(corse[i]);
}

void ricercaRitardoTotale(t_corsa *corse, int n_corse) {
	char cod[7];
	sscanf(parametri, "%s", cod);

	int i, sum=0, flag=0;
	for(i=0; i<n_corse; i++)
		if(strcmp(getLowercaseStr(cod), getLowercaseStr(corse[i].cod)) == 0)
		{
			flag = 1;
			sum += corse[i].ritardo;
		}

	if(flag)
		printf("\nRitardo totale per corse tratta %s: %d minuti.", cod, sum);
	else
		printf("\nTratta non trovata.");
}

void ricercaTraDate(t_corsa *corse, int n_corse) {
	char data1[11], data2[11];
	sscanf(parametri, "%s %s", data1, data2);
	
	int i, flag=0;
	for(i=0; i<n_corse; i++)
		if(isDateBetween(corse[i].data, data1, data2))
		{
			flag = 1;
			stampaCorsa(corse[i]);
		}
	
	if(!flag) printf("\nTratte non trovate nel periodo richiesto.");
}

void stampaCorsa(t_corsa corsa) {
	printf("\n%s %s %s %s %s %s %d", corsa.cod, corsa.partenza, corsa.destinazione, corsa.data,
									 corsa.ora_partenza, corsa.ora_destinazione, corsa.ritardo);
}

void stampaCorse(t_corsa *corse, int n_corse) {
	int i = -1;
	while(++i<n_corse)
		stampaCorsa(corse[i]);
	
	printf("\n");
}

void stampaMenu() {
	printf("\nMENU");
	printf("\n  [date]        elenco corse partite in un certo intervallo di date");
	printf("\n  [partenza]    elenco corse partite da una certa fermata");
	printf("\n  [capolinea]   elenco corse che fanno capolinea in una certa fermata");
	printf("\n  [ritardo]     elenco corse che hanno raggiunto la destinazione in ritardo in un intervallo di date");
	printf("\n  [ritardo_tot] ritardo accumulato dalle corse identificate da un certo codice di tratta");
	printf("\n  [fine]        chiusura programma");
}







