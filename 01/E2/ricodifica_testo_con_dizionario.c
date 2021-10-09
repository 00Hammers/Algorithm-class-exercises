// Un file (sorgente.txt) contiene un testo composto da un numero indefinito di righe, di lunghezza 
// massima 200 caratteri ognuna. Un secondo file (dizionario.txt) contiene un elenco di coppie 
// di stringhe. Il file dizionario.txt è organizzato come segue:
//  sulla prima riga è presente un numero intero e positivo S (≤ 30), che indica il numero di possibili 
// ricodifiche (sostituzioni) presenti nel dizionario
//  seguono S coppie <ricodifica><originale> a rappresentare le sostituzioni possibili.
// Ogni sostituzione <compresso> è nella forma $<intero>$
// Lo scopo del programma è di ricodificare il primo file di testo andando a sostituire sequenze di 
// caratteri sulla base dei contenuti del secondo file. In caso di più sostituzioni possibili per una certa 
// sottostringa, il programma scelga la prima sostituzione trovata. Il risultato della ricodifica sia salvato 
// su un terzo file (ricodificato.txt)

#include <stdio.h>
#include <stdlib.h>

#define LEN_MAX_ROW 200
#define LEN_MAX_WORD 32
#define LEN_MAX_DIZ 30

typedef struct
{
    char parola[LEN_MAX_WORD];
    char token[LEN_MAX_WORD];
} entry;

int caricaDizionario(entry diz[], char file_name[]);

int main()
{
  //  FILE *fp = fopen("dizionario.txt", "r");
    entry diz[LEN_MAX_DIZ];

    int len_diz = caricaDizionario(diz, "dizionario.txt");

    int i;
    for(i=0; i<len_diz; i++)
    {
        printf("<%s><%s>",diz[i].token, diz[i].parola);
    }


    return 0;
}

int caricaDizionario(entry diz[], char file_name[])
{
    FILE *fp = fopen(file_name, "r");
    int i, n;

    fscanf(fp, "%d", &n);

    for(i=0; i<n; i++)
        fscanf(fp, "%s %s", &diz[i].token, &diz[i].parola);

    return n;
}