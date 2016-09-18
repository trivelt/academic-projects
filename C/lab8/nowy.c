/* Maciej Michalec */

#include <stdio.h>
#include <string.h>

#define MAX_TEXT 31

struct student {
char imie[MAX_TEXT];
char nazwisko[MAX_TEXT];
float oceny[30];
int liczba_ocen; /* trzeba jeszcze wyzerowac!!*/
};

typedef struct student student;

int porownywacz(const void* jeden, const void* drugi) /* porownywanie nazwisk i imion */
{
int tmp=strcmp((*(student*)jeden).nazwisko,(*(student*)drugi).nazwisko);
if (tmp) return tmp;
return strcmp((*(student*)jeden).imie,(*(student*)drugi).imie);
}

int normalize_name(char* tekst)
{
int i;
if(tekst[0]>='a'&&tekst[0]<='z')
	{
	tekst[0]=tekst[0]-32;
	}
for(i=1;i<=MAX_TEXT;i++)
	{
	if(tekst[i]>=65&&tekst[i]<=90) 
		{
		tekst[i]=tekst[i]+'a'-'A';
		}
	}
}

int main(int argc, char *argv[])
{
char tab[2000];
char test[MAX_TEXT];
FILE* plik;
student studenci[30], s;
int i, liczba_studentow=0, flaga=0; /* wyrzucic poza main?*/
float suma=0;

if(argc>1)
	{
	plik=fopen(argv[1], "r");
	}
else 
	{
	printf("Blad!\n");
	return 1;
	}

liczba_studentow=0;
while(!feof(plik)) /* dopoki nie napotkam EOF */
	{
	fscanf(plik,"%s %s %f",s.imie, s.nazwisko, &s.oceny[0]); /* wczytuje z pliku dane o studentach*/
	normalize_name(s.imie);
	normalize_name(s.nazwisko);
	printf("otrzymalem imie %s, nazwisko %s i ocene %f\n",s.imie,s.nazwisko,s.oceny[0]);
	for(i=0;i<liczba_studentow;i++); /* sprawdzam czy student juz istnieje */
		{
		printf("%d student ma imie %s i nazwisko %s\n",i,studenci[i].imie,studenci[i].nazwisko);
		if((strcmp(s.imie, studenci[i].imie)==0 && strcmp(s.nazwisko,studenci[i].nazwisko)==0)) /*porownuje stringi*/
			{
			/* jezeli student o takim imieniu i nazwisku juz istnieje, dodaje tylko ocene */
			studenci[i].oceny[studenci[i].liczba_ocen]=s.oceny[0];
			studenci[i].liczba_ocen++;
			flaga=0; /* ustawiam na zero by nie dopisywac studenta jako nowego */
			break;
			}
		else
			{
			flaga=1;
			}
		} /* end of for */
	if(flaga) /* jezeli takiego studenta jeszcze nie ma, kopiuje jego dane do tablicy studenci */
		{
		printf("\n\nKopiuje...\n\n");
		strcpy(studenci[liczba_studentow].imie, s.imie);
		strcpy(studenci[liczba_studentow].nazwisko, s.nazwisko);
		studenci[liczba_studentow].oceny[0]=s.oceny[0];
		studenci[liczba_studentow].liczba_ocen++;
		liczba_studentow++; /* trzeba go jeszcze wczesniej wyzerowac! */
		flaga=0; 
		}
	printf("Skopiowalem %s do %s\n",s.imie,studenci[liczba_studentow-1].imie);
	printf("\nliczba studentow to %d \n",liczba_studentow);
    	} /* end of while */

fclose(plik);
qsort(studenci, liczba_studentow, sizeof(s),porownywacz); /* sortowanie listy studentow */

/*program musi przyjmowac imie i nazwisko pisane zarowno malymi jak i duzymi literami,
w pliku ma byc zachowana forma poprawna (pierwsza lit. wielka) - postac kanoniczna*/
return 0;
}

