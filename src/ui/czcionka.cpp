#include "ui/czcionka.h"

namespace ui {
	
	Czcionka::Czcionka()
		: wielkosc(0), styl(sf::Text::Regular), kolorWypelnienia(sf::Color(0xff,0xff,0xff,0xff))
	{
	}
	Czcionka::~Czcionka()
	{
	}

	void wczytajCzcionke(Czcionka& czcionka, const char* sciezka)
	{
		czcionka.czcionka.loadFromFile(sciezka);
	}

	void zmienWielkoscCzcionki(Czcionka& czcionka, unsigned int wielk)
	{
		czcionka.wielkosc =  wielk;
	}

	void zmienStylCzcionki(Czcionka& czcionka, unsigned int stl)
	{
		czcionka.styl = stl;
	}

	void zmienKolorCzcionki(Czcionka& czcionka, const sf::Color& kolor)
	{
		czcionka.kolorWypelnienia = kolor;
	}

}
