#ifndef GIELDA_GRA_H__
#define GIELDA_GRA_H__

#include "zapis_wczyt.h"
#include "obiekty_transakcji.h"
#include "gracz.h"

#include <vector>

class Gra
{
	// lista aktualnie połączonych graczy
	std::vector<Gracz> _gracze;
	
	// dane bierzącej rozgrywki
	unsigned int _tura;
	
	// podstawowe dane, na których będzie opierała się rozgrywka
	std::vector<Spolka> _spolki;
	std::vector<Waluta> _waluty;

public:
	
	Gra();
	~Gra();
	
	// startuje nową grę z aktualnie połączonymi graczami
	void start();
	// zapisuje stan rozgrywki
	void zapisz(const char* sciezka);
	// wczytuje zapisany wcześniej stan
	void wczytaj(const char* sciezka);
	
	// dodaje gracza o podanej nazwie
	// zwraca 0, jeśli uda sie dodać gracza - w przeciwnym wypadku 1
	int dodajGracza(const char* nazwa_gracza);
	// usuwa wszystkich graczy o podanej nazwie
	void usunGracza(const char* nazwa_gracza);
	
	// funkcja testowa
	void info();
	
	inline int iloscSpolek() { return _spolki.size(); }
	inline int iloscWalut() { return _waluty.size(); }
	
	friend void zapiszDane(const char*, TypDokumentu, void*);
	friend std::string utworzZnacznik(TypZnacznika, void*);
	friend void wczytajDane(const char*, void*);
	friend void* odczytajZnacznik(const std::vector<std::string>&, TypZnacznika, void*);
	
private:
	void dodajSpolke(const Spolka& nowa_spolka);
	void dodajSpolke(Spolka::Typ, const char* nazwa, unsigned int wartosc_akcji);
	void usunSpolke(const char* nazwa);
	
	void dodajWalute(Waluta nowa_waluta);
	void dodajWalute(const char* nazwa, float wartosc);
	void usunWalute(const char* nazwa);
	
	void usunWszystkieDane();
};

#endif // GIELDA_GRA_H__
