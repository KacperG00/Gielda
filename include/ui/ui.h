#ifndef GIELDA_UI_INTERFEJS_UZYTKOWNIKA_H__
#define GIELDA_UI_INTERFEJS_UZYTKOWNIKA_H__

#include "ui/klawisze_przyciski.h"

#include "ui/czcionka.h"
#include "ui/obiekt.h"
#include "ui/przycisk.h"
#include "ui/suwak.h"
#include "ui/kontener.h"

#include <SFML/Graphics.hpp>

#include <vector>

#define LICZBA_KLAWISZY 256
#define LICZBA_PRZYCISKOW_MYSZY 32

class App;

class UI
{
public:
	App* aplikacja;
	sf::RenderWindow* okno;
	Obiekt* aktualnieAktywnyObiekt;
	
	static sf::Event wydarzenie;
	static bool klawiszWcisniety[LICZBA_KLAWISZY];
	static bool przyciskMyszyWcisniety[LICZBA_PRZYCISKOW_MYSZY];
	static int pozMyszy_x, pozMyszy_y;
	
	
private:
	std::vector<Czcionka> czcionki;
	std::vector<Obiekt*> obiekty;
	
public:
	void utworzUI(sf::RenderWindow* window);

	void rysuj();
	void aktualizuj();
	
	inline void dodajCzcionke(const Czcionka& czcionka) {czcionki.push_back(czcionka);}
	void dodajObiekt(Obiekt* obiekt);
	
	void czyscWszystko();
	void zamknijOkno() {okno->close();}
};

#endif // GIELDA_UI_INTERFEJS_UZYTKOWNIKA_H__
