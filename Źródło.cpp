#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include<conio.h>
#include"funkcje.h"

#define MAX_KART 52
//#define TEST1
//#define TEST2
//#define DEMONSTRACJA
//#define EKSPERYMENT_1
//#define EKSPERYMENT_2
#define MADRA_WOJNA_DEMONSTRACJA
//#define MADRA_WOJNA_EKSPERYMENT_1
//#define MADRA_WOJNA_EKSPERYMENT_2

using namespace std;

int main()
{
	srand(time(NULL));

	//const int numer_tali = 1;
	//const int ilosc_kart = (14 - numer_tali) * 4;	//wzór na ilosc kart

	karta_t karty[MAX_KART];

	gracz_t GraczX, GraczY;

	stan_gry_t Stan_Wojny;

	GraczX.reka.rozmiar = MAX_KART;
	GraczY.reka.rozmiar = MAX_KART;

	GraczX.wojna.rozmiar = MAX_KART / 2;
	GraczY.wojna.rozmiar = MAX_KART / 2;

	Stan_Wojny.karty_zwyciescy.rozmiar = MAX_KART;	//pojemniki do "madrej wojny"
	GraczX.tymczasowe.rozmiar = 2;
	GraczY.tymczasowe.rozmiar = 2;

	GraczX.reka.karta = (karta_t*)malloc(GraczX.reka.rozmiar * sizeof karta_t);	//przypisanie rozmiaru RĄK graczy
	GraczY.reka.karta = (karta_t*)malloc(GraczY.reka.rozmiar * sizeof karta_t);

	GraczX.wojna.karta = (karta_t*)malloc(GraczX.wojna.rozmiar * sizeof karta_t);	//pojemnik na karty w bitwie/wojnie może posiadać maksymalnie połowe tali
	GraczY.wojna.karta = (karta_t*)malloc(GraczY.wojna.rozmiar * sizeof karta_t);
	
	Stan_Wojny.karty_zwyciescy.karta = (karta_t*)malloc(Stan_Wojny.karty_zwyciescy.rozmiar * sizeof karta_t);
	GraczX.tymczasowe.karta = (karta_t*)malloc(GraczX.tymczasowe.rozmiar * sizeof karta_t);
	GraczY.tymczasowe.karta = (karta_t*)malloc(GraczY.tymczasowe.rozmiar * sizeof karta_t);

#ifdef TEST_
	cout << "Karty RekaX:" << endl;

	for (int i = 0; i < ilosc_kart / 2; i++)
	{
		cout << i + 1 << "	" << GraczX.reka.karta[i].kolor << "  ";
		cout << GraczX.reka.karta[i].wartosc.numer << endl;
	}

	cout << "Karty RekaY:" << endl;

	for (int i = 0; i < ilosc_kart / 2; i++)
	{
		cout << i + 1 << "	" << GraczY.reka.karta[i].kolor << "  ";
		cout << GraczY.reka.karta[i].wartosc.numer << endl;
	}
#endif // TEST



#ifdef EKSPERYMENT_1

	Stan_Wojny.wariant = 'A';

	int eksperyment_talia, eksperyment_ilosc_kart;

	for (eksperyment_talia = 1; eksperyment_talia < 10; eksperyment_talia++)
	{
		eksperyment_ilosc_kart = (14 - eksperyment_talia) * 4;

		StworzTalie(karty, eksperyment_talia);

		Stan_Wojny.ruchy_suma = 0;

		cout << "\nTalia nr." << eksperyment_talia << ", wariant A: ";

		for (int i = 0; i < 10000; i++)
		{
			TasowanieTali(karty, eksperyment_ilosc_kart);

			PrzypiszRekeXY(&GraczX, &GraczY, karty, eksperyment_ilosc_kart);

			WyczyscPlansze(&Stan_Wojny, &GraczX, &GraczY);

			Bitwa(&Stan_Wojny, &GraczX, &GraczY);

			Stan_Wojny.ruchy_suma += Stan_Wojny.ruchy_w_grze;
		}
		cout << "\nSrednia ilosc ruchow: " << Stan_Wojny.ruchy_suma / 10000;
	}
	cout << "\n";

	Stan_Wojny.wariant = 'B';

	for (eksperyment_talia = 1; eksperyment_talia < 10; eksperyment_talia++)
	{
		eksperyment_ilosc_kart = (14 - eksperyment_talia) * 4;

		StworzTalie(karty, eksperyment_talia);

		Stan_Wojny.ruchy_suma = 0;

		cout << "\nTalia nr." << eksperyment_talia << ", wariant B: ";

		for (int i = 0; i < 10000; i++)
		{
			TasowanieTali(karty, eksperyment_ilosc_kart);

			PrzypiszRekeXY(&GraczX, &GraczY, karty, eksperyment_ilosc_kart);

			WyczyscPlansze(&Stan_Wojny, &GraczX, &GraczY);

			Bitwa(&Stan_Wojny, &GraczX, &GraczY);

			Stan_Wojny.ruchy_suma += Stan_Wojny.ruchy_w_grze;
		}
		cout << "\nSrednia ilosc ruchow: " << Stan_Wojny.ruchy_suma / 10000;
	}
	cout << "\n";

#endif // EKSPERYMENT_1

#ifdef DEMONSTRACJA

	int wybor_tali, wybrany_rozmiar;
	char wybor_wariant;

	cout << "Podaj numer tali ktora wybierasz (1:'2'-'A', 2:'3'-'A',...,9:'10'-'A'): ";
	do
	{
		cin >> wybor_tali;
	} while (wybor_tali < 1 || wybor_tali>9);

	cout << "Podaj wariant(A/B): ";
	do
	{
		cin >> wybor_wariant;
	} while (wybor_wariant != 'A' && wybor_wariant != 'B');

	wybrany_rozmiar = (14 - wybor_tali) * 4;	//wzór na ilosc kart

	Stan_Wojny.wariant = wybor_wariant;

	Stan_Wojny.rodzaj_gry = zwykla_wojna;

	StworzTalie(karty, wybor_tali);

	TasowanieTali(karty, wybrany_rozmiar);

	PrzypiszRekeXY(&GraczX, &GraczY, karty, wybrany_rozmiar);

	WyczyscPlansze(&Stan_Wojny, &GraczX, &GraczY);

	Bitwa(&Stan_Wojny, &GraczX, &GraczY);
#endif // DEMONSTRACJA


#ifdef EKSPERYMENT_2

	ktora_ranga_t ktora_ranga = ranga1;

	cout << "Ranga reki: 'A'-14pkt, 'K'- 13pkt,...,'2'-2pkt.\n";

	Stan_Wojny.wariant = 'A';

	Eksperyment_2(karty, &GraczX, &GraczY, &Stan_Wojny, ktora_ranga);

	Stan_Wojny.wariant = 'B';

	Eksperyment_2(karty, &GraczX, &GraczY, &Stan_Wojny, ktora_ranga);

	ktora_ranga = ranga2;

	cout << "Ranga reki: 'A'-14pkt, 'K'-13pkt, 'Q'-12pkt, 'J'- 11pkt, '10' - 10pkt.\n";

	Stan_Wojny.wariant = 'A';

	Eksperyment_2(karty, &GraczX, &GraczY, &Stan_Wojny, ktora_ranga);

	Stan_Wojny.wariant = 'B';

	Eksperyment_2(karty, &GraczX, &GraczY, &Stan_Wojny, ktora_ranga);

	ktora_ranga = ranga3;

	cout << "Ranga reki: 'A'-4pkt, 'K'-3pkt, 'Q'-2pkt, 'J'- 1pkt oraz 'A','A' - +14pkt , 'K','K' - +13pkt,(...), '2','2' - 2pkt \n";

	Stan_Wojny.wariant = 'A';

	Eksperyment_2(karty, &GraczX, &GraczY, &Stan_Wojny, ktora_ranga);

	Stan_Wojny.wariant = 'B';

	Eksperyment_2(karty, &GraczX, &GraczY, &Stan_Wojny, ktora_ranga);
	
#endif //EKSPERYMENT_2

#ifdef MADRA_WOJNA_DEMONSTRACJA

	Stan_Wojny.wariant = 'A';
	Stan_Wojny.rodzaj_gry = madra_wojna;

	GraczX.strategia = wlasna;
	GraczY.strategia = pokojowa;

	int wybor_tali, wybrany_rozmiar;

	cout << "Podaj numer tali ktora wybierasz (1:'2'-'A', 2:'3'-'A',...,9:'10'-'A'): ";
	do
	{
		cin >> wybor_tali;
	} while (wybor_tali < 1 || wybor_tali>9);

	system("cls");

	wybrany_rozmiar = (14 - wybor_tali) * 4;	//wzór na ilosc kart

	StworzTalie(karty, wybor_tali);

	TasowanieTali(karty, wybrany_rozmiar);

	PrzypiszRekeXY(&GraczX, &GraczY, karty, wybrany_rozmiar);

	WyczyscPlansze(&Stan_Wojny, &GraczX, &GraczY);

	Bitwa(&Stan_Wojny, &GraczX, &GraczY);
	
#endif // MADRA_WOJNA

#ifdef MADRA_WOJNA_EKSPERYMENT_1

	Stan_Wojny.wariant = 'A';

	Stan_Wojny.rodzaj_gry = madra_wojna;

	int eksperyment_talia, eksperyment_ilosc_kart;

	for (eksperyment_talia = 1; eksperyment_talia < 10; eksperyment_talia++)
	{
		eksperyment_ilosc_kart = (14 - eksperyment_talia) * 4;

		StworzTalie(karty, eksperyment_talia);

		Stan_Wojny.ruchy_suma = 0;

		cout << "\nTalia nr." << eksperyment_talia << ": ";

		for (int i = 0; i < 1000; i++)
		{
			TasowanieTali(karty, eksperyment_ilosc_kart);

			PrzypiszRekeXY(&GraczX, &GraczY, karty, eksperyment_ilosc_kart);

			WyczyscPlansze(&Stan_Wojny, &GraczX, &GraczY);

			Bitwa(&Stan_Wojny, &GraczX, &GraczY);

			Stan_Wojny.ruchy_suma += Stan_Wojny.ruchy_w_grze;
		}
		cout << "\nSrednia ilosc ruchow: " << Stan_Wojny.ruchy_suma / 1000;
	}
	cout << "\n";

#endif // MADRA_WOJNA_EKSPERYMENT_1

#ifdef MADRA_WOJNA_EKSPERYMENT_2

	Stan_Wojny.wariant = 'A';
	Stan_Wojny.rodzaj_gry = madra_wojna;

	StworzTalie(karty, 1);	//TALIA 1=52 karty
	
	GraczX.strategia = losowa;
	GraczY.strategia = losowa;

	cout << "\nLosowa vs Losowa: ";		//1
	Symulacje_1000(karty, &GraczX, &GraczY, &Stan_Wojny);

	GraczX.strategia = losowa;
	GraczY.strategia = wsciekla;

	cout << "\nLosowa vs Wsciekla: ";	//2
	Symulacje_1000(karty, &GraczX, &GraczY, &Stan_Wojny);

	GraczX.strategia = losowa;
	GraczY.strategia = pokojowa;

	cout << "\nLosowa vs Pokojowa: ";	//3
	Symulacje_1000(karty, &GraczX, &GraczY, &Stan_Wojny);

	GraczX.strategia = wsciekla;
	GraczY.strategia = wsciekla;

	cout << "\nWsciekla vs Wsciekla: ";	//4
	Symulacje_1000(karty, &GraczX, &GraczY, &Stan_Wojny);

	GraczX.strategia = wsciekla;
	GraczY.strategia = pokojowa;

	cout << "\nWsciekla vs Pokojowa: ";	//5
	Symulacje_1000(karty, &GraczX, &GraczY, &Stan_Wojny);

	GraczX.strategia = pokojowa;
	GraczY.strategia = pokojowa;

	cout << "\nPokojowa vs Pokojowa: ";	//6
	Symulacje_1000(karty, &GraczX, &GraczY, &Stan_Wojny);

#endif // MADRA_WOJNA_EKSPERYMENT_2

#ifdef TEST1
	int suma;

	int i, j;
	cout << "\n------------------------\nGx reka: ";
	suma = 0;
	for (i = 0; i < GraczX.reka.ilosc; i++)
	{
		j = (GraczX.reka.poczatek + i) % GraczX.reka.rozmiar;

		suma += GraczX.reka.karta[j].wartosc.numer;

		cout << GraczX.reka.karta[j].wartosc.numer << "(" << suma << ")|";
	}
	suma = 0;
	cout << "\nsuma: " << ranga_X << "\nGy reka: ";
	for (i = 0; i < GraczY.reka.ilosc; i++)
	{
		j = (GraczY.reka.poczatek + i) % GraczY.reka.rozmiar;

		suma += GraczY.reka.karta[j].wartosc.numer;

		cout << GraczY.reka.karta[j].wartosc.numer << "(" << suma << ")|";
	}
	cout << "\nsuma: " << ranga_Y << "\n";

	//-------
#endif // TEST1



#ifdef TEST2
	//------
	int eksperyment_talia=9, eksperyment_ilosc_kart=20, ranga_X=0, ranga_Y=0;
	Stan_Wojny.wariant = 'A';
	StworzTalie(karty, eksperyment_talia);
	for (int i = 0; i < 1000000; i++)
	{
		TasowanieTali(karty, eksperyment_ilosc_kart);

		PrzypiszRekeXY(&GraczX, &GraczY, karty, eksperyment_ilosc_kart);

		PrzypiszRange(&GraczX, &GraczY, &ranga_X, &ranga_Y);

		WyczyscPlansze(&Stan_Wojny, &GraczX, &GraczY);

		Bitwa(&Stan_Wojny, &GraczX, &GraczY);
	}
	cout << "Ile gier: " << Stan_Wojny.ile_gier;
	cout << "\nIle zwyciestwX: " << Stan_Wojny.zwyciestwa_gX;
	cout << "\nIle zwyciestwY: " << Stan_Wojny.zwyciestwa_gY;
	cout << "\nIle remisow: " << Stan_Wojny.remisy;	

#endif // TEST

	free(Stan_Wojny.karty_zwyciescy.karta);
	free(GraczX.tymczasowe.karta);
	free(GraczY.tymczasowe.karta);
	free(GraczX.reka.karta);
	free(GraczY.reka.karta);
	free(GraczX.wojna.karta);
	free(GraczY.wojna.karta);

	return 0;
}