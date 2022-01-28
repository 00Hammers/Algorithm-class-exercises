#include <stdio.h>
#include <stdlib.h>
#define LEN_VET 10

int majority(int *vet, int N);
int majorityR(int *vet, int N, int l, int r);
int conta(int *vet, int N, int val);

int main(int argc, char *argv[]) {
	int vet[LEN_VET] = {1,0,1,1,0,1,9,4,1,1};
	
	printf("\nElemento maggioritario: %d", majority(vet, LEN_VET));
	
	return 0;
}

int majority(int *vet, int N) {
	int l = 0;
	int r = N-1;
	
	return majorityR(vet, N, l, r);
}

int majorityR(int *vet, int N, int l, int r) {
	if(l==r) return vet[l];
		
	int m = (l+r)/2;
	
	int sx = majorityR(vet, N, l, m);
	int dx = majorityR(vet, N, m+1, r);

	printf("sx=%d\tdx=%d\n",sx,dx);	
	
	if(sx==dx) return sx;
	
	int sx_cnt = conta(vet, N, sx);
	int dx_cnt = conta(vet, N, dx);
	
	if(sx_cnt>N/2) return sx;
	if(dx_cnt>N/2) return dx;
	
	return -1;
}

int conta(int *vet, int n, int val) {
	int i, cnt;
	for(i=0; i<n; i++)
		if(vet[i]==val)
			cnt++;
	
	return cnt;
}
