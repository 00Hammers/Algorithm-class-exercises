#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int gcd(int a, int b);
int gcd2(int a, int b);
int isEven(int num);

int main(int argc, char *argv[]) {
	int a,b;
	printf("Inserire dividendo: ");
	scanf("%d", &a);
	printf("Inserire divisore: ");
	scanf("%d", &b);
	
	int MCD = gcd(a,b);
	
	printf("%d",MCD);
		
	return 0;
}

int gcd(int a, int b)
{
	if(a<=b)
	{
		int tmp = a;
		a = b;
		b = tmp;
	}
	
	if(a==b || b==0)
		return a;
	
	if(isEven(a))
		if(isEven(b))
			return 2*gcd(a/2, b/2);
		else
			return gcd(a/2, b);
	else
		if(isEven(b))
			return gcd(a, b/2);
		else
			return gcd((a-b)/2, b);
}

int gcd2(int a, int b)
{
	if(a<=b)
	{
		int tmp = a;
		a = b;
		b = tmp;
	}
	
	if(a==b || b==0)
		return a;
	else
		return gcd2(b, a%b);
}

int isEven(int num)
{
	return num%2==0;
}
