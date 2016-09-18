/* Maciej Michalec */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>

int licznikslow(char znak) /* funkcja zliczajaca slowa w tekscie */
{
static int liczbaslow=0;
static int poprzednik_pusty=1;
if(isspace(znak))
	{
	poprzednik_pusty=1; /* zapamietujemy wystapienie znaku pustego */
	}
else if(isalnum(znak) && poprzednik_pusty)
	{
	liczbaslow++;
	poprzednik_pusty=0;
	}
return liczbaslow;
}


int szukajwyrazu(char znak,char t[]) /* funkcja szukajaca w tekscie danego slowa */
{
static int ilerazy=0;
static int i=0;
if(znak==t[i]) /* jezeli pierwszy znak zgadza sie z t[i], oczekujemy t[i+1] na kolejnej pozycji */
	{
	i++;
	if(t[i]==0)
		{
		ilerazy++;
		i=0;
		}
	}

else i=0;
return ilerazy;
}

int swapletter(char* filename,char lit1,char lit2) /* funkcja zmienia w pliku filename kazdy znak lit1 na lit2 */
{
FILE* plik1, *plik2;
char nazwa[50];
char c;
int i=0;
plik1=fopen(filename,"a+");
sprintf(nazwa,"%s%d","temp",random());
plik2=fopen(nazwa,"a+");
/*printf("Dostalem znaki %c i %c oraz nazwe %s\n",lit1,lit2,filename);*/
while( (c=getc(plik1)) != EOF )
	{
	if(c==lit1)
		{
		fprintf(plik2,"%c",lit2);
		i++;
		}
	else
		{
		fprintf(plik2,"%c",c);
		}
	}
fclose(plik1);
remove(filename);
fseek(plik2,0,0);
plik1=fopen(filename,"a+");
do
	{
	c=getc(plik2);
	if(c==EOF) break;
	fprintf(plik1,"%c",c);;
	}while( !feof(plik2) );
fclose(plik1);
fclose(plik2);
remove(nazwa);
return i;
}

int fileExists(const char* filename) /* funkcja sprawdza czy podane plik istnieje */
{
struct stat buf;
if(stat(filename,&buf)==0) return 1; /* sprawdzamy czy da sie odczytac statystyki pliku */
else return 0;
}

int zamienciag(char* filename, char* slowo1,char* slowo2)
{
int count=0;
FILE* plik1, *plik2;
char nazwa[50];
char zapamietaj[60];
char c;
int i=0;
int poprz=0; /* czy poprzedni znak jest zgodny z szukanym */
plik1=fopen(filename,"a+");
sprintf(nazwa,"%s%d","temp",random());
plik2=fopen(nazwa,"a+");
/*printf("Dostalem slowa %s i %s oraz nazwe %s\n", slowo1,slowo2,filename);*/
while( (c=getc(plik1)) != EOF )
	{
	if(poprz==0&&c!=slowo1[i])
		{
		fprintf(plik2,"%c",c);
		poprz=0;
		for(i=0;i<50;i++)
			{
			zapamietaj[i]=0;
			}
		i=0;
		}
	else if(c==slowo1[i])
		{
		zapamietaj[i]=c;
		i++;
		poprz=1;
		if(slowo1[i]==0)
			{
			fprintf(plik2,"%s",slowo2);
			i=0;
			poprz=0;
			count++;
			}
		}
	else if(poprz==1&&c!=slowo1[i])
		{
		fprintf(plik2,"%s%c",zapamietaj,c);
		poprz=0;
		for(i=0;i<50;i++)
			{
			zapamietaj[i]=0;
			}
		i=0;
		}
	}
fclose(plik1);
remove(filename);
fseek(plik2,0,0);
plik1=fopen(filename,"a+");
do
	{
	c=getc(plik2);
	if(c==EOF) break;
	fprintf(plik1,"%c",c);;
	}while( !feof(plik2) );
fclose(plik1);
fclose(plik2);;
remove(nazwa);
return count;
}
