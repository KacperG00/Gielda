#ifndef GIELDA_UI_INTERFEJS_UZYTKOWNIKA_H__
#define GIELDA_UI_INTERFEJS_UZYTKOWNIKA_H__

#include "ui/klawisze_przyciski.h"

#include "ui/uklad.h"
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
	int aktualnyUklad;

public:
	static App* aplikacja;
	static sf::RenderWindow* okno;
	static Obiekt* aktualnieAktywnyObiekt;
	
	static sf::Event wydarzenie;
	static bool klawiszWcisniety[LICZBA_KLAWISZY];
	static bool przyciskMyszyWcisniety[LICZBA_PRZYCISKOW_MYSZY];
	static int pozMyszy_x, pozMyszy_y;
	
	
private:
	std::vector<Czcionka> czcionki;
	std::vector<Uklad*> uklady;
	
public:
	void utworzUI(sf::RenderWindow* window);

	void rysuj();
	void aktualizuj();
	
	void wybierzUklad(unsigned int uklad);

	inline void dodajCzcionke(const Czcionka& czcionka) {czcionki.push_back(czcionka);}
	Uklad * dodajUklad();
	void dodajObiekt(Obiekt* obiekt, unsigned int uklad);
	
	void czyscWszystko();
	void zamknijOkno() {okno->close();}
};

#endif // GIELDA_UI_INTERFEJS_UZYTKOWNIKA_H__
