#include <stdlib.h>
#include <stdio.h>

char *cercaRegexp(char *src, char *regexp);

int main() {
	char *src = "xxabcDexw";
	char *regexp = ".\\ac\\A[acde][^ba]"; // abcDex
	
	char *str = cercaRegexp(src, regexp);
	
	if(str==NULL)
		printf("\nNULL");
	else
		printf("\n%s",str);
	
	return 0;
}

char *cercaRegexp(char *src, char *regexp) {
	int i, j, k, l, buono, flag=0;
	char c, r;
	int tmp;
	for(i=0; src[i]!='\0'; i++)
	{
		
		buono = 1;
		for(j=0, k=i; regexp[j]!='\0' && buono; j++, k++)
		{	
			r = regexp[j];
			c = src[k];
			
			if(r=='[')
			{
				flag = 0;
				if(regexp[j+1]=='^')	// allora le lettere trovate dento [] non vanno bene e inverto logica flag
				{ 
					j++;
					flag = !flag;
				}
				
				while(r!=']')
				{
					r = regexp[++j];
					
					if(r==c)
						flag = !flag;
				}
				
				buono = flag;
			}
			else if(r=='\\')
			{
				if(regexp[++j]=='a')	// ho trovato \a
				{
					if(c<'a')	// è maiuscola
						buono = 0;
				}
				else					// ho trovato \A
				{
					if(c>'Z')	// è minuscola
						buono = 0;
				}
			}
			else if(r!='.')
			{
				if(c!=r)
					buono = 0;
			}
		}
		
		if(buono)
			return &(src[i]);
	}

	return NULL;
}




