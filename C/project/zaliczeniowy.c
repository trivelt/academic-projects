/* Maciej Michalec */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "libzal.h"

int main(int argc, char* argv[])
{
int poprzednik_pusty;
int i;
char znak1=0,znak2=0;
char filename[50],filename2[50], szukane_slowo[50];
FILE* plik;
int klawisz=0;
int c, nl,nc,samogloski,spolgloski,nw,duze,male,liczby,ileszuk,puste,interpunkcyjne,zmiany; /* liczba wierszy, znakow, liter itd. */

for(i=0;i<argc;i++)
	{
	if( strcmp(argv[i],"help") == 0 || strcmp(argv[i],"-help") == 0 || strcmp(argv[i],"-h") == 0 || strcmp(argv[i],"--help") == 0)
		{
		printf("\nWitaj w programie zaliczeniowym ver. 0.9\nProgram wczytuje od uzytkownika nazwe pliku");
		printf(" tekstowego i wyswietla dane dotyczace liczby wystepujacych\nw nim wersow, znakow, liter itd.");
		printf(" Obsluguje jedynie zwykle pliki tekstowe *.txt zawierajace standardowe znaki ASCII,\n");
		printf("poprawnosc dla znakow narodowych nie jest gwarantowana. Umozliwia zapisanie statystyk do innego pliku");
		printf("\ntekstowego (ostrzega przed ewentualnymi nadpisaniami), zliczanie w pliku podanych przez uzytkownika znakow\n");
		printf("lub ciagow znakowych oraz zamiane wszystkich znakow (identycznych z podanymi na wejsciu) wystepujacych w tekscie");
		printf("\nProgram rozroznia duze i male litery.\n\n");
		return 1;
		}

	}
podajplik:
nc=nw=samogloski=spolgloski=duze=male=liczby=ileszuk=puste=interpunkcyjne=zmiany=0;
nl=poprzednik_pusty=1;
printf("Podaj nazwe pliku: ");
scanf("%s",filename);
printf("Podales %s \n",filename);
plik=fopen(filename,"r");
if(plik==NULL) 
	{
	perror("Blad otwarcia pliku");
	return 0;
	}


/* Czyta wskazany przez usera plik znak po znaku az do napotkania EOF */
while( (c=getc(plik)) != EOF )
	{
	++nc; /* liczba znakow */
	/* licznik malych i duzych liter, nastepnie wszystkie sa zmniejszane dla ulatwienia dalszych operacji */
	if(isupper(c)) 
		{
		duze++;
		c=(char)tolower(c);
		}
	else if(isalpha(c)) male++;
	if(c=='\n') ++nl; /* licznik wersow */
	if(isdigit(c)) liczby++;
	if(ispunct(c)) interpunkcyjne++;
	/* zlicza samogloski i spolgloski */
	if(c=='a'||c=='e'||c=='i'||c=='o'||c=='u'||c=='y') samogloski++;
	else if(isalpha(c)) spolgloski++;

	if(isspace(c)) 
		{
		puste++;
		poprzednik_pusty=1; /* zapamietujemy wystapienie znaku pustego */
		}
	else if(isalnum(c) && poprzednik_pusty)
		{
		nw++; /* zwiekszamy licznik slow */
		poprzednik_pusty=0;
		}

	}

fclose(plik);

/* Wypisuje uzytkownikowi dane dot. wskazanego pliku tekstowego */
printf("\nPlik %s\nLiczba wierszy: %d\nLiczba slow: %d\nLiczba znakow: %d, w tym:\n",filename,nl,nw,nc);
printf("Znaki puste: %d\nInterpunkcyjne: %d\nCyfry: %d\nLitery %d",puste,interpunkcyjne,liczby,duze+male);
printf("\nDuze: %d\nMale: %d\nSamogloski: %d\nSpolgloski: %d\n",duze,male,samogloski,spolgloski);
while(1)
{
printf("\nCo chcesz teraz zrobic?\n1. Zbadaj inny plik\n2. Zapisz statystyki do pliku\n3. Wyszukaj slowo (znak) w pliku\n");
printf("4. Zamien znak w pliku\nDowolny inny klawisz - opusc program\n");
klawisz=0;
scanf("%d",&klawisz);
switch(klawisz)
{
	case 1:
	{
	goto podajplik;
	}
	break;
	
	case 2:
	{
	printf("\n\nPodaj nazwe pliku do ktorego zapisac dane: ");
	scanf("%s",filename2);
	printf("Podales %s \n",filename2);
	if(fileExists(filename2)) /* zabezpieczenie przed niechcianym nadpisaniem istniejacego pliku */
		{
		printf("\nTaki plik juz istnieje! Czy pomimo tego chcesz zapisac tam dane? Wybierz:\n1. Tak\n");
		printf("dowolny inny klawisz - nie (opusc program)\n");
		scanf("%d",&klawisz);
		switch(klawisz)
			{
			case 1:
			;break;
			default:
			return 1;
			break;
			}
		}

	plik=fopen(filename2,"w");
	fprintf(plik,"Plik %s:\nLiczba wierszy: %d\nLiczba slow: %d\nLiczba znakow: %d, w tym:\n",filename,nl,nw,nc);
	fprintf(plik,"Znaki puste: %d\nInterpunkcyjne: %d\nCyfry: %d\nLitery %d",puste,interpunkcyjne,liczby,duze+male);
	fprintf(plik,"\nDuze: %d\nMale: %d\nSamogloski: %d\nSpolgloski: %d\n",duze,male,samogloski,spolgloski);
	fclose(plik);
	}
	break;

	case 3:
	{
	printf("Wprowadz slowo do wyszukania: ");
	scanf("%s",szukane_slowo);
	printf("Szukasz %s", szukane_slowo);
	plik=fopen(filename,"r");
	while( (c=getc(plik)) != EOF )
		{
		ileszuk=szukajwyrazu(c,szukane_slowo);
		}
	fclose(plik);
	printf("Slowo %s wystapilo w tekscie %d razy.",szukane_slowo, ileszuk);
	}
	break;

	case 4:
	{
	printf("Wpisz znak, ktory chcesz zmienic: ");
	scanf("%c",&znak1);
	znak1=getchar();
	printf("Teraz podaj znak, NA który chcesz zamienic poprzedni: ");
	scanf("%c",&znak2);
	znak2=getchar();
	zmiany=swapletter(filename,znak1,znak2);
	printf("\nPrzeprowadzono zamiane %d znakow\n",zmiany);
	}
	break;

	default:
	return 1;
	break;
} /* koniec switcha */
klawisz=0;
} /* koniec while */
}
