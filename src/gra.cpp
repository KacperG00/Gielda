#include "gra.h"

#include <iostream>
#include <fstream>
#include <string.h>
#include <string>

Gra::Gra()
	: _tura(0)
{
}
Gra::~Gra()
{
}

void Gra::start()
{
	_tura = 0;
	wczytaj("dane/startowe_dane.txt");
}

void Gra::zapisz(const char* sciezka)
{
	zapiszDane(sciezka, TypDokumentu::ZAPISU_ROZGRYWKI, this);
}

void Gra::wczytaj(const char* sciezka)
{
	// usuwanie starych danych
	usunWszystkieDane();
	
	// wczytywanie nowych danych
	wczytajDane(sciezka, this);
}

int Gra::dodajGracza(const char* nazwa_gracza)
{
	// Jeżeli string składa się z mniej niż 4 liter
	// lub zaczyna się cyfrą
	if( !(strlen(nazwa_gracza)<=3) && ((*nazwa_gracza > '0') && (*nazwa_gracza < '9')) )
	{
		fprintf(stderr, "Nazwa gracza musi składać się min. z 4 liter i nie może zaczynać się cyfrą!\n");
		return 1;
	}
	
	_gracze.push_back( Gracz(nazwa_gracza) );
	
	return 0;
}

void Gra::usunGracza(const char* nazwa_gracza)
{
	
	// Szuka graczy o nazwie równej łańcuchowi nazwa_gracza
	for( unsigned int i = 0; i < _gracze.size(); ++i )
	{
		if( !strcmp((_gracze[i].wezNazweGracza().c_str()), nazwa_gracza) )
		{
			_gracze.erase(_gracze.begin()+i);
		}
	}
}

void Gra::info()
{
	printf("-> Gracze(%d):\n", _gracze.size());
	for( unsigned int i = 0; i < _gracze.size(); ++i )
	{
		printf("%d. %s\n", i+1, _gracze[i].wezNazweGracza().c_str());
	}
	
	printf("-> Spolki(%d):\n", _spolki.size());
	for( unsigned int i = 0; i < _spolki.size(); ++i )
	{
		printf("%3d. %-32s | %4d | %4d\n", i+1, _spolki[i].nazwa.c_str(), _spolki[i].wartosc_akcji, _spolki[i].dostepne_akcje);
	}
	
	printf("-> Waluty(%d):\n", _waluty.size());
	for( unsigned int i = 0; i < _waluty.size(); ++i )
	{
		printf("%3d. %10s | %4.2f\n", i+1, _waluty[i].nazwa.c_str(), _waluty[i].wartosc);
	}
}

void Gra::dodajSpolke(const Spolka& nowa_spolka)
{
	_spolki.push_back(nowa_spolka);
}

void Gra::dodajSpolke(Spolka::Typ typ_spolki, const char* nazwa, unsigned int wartosc_akcji)
{
	Spolka nowa_spolka;
	nowa_spolka.typ_spolki = typ_spolki;
	nowa_spolka.nazwa = nazwa;
	nowa_spolka.wartosc_akcji = wartosc_akcji;
	nowa_spolka.dostepne_akcje = 1000;
	
	_spolki.push_back(nowa_spolka);
}

void Gra::usunSpolke(const char* nazwa)
{
	for( unsigned int i = 0; i < _spolki.size(); ++i )
	{
		if( !strcmp( _spolki[i].nazwa.c_str(), nazwa ) )
		{
			_spolki.erase(_spolki.begin()+i);
		}
	}
}

void Gra::dodajWalute(Waluta nowa_waluta)
{
	_waluty.push_back(nowa_waluta);
}

void Gra::dodajWalute(const char* nazwa, float wartosc)
{
	Waluta nowa_waluta;
	nowa_waluta.nazwa = nazwa;
	nowa_waluta.wartosc = wartosc;
	
	_waluty.push_back(nowa_waluta);
}

void Gra::usunWalute(const char* nazwa)
{
	for( unsigned int i = 0; i < _waluty.size(); ++i )
	{
		if( !strcmp( _waluty[i].nazwa.c_str(), nazwa ) )
		{
			_waluty.erase(_waluty.begin()+i);
		}
	}
}

void Gra::usunWszystkieDane()
{
	_spolki.clear();
	_waluty.clear();
}
