#include <stdio.h>
#include <stdlib.h>

#define MAX_SQUADRE 20
#define MAX_GIORNATE 20

void trovaPoiStampaSquadreCapitaliste(int mat[MAX_SQUADRE][MAX_GIORNATE], int n_squadre, int n_giornate);
void stampaMatrice(int mat[MAX_SQUADRE][MAX_GIORNATE], int n, int m);

int main()
{
    int n; //squadre
    int m; //giornate
    
    int mat[MAX_SQUADRE][MAX_GIORNATE];

    FILE *fp = fopen("mat.txt", "r");
    fscanf(fp, "%d %d", &n, &m);
    
    int i, j;
    for(i=0; i<n; i++)
        for(j=0; j<m; j++)
            fscanf(fp, "%d", &mat[i][j]);

    stampaMatrice(mat, n, m);

    trovaPoiStampaSquadreCapitaliste(mat, n, m);

    return 0;
}

void trovaPoiStampaSquadreCapitaliste(int mat[MAX_SQUADRE][MAX_GIORNATE], int n_squadre, int n_giornate)
{
    int i, j;
    int max;
    int capitalisti[n_giornate];

    for(j=0; j<n_giornate; j++)
        capitalisti[j] = 0;

    for(j=0; j<n_giornate; j++)
    {
        max = -1;
        for(i=0; i<n_squadre; i++)
            if(mat[i][j]>max)
            {
                max = mat[i][j];
                capitalisti[j] = i;
            }
    }

    for(j=0; j<n_giornate; j++)
        printf("\nLa capitalista della giornata %d e': %d", j, capitalisti[j]);
}

void stampaMatrice(int mat[MAX_SQUADRE][MAX_GIORNATE], int n, int m)
{
    int i, j;

    printf("Giornate di campionato:\n");
    for(i=0; i<n; i++)
    {
        printf("Squadra %d\t", i);
        
        for(j=0; j<m; j++)
            printf("%d ", mat[i][j]);
            
        printf("\n");
	}
}
