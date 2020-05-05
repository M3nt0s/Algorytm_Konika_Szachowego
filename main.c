/**
\mainpage Temat projektu: Algorytm Konika Szachowego

<h2><b>Politechnika Swietokrzyska</b></h2>

<h2><b>Wydzial Elektrotechniki, Automatyki i Informatyki </b></h2>

<h3>Kierunek: Informatyka</h3>

<b>Studia: Stacjonarne I stopnia</b>

<b>Grupa: 1ID16A</b>

<b>Tworzyli: Pawel Zacharz, Dominik Latas, Daniel Wojnowski</b>

Opis:
- Algorytm ten polega na tym, aby konik ruszajac z dowolnego miejsca na szachownicy o podanym przez uzytkownika rozmiarze z
regula ruchu skoczka odwiedzil wszystkie pola szachownicy w taki sposob, by konik odwiedzil kazde z
pol dokladnie 1 raz. Odwiedzajac kolejne pola skoczek je numeruje i finalnie powinien wykonac ROZMIAR*ROZMIAR ruchow.

*/

#include <allegro.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/** Przechowuje adres zaladowanego przez uzytkownika obrazka */
BITMAP *kon;
/** Przechowuje adres pola o kolorze czarnym*/
BITMAP *pustyc;
/** Przechowuje adres pola o kolorze bialym*/
BITMAP *pustyb;
/** Odstep planszy od krawedzi X okna*/
int odstx=1;
/** Odstep planszy od krawedzi Y okna*/
int odsty=1;
/** Rozmiar planszy*/
int ROZMIAR;
/** Szerokosc kafelka*/
int c=50;
/** Wspolrzedne startu X*/
int sx;
/** Wspolrzedne startu Y*/
int sy;

/**
W tej funkcji zostala zainicjowana obsluga biblioteki Allegro4.

*Znajduja sie w niej takie funkcje jak:
    *- allegro_init: Ta funkcja jest niezbedna w kazdym programie wykorzystujacym Allegro. Inicjuje cala biblioteke.
    *- set_color_depth(32); - Ustawia glebie koloru
    *- set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0); - Tym poleceniem wlaczamy tryb graficzny. GFX_AUTODETECT oznacza, ze Allegro uzyje automatycznie wykrytego sterownika.GFX_AUTODETECT_WINDOWED - odpali allegro w oknie,
    *- load_bmp( "konik.bmp", default_palette ); - laduje obrazek o podanej przez nas nazwie oraz przypisuje go do wybranej przez nas zmiennej
    *- clear_to_color(); - Ta funkcja zamalowuje strukture BITMAP podanym kolorem
    *- create_bitmap(); - Tworzy bitmape o podanej wielkosci pamieci szerokosci i wysokosci

\image html init.png
*/


void init(){

    allegro_init();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
    kon = load_bmp( "konik.bmp", default_palette );
    pustyc = create_bitmap(c, c);
    clear_to_color(pustyc,makecol(0,0,0));
    pustyb = create_bitmap(c, c);
    clear_to_color(pustyb,makecol(255,255,255));
}

/**
Jest to funkcja ktorej glownym zadaniem jest rysowanie planszy o rozmiarze podanym przez uzytkownika oraz wielkosci

Zawiera funkcje takie jak:
    *- textout_ex(); - Dzieki niej mozemy wyswietlic dowolny tekst na bitmapie
    *- rect(); - Rysuje prostokat na bitmapie
    *- line(); - Rysuje linie na bitmapie
    *- makecol(); - Odpowiada za przypisanie koloru ktory podal uzytkownik do elementu
    *- textprintf_ex(); - Wyswietla tekst

\image html plansza.png
*/

void plansza(int ROZMIAR, int c){

    int i, x = 0, y=0,k,l;
    int d =c*ROZMIAR;

    textout_ex(screen, font, "Algorytm skoczka szachowego", odstx, odsty/3, makecol(255, 255, 255), 0);
    rect( screen, odstx-c, odsty-c, odstx+d+c, odsty+d+c, makecol( 13, 196, 0 ) );

    for(i=0; i<ROZMIAR; i++){

        line( screen, odstx, odsty+x, odstx+d, odsty+x, makecol( 204, 153, 0 ) );
        line( screen, odstx+y, odsty, odstx+y, odsty+d, makecol( 204, 153, 0 ) );

        textprintf_ex( screen, font, odstx+x+c/2, odsty+d+c/2, makecol( 13, 196, 0 ), 0, "%d", i );
        textprintf_ex( screen, font, odstx-c/2, odsty+c/2+y, makecol( 13, 196, 0 ), 0, "%d", i );
        x+=c;
        y+=c;
    }

    line( screen, odstx, odsty+x, odstx+d, odsty+x, makecol( 204, 153, 0 ) );
    line( screen, odstx+y, odsty, odstx+y, odsty+d, makecol( 204, 153, 0 ) );


    for(l=0; l<ROZMIAR; l++){

        k=l%2;

        while(k<ROZMIAR){

            floodfill(screen, odstx+k*c+c/2-2, odsty+l*c+c/2-2, makecol(255,255,255));
            k+=2;
        }
    }
}

/**

Funkcja ta sprawdza na jakim polu aktualnie jest skoczek oraz
odpowiednio dostosowuje obrazek figury skoczka do rozmiaru pola szachownicy
a takze zapisuje nr ruchu na srodku pola planszy.

Uzyto w niej takie funkcje jak:
    *- getpixel(); - Zwraca kolor piksela znajdujacy sie na podanej pozycji z okreslonej bitmapy.
    *- stretch_sprite(); - Kopiuje bitmape zmieniajac jej szerokosc i wysokosc.
    *- _sleep(); - Spowalnia ruch skoczka o podana ilosc czasu

\image html ruch1.png
*/
void ruch1(int ROZMIAR, int i, int j, int a){


    if(getpixel(screen, odstx+i*c+c/2-2,odsty+j*c+c/2-2)== makecol(255,255,255)){

        stretch_sprite( screen, kon, odstx+i*c+2, odsty+j*c+2, 9*c/10, 9*c/10 );
        _sleep(400);
        stretch_sprite( screen, pustyb, odstx+i*c+2, odsty+j*c+2, 9*c/10, 9*c/10 );
        textprintf_ex( screen, font, odstx+i*c+c/2-2, odsty+j*c+c/2-2, makecol(222, 155, 0), - 1, "%d", a );
    }

    else{

        stretch_sprite(screen, kon, odstx+i*c+2, odsty+j*c+2, 9*c/10, 9*c/10 );
        _sleep(400);
        stretch_sprite(screen, pustyc, odstx+i*c+2, odsty+j*c+2, 9*c/10, 9*c/10 );
        textprintf_ex(screen, font, odstx+i*c+c/2-2, odsty+j*c+c/2-2, makecol( 222, 155, 44 ), - 1, "%d", a );
    }
}



/**

Funkcja ospowiada za odpowiednie poruszanie sie
figury skoczka po planszy.
Jak wiadomo konik moze poruszac sie po tak zwanej "L".

Posiada on maksymalnie 8 roznych ruchow co zostalo
odpowiednio uwzglednione w tej funkcji.
\image html ruch.png

 */


int ruch(int tab[][100], int N, int wariant, int x, int y, int *nx, int *ny){

        switch (wariant){

        case 1:
            *nx = x+1;
            *ny = y-2;
            break;
        case 2:
            *nx = x+2;
            *ny = y-1;
            break;
        case 3:
            *nx = x+2;
            *ny = y+1;
            break;
        case 4:
            *nx = x+1;
            *ny = y+2;
            break;
        case 5:
            *nx = x-1;
            *ny = y+2;
            break;
        case 6:
            *nx = x-2;
            *ny = y+1;
            break;
        case 7:
            *nx = x-2;
            *ny = y-1;
            break;
        case 8:
            *nx = x-1;
            *ny = y-2;
            break;
        }

        if (0<=*nx && *nx<N && 0<=*ny && *ny<N && tab[*nx][*ny]==0){
            return 1;
        }

    return 0;
}

/**

Funkcja ta jest odpowiedzialna za odpowiedni wybor ruchu skoczka szachowego.
Korzysta ona z funkcji ruch() z odpowiednim parametrem odpowiadajacym za
jeden z 8 wariantow skoku.

Sprawdza ona czy konik wykonal ostatni ruch. Jezeli nie to
nastepuje rekurencyjne wywolanie funkcji z kolejnymi parametrami.

Jezeli jednek skoczek wykonal swoj ostatni ruch o numerze ROZMIAR*ROZMIAR
to wyswietla ona macierz liczbowa reprezentujaca szachownice
z kolejnymi skokami konika.
\image html droga.png

 */

int droga(int tab[][100], int ROZMIAR, int x, int y, int ktory)
{
        int nx, ny, w;
        int i,j;

        tab[x][y] = ktory;

        if(ktory == ROZMIAR*ROZMIAR)
        {
            for(i=0 ; i<ROZMIAR ; i++)
            {
                for(j=0 ; j<ROZMIAR; j++)
                    printf("%.2d ",tab[i][j]);
                printf("\n");
            }
            return 1;
        }
        else
        {
            for(w=1 ; w<9 ; w++)
                if(ruch(tab, ROZMIAR, w, x, y, &nx, &ny) == 1)
                    if (droga(tab, ROZMIAR, nx, ny, ktory+1) == 1)
                        return 1;
            tab[x][y] = 0;//cofnfniecie
        }

        return 0;
}

/**

Funkcja ta odpowiada za ustawienie na calej szachownicy
wartosci 0 na kazdym jej polu w celu ulatwienia sprawdzania
czy konik byl juz na danym polu czy tez nie.

\image html czysc.png
*/

void czysc(int tab[][100],int ROZMIAR){



        int i,j;
        for(i=0 ; i<ROZMIAR ; i++)
            for(j=0 ; j<ROZMIAR ; j++)
                tab[i][j] = 0;

}

/**
Funkcja ta ospowiada za szukanie prawidlowego ruchu konika
na bazie jego aktualnej pozycji oraz podanego rozmiaru szachownicy.

\image html szukaj.png
*/

void szukaj(int tab[][100],int szukana,int *i, int *j, int ROZMIAR){

        int k, l;
        bool s=1;
        for(k=0; k<ROZMIAR; k++){
            for(l=0; l<ROZMIAR; l++){

                if(tab[k][l]==szukana){

                    *i = k;
                    *j = l;
                    s=0;
                    break;
                }
                if(!s){
                    break;
                }
            }
        }
}

/**

Funkcja odpowiada za wczytywanie danych dotyczacych
punktu startowego skoczka oraz rozmiaru szachownicy
podanych przez uzywkownika.

Posiada ona odpowiednie zabezpieczenia dotyczace rozmiaru
szachownicy a takze wspolrzednych ktore wykraczaly by poza szachownice.

\image html podaj_dane.png

*/

int podaj_dane(){

        do{
            printf("Podaj rozmiar szachownicy:");
            scanf("%d", &ROZMIAR);

        while(ROZMIAR<=0){
            system("cls");
            printf("Rozmiar nie moze byc mniejszy lub rowny 0!!\n\n");
            podaj_dane();
        }
            printf("Podaj punkt startowy: (x,.)");
            scanf("%d",&sx);
            printf("Podaj punkt startowy: (.,y)");
            scanf("%d", &sy);

            if((sx>(ROZMIAR-1) || sy>(ROZMIAR-1)) || (sx<0 || sy<0)){

                system("cls");
                printf("Podaj poprawna pozycje!!\n\n");
                podaj_dane();
            }

    }while((sx>(ROZMIAR-1) || sy>(ROZMIAR-1)) || (sx<0 || sy<0));

    return 0;
}

/**

Informuje ona uzytkownika o tym czy konik znalazl odpowiednie
rozwiazanie czy tez nie i wyswietla odpowiedni komunikat.

Na koniec pyta uzytkownika czy chce podac inne dane bez wzgledu
na to czy skoczek przeszedl cala szachownice czy tez nie.
\image html inicjalizuj.png

 */

int inicjalizuj(){

        int a=1;//numer ruchu na planszy
        int i,j; //pozycja skoczka

        int tab[100][100];
        int podaj_dane();
        int wybor;
        odstx = (800-c*ROZMIAR)/2;
        odsty = (600-c*ROZMIAR)/2;
        czysc(tab, ROZMIAR);
        printf("\nSTART Z POZYCJI (%d, %d)\n",sx,sy);
        printf("Szukam rozwiazania ...\n");
        if(droga(tab, ROZMIAR, sx, sy, 1)==1){

            printf("Znalazlem rozwiazanie\n");
            init();
            int p;

            plansza(ROZMIAR,c);

                for(p=1; p<=ROZMIAR*ROZMIAR; p++){

                    szukaj(tab,p,&i,&j,ROZMIAR);
                    ruch1(ROZMIAR,i,j,a++);

                    if(p == ROZMIAR*ROZMIAR){
                        printf("Udalo sie! Konik szachowy byl na kazdym polu szachownicy tylko raz! \n");
                    }

                    printf("RUCH:\(%d, %d)=%d\n",i,j,p);
                }


        puts("\n==============================================================================================================================\n");
        printf("\t\t\t\t      CZY CHCESZ PODAC INNE DANE? (1-TAK)/(2-NIE)\n");
        puts("\n==============================================================================================================================\n");

        scanf("%d", &wybor);

        while(wybor){
        if(wybor==1){
            system("cls");
            allegro_exit();
            podaj_dane();
            inicjalizuj();
        }
        if(wybor==2){
            system("cls");
            allegro_exit();
            puts("\n==============================================================================================================================\n");
            printf("\t\t\t\t      DZIEKUJEMY ZA SKORZYSTANIE Z PROGRAMU!\n");
            puts("\n==============================================================================================================================\n");
            exit(1);
        }
        }
        }
        else

            printf("Nie znaleziono rozwiazania!\n\n");

            puts("\n==============================================================================================================================\n");
            printf("\t\t\t\t      CZY CHCESZ PODAC INNE DANE? (1-TAK)/(2-NIE)\n");
            puts("\n==============================================================================================================================\n");
            scanf("%d", &wybor);

        while(wybor){
        if(wybor==1){
            system("cls");
            allegro_exit();
            podaj_dane();
            inicjalizuj();
        }
        if(wybor==2){
            system("cls");
            allegro_exit();
            puts("\n==============================================================================================================================\n");
            printf("\t\t\t\t      DZIEKUJEMY ZA SKORZYSTANIE Z PROGRAMU!\n");
            puts("\n==============================================================================================================================\n");
            exit(1);
        }
        }

    return 0;
}



/**

Funkcja w ktorej wywolane sa dwie najwazniejsze funkcje naszego programu
odpowiadajace za realizacje caleo algorytmu skoczka.
\image html main.png
 */


int main(){

    podaj_dane();
    inicjalizuj();
    return 0;
}
END_OF_MAIN()
/* */
