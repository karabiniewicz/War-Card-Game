#ifndef funkcje_h
#define funkcje_h

#define MAX_KART 52

typedef enum
{
	jenda,
	dwie
}WypisKarty_t;

enum ZnakKarty_t
{	//oznaczenia: od '2' do Asa - od 2 do 14
	J = 11,
	Q,
	K,
	A
};

enum KolorKarty_t
{
	pik = 1,
	kier,
	karo,
	trefl
};

typedef enum
{
	nikt,
	zabieraX,
	zabieraY
}PrzydzielenieKarty_t;

enum StanGry_t
{
	kontynuuj,
	zakoncz
};

typedef struct
{
	union
	{
		enum ZnakKarty_t znak;
		int numer;
	} wartosc;
	enum KolorKarty_t kolor;
}karta_t;

typedef struct
{
	karta_t* karta;
	int poczatek = 0;
	int koniec = 0;		//pierwsze wolne miejsce w kolejce
	int ilosc = 0;
	int rozmiar = 0;	//maxymalny rozmiar tali
} kolejka_t;

typedef enum
{
	losowa,
	wsciekla,
	pokojowa,
	wlasna
}strategia_t;

typedef struct
{
	kolejka_t reka;
	kolejka_t wojna;
	kolejka_t tymczasowe;	//pojemnik na karty przy przenoszeniu kart
	strategia_t strategia = losowa;
} gracz_t;

typedef enum
{
	graczX,
	graczY
}kto_dwie_karty_t;

typedef enum
{
	zwykla_wojna,
	madra_wojna
}rodzaj_gry_t;

typedef enum
{
	ranga1,
	ranga2,
	ranga3
}ktora_ranga_t;

typedef struct
{
	char wariant;
	PrzydzielenieKarty_t kto_zabiera_karte = nikt;
	int ile_gier = 0;
	int zwyciestwa_gX = 0;
	int zwyciestwa_gY = 0;
	int remisy = 0;
	int ruchy_w_grze;
	int ruchy_suma = 0;
	rodzaj_gry_t rodzaj_gry = zwykla_wojna;
	int kto_dwie_karty = graczX;
	kolejka_t karty_zwyciescy;
	enum StanGry_t stan_gry;
}stan_gry_t;

void StworzTalie(karta_t karta[], int ktora_talia);

void TasowanieTali(karta_t* karta, int ilosc_kart);

void PrzypiszRekeXY(gracz_t* Gx, gracz_t* Gy, karta_t stos_kart[], int ilosc_kart);

void Przenies_Z_Do(kolejka_t* from, kolejka_t* to, int ile);

void WyczyscPlansze(stan_gry_t* Stan, gracz_t* Gx, gracz_t* Gy);

void Wybor(gracz_t* Gracz, gracz_t* Przeciwnik);

void WyczyscPojemnik(kolejka_t* Pojemnik);

void Bitwa(stan_gry_t* Stan, gracz_t* Gx, gracz_t* Gy);

PrzydzielenieKarty_t Wojna(stan_gry_t* Stan, gracz_t* Gx, gracz_t* Gy);

PrzydzielenieKarty_t Porownanie(stan_gry_t* Stan, gracz_t* Gx, gracz_t* Gy);

void PrzypiszRange(gracz_t* Gx, gracz_t* Gy, int* rangaX, int* rangaY, ktora_ranga_t ktora_ranga);

void Eksperyment_2(karta_t* karty, gracz_t* GraczX, gracz_t* GraczY, stan_gry_t* Stan_Wojny, ktora_ranga_t ktora_ranga);

void Symulacje_1000(karta_t* karty, gracz_t* GraczX, gracz_t* GraczY, stan_gry_t* Stan_Wojny);
#endif
