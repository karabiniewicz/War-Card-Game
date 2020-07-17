#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include<Windows.h>
#include"funkcje.h"

//#define TEST
#define DEMONSTRACJA
#define MADRA_WOJNA
#define GRAFIKA_TEKSTOWA
#define NIESKONCZONA_ROZGRYWKA 10000
#define MAX_KART 52
#define MAX_LINIA 12

using namespace std;

void WypiszWartosc(karta_t karta)
{
	if (karta.wartosc.numer <= 10)
		cout << karta.wartosc.numer;
	else if (karta.wartosc.znak == J)
		cout << "J";
	else if (karta.wartosc.znak == Q)
		cout << "Q";
	else if (karta.wartosc.znak == K)
		cout << "K";
	else if (karta.wartosc.znak == A)
		cout << "A";
}

void WypiszKolor(karta_t karta)
{
	if (karta.kolor == pik)
		cout << (char)6;	//znak ascii pika
	else if (karta.kolor == kier)
		cout << (char)3;
	else if (karta.kolor == trefl)
		cout << (char)5;
	else if (karta.kolor == karo)
		cout << (char)4;
}

void WypiszKarte(karta_t karta)
{
	WypiszWartosc(karta);
	WypiszKolor(karta);
	cout << "|";
}

void gotoxy(int x, int y)
{
	COORD kursor = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), kursor);
}

void Plansza_Karta(int x, int y, kolejka_t Karty, WypisKarty_t ile)
{
	if (ile == dwie)
		gotoxy(x, y + 1);
	else
		gotoxy(x, y + 2);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 128);
	for (int j = 0; j < 11; j++)
	{
		cout << " ";
	}

	if (ile == dwie)
		gotoxy(x - 1, y + 2);
	else
		gotoxy(x - 1, y + 3);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
	for (int j = 0; j < 13; j++)
	{
		cout << " ";
	}
	if (ile == dwie)
	{
		gotoxy(x - 1, y + 3);
		for (int j = 0; j < 13; j++)
		{
			if (j == 2)
			{
				WypiszWartosc(Karty.karta[1]);
			}
			else if (j == 10)
			{
				WypiszKolor(Karty.karta[1]);
			}
			else
				cout << " ";
		}
	}

	//	Glowny wypis	
	for (int i = 0; i < 10; i++)
	{
		gotoxy(x - 2, y + 4 + i);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
		for (int j = 0; j < 15; j++)
		{
			if (i == 1 && j == 2 || i == 8 && j == 12)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
				WypiszWartosc(Karty.karta[0]);
			}
			else if (i == 8 && j == 2 || i == 1 && j == 12)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 244);
				WypiszKolor(Karty.karta[0]);
			}
			else
				cout << " ";
		}
	}
}

void StworzTalie(karta_t karta[], int ktora_talia) // ktora_talia wybiera rozmiar tali 
{
	int i = ktora_talia + 1;	//jeżeli talia 1 -> od '2', talia 2 -> od '3' ...

	int numer_karty = 0;

	//przypisanie
	for (; i <= 10; i++)	//od karty '2'/'3'/... do '10'
	{
		for (int j = 1; j <= 4; j++, numer_karty++)	//dla ♠ ♥ ♦ ♣
		{
			karta[numer_karty].wartosc.numer = i;

			//opcja 1^
			if (j == pik)
				karta[numer_karty].kolor = pik;
			else if (j == kier)
				karta[numer_karty].kolor = kier;
			else if (j == karo)
				karta[numer_karty].kolor = karo;
			else if (j == trefl)
				karta[numer_karty].kolor = trefl;
		}
	}

	for (i = 11; i <= 14; i++)	//od karty 'J' do 'A'
	{
		for (int j = 1; j <= 4; j++, numer_karty++)	//dla ♠ ♥ ♦ ♣
		{
			karta[numer_karty].wartosc.znak = (enum ZnakKarty_t)(i);

			//opcja 2^
			karta[numer_karty].kolor = (enum KolorKarty_t)j;
		}
	}
}

void TasowanieTali(karta_t* karta, int ilosc_kart)
{
	int losowa_karta;
	int i;
	karta_t zmienna_karta;

	for (i = 0; i < ilosc_kart; i++)
	{
		losowa_karta = rand() % ilosc_kart;
		zmienna_karta = karta[losowa_karta];
		karta[losowa_karta] = karta[i];
		karta[i] = zmienna_karta;
	}
}

void PrzypiszRekeXY(gracz_t* Gx, gracz_t* Gy, karta_t stos_kart[], int ilosc_kart)
{
	Gx->reka.koniec = Gx->reka.ilosc = ilosc_kart / 2;	//Gracze mają po połowie tali
	Gy->reka.koniec = Gy->reka.ilosc = ilosc_kart / 2;

	int i = 0;
	while (ilosc_kart > 0)
	{
		Gx->reka.karta[i] = stos_kart[--ilosc_kart];
		Gy->reka.karta[i++] = stos_kart[--ilosc_kart];
	}
}

void Przenies_Z_Do(kolejka_t* from, kolejka_t* to, int ile)
{
	if (from->ilosc >= ile)
	{
		to->koniec = to->poczatek + to->ilosc;

		while (ile > 0)
		{
			if (to->koniec >= to->rozmiar)
				to->koniec -= to->rozmiar;

			if (from->poczatek == from->rozmiar)
				from->poczatek = 0;

			to->karta[to->koniec++] = from->karta[from->poczatek++];
			to->ilosc++;
			from->ilosc--;
			ile--;
		}
	}
	else
	{
		cout << endl << "Blad w 'Przenies_Z_Do'<---------------" << endl;
		return;
	}
}

void WyczyscPlansze(stan_gry_t* Stan, gracz_t* Gx, gracz_t* Gy)
{
	Stan->kto_zabiera_karte = nikt;
	Stan->stan_gry = kontynuuj;
	Stan->ruchy_w_grze = 0;

	Gx->reka.poczatek = 0;
	Gy->reka.poczatek = 0;

	Gx->wojna.poczatek = Gx->wojna.ilosc = Gx->wojna.koniec = 0;
	Gy->wojna.poczatek = Gy->wojna.ilosc = Gy->wojna.koniec = 0;

#ifdef MADRA_WOJNA
	Gx->tymczasowe.poczatek = Gx->tymczasowe.ilosc = Gx->tymczasowe.koniec = 0;
	Gx->tymczasowe.poczatek = Gx->tymczasowe.ilosc = Gx->tymczasowe.koniec = 0;
	Stan->karty_zwyciescy.poczatek = Stan->karty_zwyciescy.ilosc = Stan->karty_zwyciescy.koniec = 0;
#endif // MADRA_WOJNA

#ifdef GRAFIKA_TEKSTOWA
	system("cls");
#endif // GRAFIKA_TEKSTOWA

}

void Wybor(gracz_t* Gracz, gracz_t* Przeciwnik)
{
	int pierwsza_karta, wybrana_karta;
	karta_t zmienna_karta;

	if (Przeciwnik->wojna.poczatek == Przeciwnik->wojna.rozmiar )
		Przeciwnik->wojna.poczatek = 0;

	if (Gracz->strategia == losowa)
	{	// 0- poprawna pozycja kary, 1- zamiana na zerowe miejsce
		pierwsza_karta = rand() % 2;	
		if (pierwsza_karta == 1)
		{
			zmienna_karta = Gracz->tymczasowe.karta[1];
			Gracz->tymczasowe.karta[1] = Gracz->tymczasowe.karta[0];
			Gracz->tymczasowe.karta[0] = zmienna_karta;
		}
	}
	else if (Gracz->strategia == wsciekla)
	{
		if (Przeciwnik->wojna.karta[Przeciwnik->wojna.poczatek].wartosc.numer == Gracz->tymczasowe.karta[0].wartosc.numer)
		{	//nic nie trzeba zmieniac
		}
		else if (Przeciwnik->wojna.karta[Przeciwnik->wojna.poczatek].wartosc.numer == Gracz->tymczasowe.karta[1].wartosc.numer)
		{	//zamiana
			zmienna_karta = Gracz->tymczasowe.karta[1];
			Gracz->tymczasowe.karta[1] = Gracz->tymczasowe.karta[0];
			Gracz->tymczasowe.karta[0] = zmienna_karta;
		}
		else if (Przeciwnik->wojna.karta[Przeciwnik->wojna.poczatek].wartosc.numer < Gracz->tymczasowe.karta[0].wartosc.numer)
		{
			if (Przeciwnik->wojna.karta[Przeciwnik->wojna.poczatek].wartosc.numer < Gracz->tymczasowe.karta[1].wartosc.numer)
			{
				if (Gracz->tymczasowe.karta[0].wartosc.numer < Gracz->tymczasowe.karta[1].wartosc.numer)
				{	//nic nie trzeba robic
				}
				else
				{	//zamiana
					zmienna_karta = Gracz->tymczasowe.karta[1];
					Gracz->tymczasowe.karta[1] = Gracz->tymczasowe.karta[0];
					Gracz->tymczasowe.karta[0] = zmienna_karta;
				}
			}
		}
		else if (Przeciwnik->wojna.karta[Przeciwnik->wojna.poczatek].wartosc.numer < Gracz->tymczasowe.karta[1].wartosc.numer)
		{	//zamiana
			zmienna_karta = Gracz->tymczasowe.karta[1];
			Gracz->tymczasowe.karta[1] = Gracz->tymczasowe.karta[0];
			Gracz->tymczasowe.karta[0] = zmienna_karta;
		}
		else if (Gracz->tymczasowe.karta[1].wartosc.numer < Gracz->tymczasowe.karta[0].wartosc.numer)
		{	//zamiana
			zmienna_karta = Gracz->tymczasowe.karta[1];
			Gracz->tymczasowe.karta[1] = Gracz->tymczasowe.karta[0];
			Gracz->tymczasowe.karta[0] = zmienna_karta;
		}
	}
	else if (Gracz->strategia == pokojowa)
	{
		if (Przeciwnik->wojna.karta[Przeciwnik->wojna.poczatek].wartosc.numer > Gracz->tymczasowe.karta[0].wartosc.numer)
		{	//nic nie trzeba robic
		}
		else if (Przeciwnik->wojna.karta[Przeciwnik->wojna.poczatek].wartosc.numer > Gracz->tymczasowe.karta[1].wartosc.numer)
		{	//zamiana
			zmienna_karta = Gracz->tymczasowe.karta[1];
			Gracz->tymczasowe.karta[1] = Gracz->tymczasowe.karta[0];
			Gracz->tymczasowe.karta[0] = zmienna_karta;
		}
		else if (Przeciwnik->wojna.karta[Przeciwnik->wojna.poczatek].wartosc.numer == Gracz->tymczasowe.karta[0].wartosc.numer)
		{	//zamiana
			zmienna_karta = Gracz->tymczasowe.karta[1];
			Gracz->tymczasowe.karta[1] = Gracz->tymczasowe.karta[0];
			Gracz->tymczasowe.karta[0] = zmienna_karta;
		}
		else if (Przeciwnik->wojna.karta[Przeciwnik->wojna.poczatek].wartosc.numer == Gracz->tymczasowe.karta[1].wartosc.numer)
		{	//nic nie trzeba robic
		}
		else if (Gracz->tymczasowe.karta[1].wartosc.numer < Gracz->tymczasowe.karta[0].wartosc.numer)
		{	//zamiana
			zmienna_karta = Gracz->tymczasowe.karta[1];
			Gracz->tymczasowe.karta[1] = Gracz->tymczasowe.karta[0];
			Gracz->tymczasowe.karta[0] = zmienna_karta;
		}
	}
	else if (Gracz->strategia == wlasna)	// czyli rozgrywka razem z interfejsem
	{
		gotoxy(5, 6);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		cout << "Gracz X";
		Plansza_Karta(3, 6, Gracz->tymczasowe, dwie);

		cout << "\nPrzeciwnik wyrzucil: ";
		WypiszKarte(Przeciwnik->wojna.karta[Przeciwnik->wojna.poczatek]);
		cout << "\nWyciagniete 2 karty to: ";
		WypiszKarte(Gracz->tymczasowe.karta[0]);
		WypiszKarte(Gracz->tymczasowe.karta[1]);
		cout << "\nWybierasz karte (1/2): ";
		cin >> wybrana_karta;

		if (wybrana_karta == 2)
		{	//zamiana
			zmienna_karta = Gracz->tymczasowe.karta[1];
			Gracz->tymczasowe.karta[1] = Gracz->tymczasowe.karta[0];
			Gracz->tymczasowe.karta[0] = zmienna_karta;
		}
	}
}

void WyczyscPojemnik(kolejka_t* Pojemnik)
{
	Pojemnik->ilosc = Pojemnik->koniec = Pojemnik->poczatek = 0;
}

PrzydzielenieKarty_t Porownanie(stan_gry_t* Stan, gracz_t* Gx, gracz_t* Gy)
{
	if (Gx->wojna.karta[Gx->wojna.koniec - 1].wartosc.numer > Gy->wojna.karta[Gy->wojna.koniec - 1].wartosc.numer)
	{
#ifdef DEMONSTRACJA

		cout << "	zabieraX\n";

#endif //DEMONSTRACJA

		return zabieraX;
	}
	else if (Gx->wojna.karta[Gx->wojna.koniec - 1].wartosc.numer < Gy->wojna.karta[Gy->wojna.koniec - 1].wartosc.numer)
	{
#ifdef DEMONSTRACJA

		cout << "	zabieraY\n";

#endif //DEMONSTRACJA

		return zabieraY;
	}
	else
	{
#ifdef DEMONSTRACJA
		cout << "\nWojna!: ";
#endif //DEMONSTRACJA
		return Wojna(Stan, Gx, Gy);
	}
}

PrzydzielenieKarty_t Wojna(stan_gry_t* Stan, gracz_t* Gx, gracz_t* Gy)
{
	if (Gx->reka.ilosc <= 0 || Gy->reka.ilosc <= 0)
		return nikt;
	else if ((Gx->reka.ilosc == 1 || Gy->reka.ilosc == 1) && Stan->wariant == 'A')
		return nikt;
	else if (Stan->wariant == 'B' && (Gx->reka.ilosc <= 2 || Gy->reka.ilosc <= 2))
	{	//wariant B
		Stan->wariant = 'A';
		if (Gx->reka.ilosc == 1 && Gy->reka.ilosc > 4)
		{
			Przenies_Z_Do(&(Gy->reka), &(Gx->wojna), 2);
			Stan->ruchy_w_grze++;

			Przenies_Z_Do(&(Gy->reka), &(Gy->wojna), 2);
			Stan->ruchy_w_grze++;
		}
		else if (Gx->reka.ilosc == 2 && Gy->reka.ilosc > 2)
		{
			Przenies_Z_Do(&(Gy->reka), &(Gx->wojna), 1);
			Przenies_Z_Do(&(Gy->reka), &(Gy->wojna), 1);
			Stan->ruchy_w_grze++;

			Przenies_Z_Do(&(Gy->reka), &(Gy->wojna), 1);
			Przenies_Z_Do(&(Gx->reka), &(Gx->wojna), 1);
			Stan->ruchy_w_grze++;
		}
		else if (Gy->reka.ilosc == 1 && Gx->reka.ilosc > 4)
		{
			Przenies_Z_Do(&(Gx->reka), &(Gy->wojna), 2);
			Stan->ruchy_w_grze++;

			Przenies_Z_Do(&(Gx->reka), &(Gx->wojna), 2);
			Stan->ruchy_w_grze++;
		}
		else if (Gy->reka.ilosc == 2 && Gx->reka.ilosc > 2)
		{
			Przenies_Z_Do(&(Gx->reka), &(Gy->wojna), 1);
			Przenies_Z_Do(&(Gx->reka), &(Gx->wojna), 1);
			Stan->ruchy_w_grze++;

			Przenies_Z_Do(&(Gy->reka), &(Gy->wojna), 1);
			Przenies_Z_Do(&(Gx->reka), &(Gx->wojna), 1);
			Stan->ruchy_w_grze++;
		}
		else
		{
			return Wojna(Stan, Gx, Gy);
		}
	}
	else
	{	//madra wojna
		if (Gx->tymczasowe.ilosc > 0)
		{
			Przenies_Z_Do(&(Gx->tymczasowe), &(Gx->wojna), 1);
			Przenies_Z_Do(&(Gx->reka), &(Gx->wojna), 1);
			Stan->ruchy_w_grze++;

			Przenies_Z_Do(&(Gy->reka), &(Gy->wojna), 2);
			Stan->ruchy_w_grze++;
		}
		else if (Gy->tymczasowe.ilosc > 0)
		{
			Przenies_Z_Do(&(Gy->tymczasowe), &(Gy->wojna), 1);
			Przenies_Z_Do(&(Gy->reka), &(Gy->wojna), 1);
			Stan->ruchy_w_grze++;

			Przenies_Z_Do(&(Gx->reka), &(Gx->wojna), 2);
			Stan->ruchy_w_grze++;
		}
		else
		{	//zwykła wojna
			Przenies_Z_Do(&(Gx->reka), &(Gx->wojna), 2);
			Stan->ruchy_w_grze++;

			Przenies_Z_Do(&(Gy->reka), &(Gy->wojna), 2);
			Stan->ruchy_w_grze++;
		}
	}
#ifdef DEMONSTRACJA
	int i, j;
	for (i = 0; i < Gx->wojna.ilosc; i++)
	{
		j = (Gx->wojna.poczatek + i) % Gx->wojna.rozmiar;
		if (i % 2)	//wypis X na pozycjach nieparzystych
		{
			cout << "X|";
		}
		else
			WypiszKarte(Gx->wojna.karta[j]);
	}

	cout << " vs ";

	for (i = 0; i < Gy->wojna.ilosc; i++)
	{
		j = (Gy->wojna.poczatek + i) % Gy->wojna.rozmiar;
		if (i % 2)	//wypis X na pozycjach nieparzystych
		{
			cout << "X|";
		}
		else
			WypiszKarte(Gy->wojna.karta[j]);
	}

#endif //DEMONSTRACJA

	return Porownanie(Stan, Gx, Gy);
}

void Bitwa(stan_gry_t* Stan, gracz_t* Gx, gracz_t* Gy)
{
	while (Stan->stan_gry == kontynuuj && Gx->reka.ilosc > 0 && Gy->reka.ilosc > 0)
	{
#ifdef DEMONSTRACJA

#ifdef GRAFIKA_TEKSTOWA

		gotoxy(1, 0);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		cout << "Reka X:";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 96);

#endif // GRAFIKA_TEKSTOWA
		
#ifndef GRAFIKA_TEKSTOWA

		cout << "\n------------------------\n";
		cout<<"Gx reka:";

#endif // !GRAFIKA_TEKSTOWA

		int i, j, k=0;

		for (i = 0; i < Gx->reka.ilosc; i++)
		{
			j = (Gx->reka.poczatek + i) % Gx->reka.rozmiar;

			if ((i % MAX_LINIA) == 0 && i != 0)
				cout << "\n" << "	";	//odstep
			WypiszKarte(Gx->reka.karta[j]);
		}

#ifdef GRAFIKA_TEKSTOWA

		gotoxy(50, k);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		cout << "Reka Y:";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 96);

#endif // GRAFIKA_TEKSTOWA

#ifndef GRAFIKA_TEKSTOWA

		cout << "\nGy reka:";

#endif // !GRAFIKA_TEKSTOWA

		for (i = 0; i < Gy->reka.ilosc; i++)
		{
			j = (Gy->reka.poczatek + i) % Gy->reka.rozmiar;
			
			if ((i % MAX_LINIA) == 0 && i != 0)
			{
				cout << "\n";

#ifdef GRAFIKA_TEKSTOWA

				gotoxy(57, ++k);

#endif // GRAFIKA_TEKSTOWA

#ifndef GRAFIKA_TEKSTOWA

				cout << "	";	//odstep

#endif // !GRAFIKA_TEKSTOWA

			}
			WypiszKarte(Gy->reka.karta[j]);
		}
		cout << "\n";


#endif // DEMONSTRACJA

		if (Stan->ruchy_w_grze > NIESKONCZONA_ROZGRYWKA)
		{
			Stan->stan_gry = zakoncz;
			break;
		}
		
		if (Stan->rodzaj_gry == madra_wojna)
		{
			if (Stan->kto_dwie_karty == graczX)
			{
				if (Gy->tymczasowe.ilosc > 0)	//gdy gracz trzyma juz jakas karte
					Przenies_Z_Do(&(Gy->tymczasowe), &(Gy->wojna), 1);
				else
					Przenies_Z_Do(&(Gy->reka), &(Gy->wojna), 1);

				if (Gx->reka.ilosc >= 2)		//dopoki gracz moze wyciagnac 2 karty
				{
					Przenies_Z_Do(&(Gx->reka), &(Gx->tymczasowe), 2);
					Wybor(Gx, Gy);
					Przenies_Z_Do(&(Gx->tymczasowe), &(Gx->wojna), 1);
				}
				else							//gdy ma juz tylko jedna karte
				{
					Przenies_Z_Do(&(Gx->reka), &(Gx->wojna), 1);
				}
			}
			else	// dwie karty graczY
			{
				if (Gx->tymczasowe.ilosc > 0)	//gdy gracz trzyma juz jakas karte
					Przenies_Z_Do(&(Gx->tymczasowe), &(Gx->wojna), 1);
				else
					Przenies_Z_Do(&(Gx->reka), &(Gx->wojna), 1);

				if (Gy->reka.ilosc >= 2)		//dopoki gracz moze wyciagnac 2 karty
				{
					Przenies_Z_Do(&(Gy->reka), &(Gy->tymczasowe), 2);
					Wybor(Gy, Gx);
					Przenies_Z_Do(&(Gy->tymczasowe), &(Gy->wojna), 1);
				}
				else							//gdy ma juz tylko jedna karte
				{
					Przenies_Z_Do(&(Gy->reka), &(Gy->wojna), 1);
				}
			}

			Stan->kto_dwie_karty = (++Stan->kto_dwie_karty) % 2;	//zmiana osoby bioracej dwie karty
		}
		else	//zwykla wojna
		{
			Przenies_Z_Do(&(Gx->reka), &(Gx->wojna), 1);
			Przenies_Z_Do(&(Gy->reka), &(Gy->wojna), 1);
		}
		Stan->ruchy_w_grze++;

#ifdef DEMONSTRACJA

		cout << "\nBitwa: ";
		for (i = 0; i < Gx->wojna.ilosc; i++)
		{
			j = (Gx->wojna.poczatek + i) % Gx->wojna.rozmiar;

			WypiszKarte(Gx->wojna.karta[j]);
		}

		cout << " vs ";

		for (i = 0; i < Gy->wojna.ilosc; i++)
		{
			j = (Gy->wojna.poczatek + i) % Gy->wojna.rozmiar;

			WypiszKarte(Gy->wojna.karta[j]);
		}

#ifdef MADRA_WOJNA

		cout << "\nGx trzyma: ";
		for (i = 0; i < Gx->tymczasowe.ilosc; i++)
		{
			j = (Gx->tymczasowe.poczatek + i) % Gx->tymczasowe.rozmiar;

			WypiszKarte(Gx->tymczasowe.karta[j]);
		}

		cout << "\nGy trzyma: ";

		for (i = 0; i < Gy->tymczasowe.ilosc; i++)
		{
			j = (Gy->tymczasowe.poczatek + i) % Gy->tymczasowe.rozmiar;

			WypiszKarte(Gy->tymczasowe.karta[j]);
		}
#endif // MADRA_WOJNA

#endif // DEMONSTRACJA

		Stan->kto_zabiera_karte = Porownanie(Stan, Gx, Gy);

		if (Stan->kto_zabiera_karte == zabieraX)
		{
			if (Stan->rodzaj_gry == madra_wojna)
			{
				WyczyscPojemnik(&(Stan->karty_zwyciescy));		// tasowanie nastepuje od poczatku pojemnika

				Przenies_Z_Do(&(Gx->wojna), &(Stan->karty_zwyciescy), Gx->wojna.ilosc);
				Przenies_Z_Do(&(Gy->wojna), &(Stan->karty_zwyciescy), Gy->wojna.ilosc);

#ifdef MADRA_WOJNA

#ifdef DEMONSTRACJA

				cout << "\nPrzed tasowaniem: ";

				for (i = 0; i < Stan->karty_zwyciescy.ilosc; i++)
				{
					j = (Stan->karty_zwyciescy.poczatek + i) % Stan->karty_zwyciescy.rozmiar;

					WypiszKarte(Stan->karty_zwyciescy.karta[j]);
				}
				cout << "\n";

#endif // DEMONSTRACJA

				TasowanieTali(Stan->karty_zwyciescy.karta, Stan->karty_zwyciescy.ilosc);

#ifdef DEMONSTRACJA

				cout << "\nPo tasowaniu: ";

				for (i = 0; i < Stan->karty_zwyciescy.ilosc; i++)
				{
					j = (Stan->karty_zwyciescy.poczatek + i) % Stan->karty_zwyciescy.rozmiar;

					WypiszKarte(Stan->karty_zwyciescy.karta[j]);
				}
				cout << "\n";

#endif // DEMONSTRACJA

#endif // MADRA_WOJNA	

				Przenies_Z_Do(&(Stan->karty_zwyciescy), &(Gx->reka), Stan->karty_zwyciescy.ilosc);
			}
			else
			{
				Przenies_Z_Do(&(Gx->wojna), &(Gx->reka), Gx->wojna.ilosc);
				Przenies_Z_Do(&(Gy->wojna), &(Gx->reka), Gy->wojna.ilosc);
			}
		}
		else if (Stan->kto_zabiera_karte == zabieraY)
		{
			if (Stan->rodzaj_gry == madra_wojna)
			{
				WyczyscPojemnik(&(Stan->karty_zwyciescy));

				Przenies_Z_Do(&(Gx->wojna), &(Stan->karty_zwyciescy), Gx->wojna.ilosc);
				Przenies_Z_Do(&(Gy->wojna), &(Stan->karty_zwyciescy), Gy->wojna.ilosc);

#ifdef MADRA_WOJNA
	
#ifdef DEMONSTRACJA

				cout << "\nPrzed tasowaniem: ";

				for (i = 0; i < Stan->karty_zwyciescy.ilosc; i++)
				{
					j = (Stan->karty_zwyciescy.poczatek + i) % Stan->karty_zwyciescy.rozmiar;

					WypiszKarte(Stan->karty_zwyciescy.karta[j]);
				}
				cout << "\n";

#endif // DEMONSTRACJA

				TasowanieTali(Stan->karty_zwyciescy.karta, Stan->karty_zwyciescy.ilosc);

#ifdef DEMONSTRACJA

				cout << "\nPo tasowaniu: ";

				for (i = 0; i < Stan->karty_zwyciescy.ilosc; i++)
				{
					j = (Stan->karty_zwyciescy.poczatek + i) % Stan->karty_zwyciescy.rozmiar;

					WypiszKarte(Stan->karty_zwyciescy.karta[j]);
				}
				cout << "\n";

#endif // DEMONSTRACJA

#endif // MADRA_WOJNA	

				Przenies_Z_Do(&(Stan->karty_zwyciescy), &(Gy->reka), Stan->karty_zwyciescy.ilosc);
			}
			else
			{
				Przenies_Z_Do(&(Gy->wojna), &(Gy->reka), Gy->wojna.ilosc);
				Przenies_Z_Do(&(Gx->wojna), &(Gy->reka), Gx->wojna.ilosc);
			}
		}
		else
		{
			Stan->stan_gry = zakoncz;
		}
	}

	if (Gx->reka.ilosc < 2 && Gy->reka.ilosc < 2)
	{
		Stan->remisy++;
		Stan->stan_gry = zakoncz;
#ifdef DEMONSTRACJA
		cout << endl << "Remis!" << endl;
#endif // DEMONSTRACJA
	}
	else if (Gx->reka.ilosc < 2)
	{
		Stan->zwyciestwa_gY++;
		Stan->stan_gry = zakoncz;
#ifdef DEMONSTRACJA
		cout << endl << "Zwycieza graczY!" << endl;
#endif // DEMONSTRACJA
	}
	else if (Gy->reka.ilosc < 2)
	{
		Stan->zwyciestwa_gX++;
		Stan->stan_gry = zakoncz;
#ifdef DEMONSTRACJA
		cout << endl << "Zwycieza graczX!" << endl;
#endif // DEMONSTRACJA
	}
	else
	{
		//cout << endl << "Przepelnie!" << endl;
		Stan->remisy++;
	}
	Stan->ile_gier++;
}

void PrzypiszRange(gracz_t* Gx, gracz_t* Gy, int* rangaX, int* rangaY, ktora_ranga_t ktora_ranga)
{
	for (int i = 0; i < Gx->reka.koniec; i++)
	{
		if (ktora_ranga == ranga1)
		{	//Ranga reki: 'A'-14pkt, 'K'-13pkt,...,'2'-2pkt
			*rangaX += Gx->reka.karta[i].wartosc.numer;
			*rangaY += Gy->reka.karta[i].wartosc.numer;
		}
		else if (ktora_ranga == ranga2)
		{	//Ranga reki: 'A'-14pkt, 'K'-13pkt, 'Q'-12pkt, 'J'- 11pkt, '10' - 10pkt
			if (Gx->reka.karta[i].wartosc.numer >= 10)
				*rangaX += Gx->reka.karta[i].wartosc.numer;

			if (Gy->reka.karta[i].wartosc.numer >= 10)
				*rangaY += Gy->reka.karta[i].wartosc.numer;			
		}
		else if (ktora_ranga == ranga3)
		{	//Ranga reki: 'A'-4pkt, 'K'-3pkt, 'Q'-2pkt, 'J'- 1pkt
			//			  'A','A' - +14pkt , 'K','K' - +13pkt,(...), '2','2' - 2pkt 
			if (Gx->reka.karta[i].wartosc.numer > 10)
				*rangaX += (Gx->reka.karta[i].wartosc.numer - 10);

			if (Gy->reka.karta[i].wartosc.numer > 10)
				*rangaY += (Gy->reka.karta[i].wartosc.numer - 10);

			if (i > 0)
			{
				if (Gx->reka.karta[i].wartosc.numer == Gx->reka.karta[i - 1].wartosc.numer)
					*rangaX += Gx->reka.karta[i].wartosc.numer;

				if (Gy->reka.karta[i].wartosc.numer == Gy->reka.karta[i - 1].wartosc.numer)
					*rangaY += Gy->reka.karta[i].wartosc.numer;
			}
		}
	}
}

void Eksperyment_2(karta_t* karty, gracz_t* GraczX, gracz_t* GraczY, stan_gry_t* Stan_Wojny, ktora_ranga_t ktora_ranga)
{
	int eksperyment_talia, eksperyment_ilosc_kart, ranga_X, ranga_Y, zwyciestwaX = 0, zwyciestwaY = 0;

	for (eksperyment_talia = 1; eksperyment_talia < 10; eksperyment_talia++)
	{
		eksperyment_ilosc_kart = (14 - eksperyment_talia) * 4;

		StworzTalie(karty, eksperyment_talia);

		cout << "\nTalia nr." << eksperyment_talia << ":";

		for (int i = 0; i < 100; i++)
		{
			ranga_X = 0;
			ranga_Y = 0;

			TasowanieTali(karty, eksperyment_ilosc_kart);

			PrzypiszRekeXY(GraczX, GraczY, karty, eksperyment_ilosc_kart);

			PrzypiszRange(GraczX, GraczY, &ranga_X, &ranga_Y, ktora_ranga);

			WyczyscPlansze(Stan_Wojny, GraczX, GraczY);

			Bitwa(Stan_Wojny, GraczX, GraczY);

			cout << "\n" << ranga_X << ";";
			if (Stan_Wojny->zwyciestwa_gX > zwyciestwaX)
			{
				zwyciestwaX++;
				cout << 1;	//wygrana
			}
			else
				cout << 0;	//porazka

			cout << "\n" << ranga_Y << ";";
			if (Stan_Wojny->zwyciestwa_gY > zwyciestwaY)
			{
				zwyciestwaY++;
				cout << 1;
			}
			else
				cout << 0;
			cout << "\n";
		}
	}
	cout << "\n";
	Stan_Wojny->zwyciestwa_gY = Stan_Wojny->zwyciestwa_gX = 0;
}

void Symulacje_1000(karta_t* karty, gracz_t* GraczX, gracz_t* GraczY, stan_gry_t* Stan_Wojny)
{
	for (int i = 0; i < 1000; i++)
	{
		TasowanieTali(karty, MAX_KART);

		PrzypiszRekeXY(GraczX, GraczY, karty, MAX_KART);

		WyczyscPlansze(Stan_Wojny, GraczX, GraczY);

		Bitwa(Stan_Wojny, GraczX, GraczY);
	}
	cout << "\nIle gier: " << Stan_Wojny->ile_gier;
	cout << "\nIle zwyciestwX: " << Stan_Wojny->zwyciestwa_gX;
	cout << "\nIle zwyciestwY: " << Stan_Wojny->zwyciestwa_gY;
	cout << "\nIle remisow: " << Stan_Wojny->remisy;
	cout << "(" << ((float)Stan_Wojny->zwyciestwa_gX / (Stan_Wojny->ile_gier-Stan_Wojny->remisy)) * 100 << "% - " << ((float)Stan_Wojny->zwyciestwa_gY / (Stan_Wojny->ile_gier - Stan_Wojny->remisy)) * 100 << "%)\n";

	Stan_Wojny->ile_gier = Stan_Wojny->zwyciestwa_gX = Stan_Wojny->zwyciestwa_gY = Stan_Wojny->remisy = 0;
}